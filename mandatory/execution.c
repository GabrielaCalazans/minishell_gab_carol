/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:55:22 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/04 14:28:55 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_fd(t_data *data, int n_fd)
{
	int	i;

	i = 0;
	while (i <= n_fd)
		close(data->fd[i++]);
}

void	execution(t_data *data)
{
	int		pid[3];
	int		status;
	int		ord;
	int		i;
	int		bkp;

	ord = 0;
	i = 0;
	data->n_cmd = 1;
	data->fd = ft_calloc(data->n_cmd * 2, sizeof(int));
	while (i < data->n_cmd * 2 - 1)
	{
		pipe(&data->fd[i]);
		i += 2;
	}
	i = 0;
	status = 0;
	while (i < data->n_cmd)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			bkp = dup(1);
			set_path_command(data);
			if (data->n_cmd - 1 != 0)
				dup_pipe(ord, data);
			execve(data->cmd->cmd[0], data->cmd->cmd, data->env);
			dup2(bkp, 1);
			printf("Error!\n");
			exit(1);
		}
		ord++;
		i++;
	}
	close_fd(data, data->n_cmd * 2);
	i = 0;
	while (i < data->n_cmd)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	exit(0);
}

void	dup_pipe(int ord, t_data *data)
{
	if (ord == 0)
	{
		dup2(data->fd[1], 1);
		close_fd(data, data->n_cmd * 2);
	}
	else if (ord == data->n_cmd - 1)
	{
		dup2(data->fd[ord], 0);
		close_fd(data, data->n_cmd * 2);
	}
	else
	{
		dup2(data->fd[ord + 1], 0);
		dup2(data->fd[ord + 2], 1);
		close_fd(data, data->n_cmd * 2);
	}
}

//test execution
//		if (i == 0) 
//			data->cmd = (char *[]){"/usr/bin/ls", NULL};
//		else if (i == 1)
//			data->cmd = (char *[]) {"/usr/bin/wc", "-c", NULL};
//		else 	
//			data->cmd = (char *[]) {"/usr/bin/tr", "6", "9", NULL};
