/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:55:22 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/21 16:20:30 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execution(t_data *data)
{
	int	pid[2];
	int	status;
	int fd[2][2];
	int ord = 0;
	int i = 0;
	
	pipe(fd[0]);
	pipe(fd[1]);
	status = 0;
	while (i < 3)
	{
		if (i == 0) 
			data->cmd = (char *[]) {"/usr/bin/ls", NULL};
		else if (i == 1)
			data->cmd = (char *[]) {"/usr/bin/wc", "-c", NULL};
		else 	
			data->cmd = (char *[]) {"/usr/bin/tr", "6", "9", NULL};
		pid[i] = fork();
		if (pid[i] == 0)
		{
			int bkp = dup(1);
			printf("%i\n", i);
			set_path_command(data);
			printf("%s\n", data->cmd[0]);
			dup_pipe((int *)fd, ord, 1);
			execve(data->cmd[0], data->cmd, data->env);
			dup2(bkp, 1);
			printf("Error!\n");
			exit(1);
		}
		ord++;
		i++;
	}
	close(fd[0][0]);
	close(fd[0][1]);
	for (int y = 0; y < 2; y++) {
		waitpid(pid[y], &status, 0);
	}
}

void	dup_pipe(int *fd, int ord, int len_pipe)
{
	
	if (ord == 0) {
		printf("primeiro pipe\n");
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}
	else if (ord == len_pipe) {
		printf("segundo pipe\n");
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		printf("else pipe\n");	
		dup2(0, fd[0]);
		dup2(1, fd[1]);
		close(fd[0]);
		close(fd[1]);
	}
}
