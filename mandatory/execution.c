/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinekunimura <carolinekunimura@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:55:22 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/16 16:21:22 by carolinekun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execution(t_data *data)
{
	int	pid;
	int	status;
	int fd[2];

	pid = fork();
	pipe(fd);
	if (pid == 0)
	{
		set_path_command(data);
		execve(data->cmd[0], data->cmd, data->env);
		printf("Error!\n");
		exit(1);
	}
	waitpid(-1, &status, 0);
}

void	dup_pipe(int *fd, int ord, int len_pipe)
{
	if (ord == 0)
		dup2(0, fd[0]);
	else if (ord == len_pipe)
		dup2(1, fd[1]);
	else
	{
		dup2(0, fd[0]);
		dup2(1, fd[1]);
	}
}
