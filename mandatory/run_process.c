/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 22:25:12 by dapaulin          #+#    #+#             */
/*   Updated: 2023/12/10 22:28:37 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_one_builtin(t_data *data)
{
	if (data->n_cmd == 1 && data->cmd->cmd && is_builtins(data->cmd->cmd[0]))
	{	
		run_redirect(data, 0, 0);
		exec_builtin(data);
		close(1);
		close(0);
		dup2(data->bkp_fd[0], 0);
		close(data->bkp_fd[0]);
		dup2(data->bkp_fd[1], 1);
		close(data->bkp_fd[1]);
		return (1);
	}
	return (0);
}

void	run_only_redirects(t_data *data)
{
	if (!data->cmd->cmd && data->n_cmd == 1)
	{
		run_redirect(data, 0, 0);
		close(1);
		close(0);
		dup2(data->bkp_fd[0], 0);
		close(data->bkp_fd[0]);
		dup2(data->bkp_fd[1], 1);
		close(data->bkp_fd[1]);
	}
}

int	run_process(t_data *data, int **pid)
{
	int	i;
	int	ord;

	i = 0;
	ord = 0;
	while (data->rdct || data->cmd)
	{
		(*pid)[i] = fork();
		if ((*pid)[i] == 0)
		{
			run_signals(2);
			free((*pid));
			execute_pid(data, i, ord);
		}
		if (data->rdct && data->rdct->index == i)
			data->rdct = data->rdct->next;
		if (data->cmd)
			data->cmd = data->cmd->next;
		i++;
		ord += 2;
	}
	return (i);
}

void	run_waitpid(t_data *data, int **pid, int len)
{
	int	j;
	int	status;

	j = 0;
	close_fd(data, (data->n_cmd - 1) * 2);
	while (j < len)
		waitpid((*pid)[j++], &status, 0);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	free((*pid));
}
