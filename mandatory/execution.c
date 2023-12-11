/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:55:22 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/11 16:42:32 by ckunimur         ###   ########.fr       */
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
	t_cmd	*tmp_cmds;
	t_rdct	*tmp_rdcts;

	len = 0;
	config_pipe(data);
	tmp_cmds = data->cmd;
	tmp_rdcts = data->rdct;
	data->bkp_fd[1] = dup(1);
	data->bkp_fd[0] = dup(0);
	if (run_one_builtin(data))
		return ;
	data->pid = ft_calloc(data->n_cmd, sizeof(int));
	run_only_redirects(data);
	len = run_process(data, &data->pid);
	run_waitpid(data, &data->pid, len);
	data->cmd = tmp_cmds;
	data->rdct = tmp_rdcts;
}

// Verificar se é um diretorio ou se o executavel pode ser executado.
void	execute_pid(t_data *data, int i, int ord)
{
	if (data->n_cmd - 1 != 0)
		dup_pipe(i, ord, data);
	run_redirect(data, i, 1);
	if (data->cmd->cmd && exec_builtin(data) == 0)
	{
		set_path_command(data);
		execve(data->cmd->cmd[0], data->cmd->cmd, data->env);
		dup2(data->bkp_fd[1], 1);
		close(1);
		close(0);
		perror(data->cmd->cmd[0]);
		clean_exit(data);
		exit(127);
	}
	else
	{
		rl_clear_history();
		ft_clear_env(data->env_node);
		ft_clear_data(data);
		exit(data->exit_code);
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
		close(data->fd[1]);
	}
	else if (i == data->n_cmd - 1)
	{
		dup2(data->fd[ord - 2], 0);
		close_fd(data, (data->n_cmd - 1) * 2);
		close(data->fd[ord - 2]);
	}
	else
	{
		dup2(data->fd[ord - 2], 0);
		dup2(data->fd[ord + 1], 1);
		close_fd(data, (data->n_cmd - 1) * 2);
		close(data->fd[ord - 2]);
		close(data->fd[ord + 1]);
	}
}
