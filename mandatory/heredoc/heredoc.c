/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:37:52 by carolinekun       #+#    #+#             */
/*   Updated: 2023/12/04 18:00:17 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	find_hrdc(t_data *data)
{
	t_rdct	*temp;
	int		i;

	i = 0;
	temp = data->rdct;
	while (temp->next != NULL)
	{
		while (i < temp->nbr_rdcts)
		{
			if (temp->redirects[i] == HEREDOC)
				heredoc(temp->files[i]);
		}
		temp = temp->next;
	}
}

void	heredoc(char	*key_str)
{
	char	*str;
	int		fd;
	int		bkpfd;
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		run_signals(1);
		fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		bkpfd = dup(1);
		str = readline("> ");
		while ((str != NULL) && ft_strncmp(key_str, str, \
			(ft_strlen(key_str) + 1)) != 0)
		{
			dup2(fd, 1);
			printf("%s\n", str);
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