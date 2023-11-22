/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:37:52 by carolinekun       #+#    #+#             */
/*   Updated: 2023/11/21 19:37:03 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    heredoc(t_data *data)
{
	char    *str;
	int fd;
	int bkpfd;
	int pid;
	int status;
	
	pid = fork();
	if (pid == 0)
	{
		fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		bkpfd = dup(1);
		str = readline("> ");
		while ((str != NULL) && ft_strncmp(data->cmd[1], str, (ft_strlen(data->cmd[1]) +1)) != 0)
		{
			
			dup2(fd, 1);
			printf("%s\n",str);
			dup2(bkpfd, 1);
			free(str);
			str = readline("> ");
		}
	}
	waitpid(pid, &status, 0);
	exit(0);
}




/*
1. colocar sinais heredoc
2. excluir arquivo heredoc na hora da edição e execução
3. implementar execução de multiplos heredoc(s)
4. implementar exit code pro heredoc
*/