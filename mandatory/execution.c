/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:55:22 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/17 13:18:58 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_fd(t_data *data, int n_fd)
{
	int	i;

	i = 0;
	if (n_fd == 0)
		return ;
	while (i <= n_fd)
		close(data->fd[i++]);
}

void	execution(t_data *data)
{
	int		len;

	len = 0;
	data->pid = ft_calloc(data->n_cmd, sizeof(int));
	config_pipe(data);
	data->bkp_fd[1] = dup(1);
	data->bkp_fd[0] = dup(0);
	if (run_one_builtin(data))
		return ;
	run_only_redirects(data);
	len = run_process(data, &data->pid);
	run_waitpid(data, &data->pid, len);
}

int	valid_stat(t_data *data)
{
	struct stat	path_stat;

	if (access(data->cmd->cmd[0], F_OK) == -1)
	{
		error_msg(data, " command not found", 2, 127);
		return (0);
	}
	if (stat(data->cmd->cmd[0], &path_stat) != 0)
	{
		perror("stat");
		return (0);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		error_msg(data, " Is a directory\n", 2, 126);
		return (0);
	}
	if (access(data->cmd->cmd[0], X_OK) == -1)
	{
		error_msg(data, " Permission denied", 2, 126);
		return (0);
	}
	return (1);
}

// int	valid_stat(t_data *data)
// {
// 	struct stat	path_stat;

// 	if (access(data->cmd->cmd[0], F_OK) == -1)
// 	{
// 		ft_putendl_fd(" command not found", 2);
// 		data->exit_code = 127;
// 		return (0);
// 	}
// 	if (stat(data->cmd->cmd[0], &path_stat) != 0)
// 	{
// 		perror("stat");
// 		return (0);
// 	}
// 	if (S_ISDIR(path_stat.st_mode))
// 	{
// 		ft_putstr_fd(" Is a directory\n", 2);
// 		data->exit_code = 126;
// 		return (0);
// 	}
// 	if (access(data->cmd->cmd[0], X_OK) == -1)
// 	{
// 		ft_putendl_fd(" Permission denied", 2);
// 		data->exit_code = 126;
// 		return (0);
// 	}
// 	return (1);
// }

void	execute_pid(t_data *data, int i, int ord)
{
	if (data->n_cmd - 1 != 0)
		dup_pipe(i, ord, data);
	run_redirect(data, i, 1);
	if (data->cmd->cmd && exec_builtin(data) == 0)
	{
		set_path_command(data);
		if (valid_stat(data))
		{
			execve(data->cmd->cmd[0], data->cmd->cmd, data->env);
			dup2(data->bkp_fd[1], 1);
			perror(data->cmd->cmd[0]);
		}
		else
			dup2(data->bkp_fd[1], 1);
		close(1);
		close(0);
		if (data->exit_code != 126)
			data->exit_code = 127;
		clean_exit(data, 0);
	}
	else
		clean_exit(data, 0);
}

void	config_pipe(t_data *data)
{
	int	i;

	i = 0;
	data->fd = ft_calloc(data->n_cmd * 2, sizeof(int));
	while (data->n_cmd != 1 && i < data->n_cmd * 2 - 1)
	{
		pipe(&data->fd[i]);
		i += 2;
	}
}
