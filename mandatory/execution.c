/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:55:22 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/06 16:21:40 by ckunimur         ###   ########.fr       */
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
	int		*pid;
	int		status;
	int		i;
	t_cmd	*tmp_cmds;
	t_rdct	*tmp_rdcts;

	i = 0;
	status = 0;
	pid = ft_calloc(data->n_cmd, sizeof(int));
	config_pipe(data);
	tmp_cmds = data->cmd;
	tmp_rdcts = data->rdct;
	if (data->n_cmd == 1 && exec_builtin(data))
		return ;
	while (i < data->n_cmd)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			run_signals(2);
			execute_pid(data, i);
		}
		if (data->rdct)
			data->rdct = data->rdct->next;
		if (data->cmd)
			data->cmd = data->cmd->next;
		i++;
	}
	i = 0;
	close_fd(data, (data->n_cmd - 1) * 2);
	while (i < data->n_cmd)
		waitpid(pid[i++], &status, 0);
	free(pid);
	free(data->fd);
	data->cmd = tmp_cmds;
	data->rdct = tmp_rdcts;
}

void	execute_pid(t_data *data, int i)
{
	int	bkp;
	char **temp_cmd;
	char **temp_env;

	bkp = dup(1);
	run_redirect(data);
	set_path_command(data);
	if (data->n_cmd - 1 != 0)
		dup_pipe(i, data);
	if (!exec_builtin(data) && data->cmd->cmd[0] != NULL)
	{
		temp_cmd = ft_arraydup(data->cmd->cmd);
		temp_env = ft_arraydup(data->env);
		ft_clear_data(data);
		execve(temp_cmd[0], temp_cmd, temp_env);
	}
	dup2(bkp, 1);
	printf("Error! execute_pid\n");
	ft_clear_data(data);
	exit(1);
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

void	dup_pipe(int ord, t_data *data)
{
	if (ord == 0)
	{
		dup2(data->fd[1], 1);
		close_fd(data, (data->n_cmd - 1) * 2);
	}
	else if (ord == data->n_cmd - 1)
	{
		dup2(data->fd[ord], 0);
		close_fd(data, (data->n_cmd - 1) * 2);
	}
	else
	{
		dup2(data->fd[ord + 1], 0);
		dup2(data->fd[ord + 2], 1);
		close_fd(data, (data->n_cmd - 1) * 2);
	}
}

