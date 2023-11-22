/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:55:22 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/22 16:17:03 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execution(t_data *data)
{
	int	pid[3];
	int	status;
	int ord = 0;
	int i = 0;

	data->n_cmd = 3;
	data->fd = ft_calloc(data->n_cmd * 2, sizeof(int));
	while (i < data->n_cmd * 2 - 1)
	{
		pipe(&data->fd[i]);
		i += 2;
	}
	i = 0;
	status = 0;
	while (i < 3)
	{
		// if (i == 0) 
		// 	data->cmd = (char *[]) {"/usr/bin/ls", NULL};
		// else if (i == 1)
		// 	data->cmd = (char *[]) {"/usr/bin/wc", "-c", NULL};
		// else 	
		// 	data->cmd = (char *[]) {"/usr/bin/tr", "6", "9", NULL};
		pid[i] = fork();
		if (pid[i] == 0)
		{
			int bkp = dup(1);
			printf("%i\n", i);
			// set_path_command(data);
			printf("%s\n", data->cmd[0]);
			dup_pipe(ord, data);
			execve(data->cmd[0], data->cmd, data->env);
			dup2(bkp, 1);
			printf("Error!\n");
			exit(1);
		}
		ord++;
		i++;
	}
	close(data->fd[0]);
	close(data->fd[1]);
	close(data->fd[2]);
	close(data->fd[3]);
	for (int y = 0; y < data->n_cmd; y++) {
		waitpid(pid[y], &status, 0);
	}
}

void	dup_pipe(int ord, t_data *data)
{
	
	if (ord == 0) {
		printf("primeiro pipe\n");
		dup2(data->fd[1], 1);
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->fd[2]);
		close(data->fd[3]);
	}
	else if (ord == data->n_cmd - 1) {
		printf("segundo pipe\n");
		dup2(data->fd[2], 0);
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->fd[2]);
		close(data->fd[3]);
	}
	else
	{
		printf("else pipe\n");	
		dup2(data->fd[0], 0);
		dup2(data->fd[3], 1);
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->fd[2]);
		close(data->fd[3]);
	}
}
