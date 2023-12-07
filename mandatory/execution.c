/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:55:22 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/07 16:05:53 by ckunimur         ###   ########.fr       */
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
	int		j;
	int ord = 0;
	t_cmd	*tmp_cmds;
	t_rdct	*tmp_rdcts;

	status = 0;
	pid = ft_calloc(data->n_cmd, sizeof(int));
	config_pipe(data);
	tmp_cmds = data->cmd;
	tmp_rdcts = data->rdct;
	data->bkp_fd[1] = dup(1);
	data->bkp_fd[0] = dup(0);
	i = 0;
	//printf("'%p'\n", data->cmd->cmd);
	if (data->cmd->cmd && data->n_cmd == 1 && is_builtins(data->cmd->cmd[0]))
	{	
		run_redirect(data, i);
		exec_builtin(data);
		dup2(data->bkp_fd[0], 0);
		dup2(data->bkp_fd[1], 1);
		return ;
	}
	while (data->rdct || data->cmd)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			run_signals(2);
			execute_pid(data, i, ord);
		}
		if (data->rdct)
			data->rdct = data->rdct->next;
		if (data->cmd)
			data->cmd = data->cmd->next;
		i++;
		ord+=2;
	}
	j = 0;
	close_fd(data, (data->n_cmd - 1) * 2);
	while (j < i)
		waitpid(pid[j++], &status, 0);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	free(pid);
	free(data->fd);
	data->cmd = tmp_cmds;
	data->rdct = tmp_rdcts;
}

void	execute_pid(t_data *data, int i, int ord)
{
	if (data->cmd->cmd == NULL)
		return ;
	if (data->n_cmd - 1 != 0)
		dup_pipe(i, ord, data);
	run_redirect(data, i);
	if (exec_builtin(data) == 0)
	{
		set_path_command(data);
		execve(data->cmd->cmd[0], data->cmd->cmd, data->env);
		dup2(data->bkp_fd[1], 1);
		perror(data->cmd->cmd[0]);
		ft_clear_data(data);
		exit(127);
	}
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

void	dup_pipe(int i, int ord, t_data *data)
{
	if (i == 0)
	{
		dup2(data->fd[1], 1);
		close_fd(data, (data->n_cmd - 1) * 2);
	}
	else if (i == data->n_cmd - 1)
	{
		dup2(data->fd[ord - 2], 0);
		close_fd(data, (data->n_cmd - 1) * 2);
	}
	else
	{
		dup2(data->fd[ord - 2], 0);
		dup2(data->fd[ord + 1], 1);
		close_fd(data, (data->n_cmd - 1) * 2);
	}
}

