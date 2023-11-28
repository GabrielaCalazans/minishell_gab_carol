/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:55:22 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/28 19:19:32 by gacalaza         ###   ########.fr       */
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
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		set_path_command(data);
		execve(data->cmd->cmd[0], data->cmd->cmd, data->env);
		printf("Error!\n");
		exit(1);
	}
	waitpid(-1, &status, 0);
}

// void	execution(t_data *data)
// {
// 	int	pid[3];
// 	int	status;
// 	int	ord;
// 	int	i;

// 	ord = 0;
// 	i = 0;
// 	data->n_cmd = 3;
// 	data->fd = ft_calloc(data->n_cmd * 2, sizeof(int));
// 	while (i < data->n_cmd * 2 - 1)
// 	{
// 		pipe(&data->fd[i]);
// 		i += 2;
// 	}
// 	i = 0;
// 	status = 0;
// 	while (i < 3)
// 	{
// 		// if (i == 0) 
// 		// 	data->cmd->cmd = (char *[]) {"/usr/bin/ls", NULL};
// 		// else if (i == 1)
// 		// 	data->cmd = (char *[]) {"/usr/bin/wc", "-c", NULL};
// 		// else 	
// 		// 	data->cmd = (char *[]) {"/usr/bin/tr", "6", "9", NULL};
// 		pid[i] = fork();
// 		if (pid[i] == 0)
// 		{
// 			int bkp = dup(1);
// 			set_path_command(data);
// 			dup_pipe(ord, data);
// 			execve(data->cmd->cmd[0], data->cmd->cmd, data->env);
// 			dup2(bkp, 1);
// 			printf("Error!\n");
// 			exit(1);
// 		}
// 		ord++;
// 		i++;
// 	}
// 	close_fd(data, data->n_cmd * 2);
// 	for (int y = 0; y < data->n_cmd; y++) {
// 		waitpid(pid[y], &status, 0);
// 	}
// }

void	dup_pipe(int ord, t_data *data)
{
	
	if (ord == 0)
	{
		dup2(data->fd[1], 1);
		close_fd(data, data->n_cmd * 2);
	}
	else if (ord == data->n_cmd - 1)
	{
		dup2(data->fd[2], 0);
		close_fd(data, data->n_cmd * 2);
	}
	else
	{
		dup2(data->fd[0], 0);
		dup2(data->fd[3], 1);
		close_fd(data, data->n_cmd * 2);
	}
}
