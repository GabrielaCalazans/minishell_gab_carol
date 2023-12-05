/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:37:52 by carolinekun       #+#    #+#             */
/*   Updated: 2023/12/05 18:59:02 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	find_heredoc(t_data *data)
{
	t_rdct	*temp;
	int		i;

	i = 0;
	temp = data->rdct;
	while (temp)
	{
		while (i < temp->nbr_rdcts)
		{
			if (temp->redirects[i] == HEREDOC){
				ft_heredoc(temp->files[i]);
			}
			i++;
		}
		temp = temp->next;
	}
}

void	run_redirect(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->rdct->nbr_rdcts)
	{
		if (data->rdct->redirects[i] == HEREDOC)
			ft_input(HEREDOC_FILE, data);
		if (data->rdct->redirects[i] == APPEND)
			ft_append(data->rdct->files[i], data);
		if (data->rdct->redirects[i] == REDIRECT_IN)
			ft_input(data->rdct->files[i], data);
		if (data->rdct->redirects[i] == REDIRECT_OUT)
			ft_output(data->rdct->files[i], data);
	}
}

void	ft_heredoc(char	*key_str)
{
	char	*str;
	int		fd;
	int		bkpfd;
	int		pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		run_signals(1);
		fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		bkpfd = dup(1);
		str = readline("> ");
		while ((str != NULL) && ft_strncmp(key_str, str, \
				(ft_strlen(key_str))) != 0)
		{
			dup2(fd, 1);
			printf("%s\n", str);
			dup2(bkpfd, 1);
			free(str);
			str = readline("> ");
		}
		// exit(0);
	}
	waitpid(pid, &status, 0);
	// return (status);
	// exit(status);
}

/*
1. colocar sinais heredoc
2. excluir arquivo heredoc na hora da edição e execução
3. implementar execução de multiplos heredoc(s)
4. implementar exit code pro heredoc
*/