/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:37:52 by carolinekun       #+#    #+#             */
/*   Updated: 2023/12/15 19:56:59 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	find_heredoc(t_data *data)
{
	t_rdct	*temp;
	int		i;

	i = 0;
	temp = data->rdct;
	data->head_rdct = data->rdct;
	while (temp)
	{
		while (i < temp->nbr_rdcts)
		{
			if (temp->redirects[i] == HEREDOC)
				ft_heredoc(temp->files[i], data);
			i++;
		}
		temp = temp->next;
	}
}

int	run_redirect(t_data *data, int index, int check)
{
	int	i;

	i = 0;
	if (data->rdct == NULL || data->rdct->files == NULL \
		|| data->rdct->index != index)
		return (0);
	while (i < data->rdct->nbr_rdcts)
	{
		if (data->rdct->redirects[i] == HEREDOC)
			ft_input(HEREDOC_FILE, data, check);
		if (data->rdct->redirects[i] == APPEND)
			ft_append(data->rdct->files[i], data, check);
		if (data->rdct->redirects[i] == REDIRECT_IN)
			ft_input(data->rdct->files[i], data, check);
		if (data->rdct->redirects[i] == REDIRECT_OUT)
			ft_output(data->rdct->files[i], data, check);
		i++;
	}
	return (data->exit_code);
}

/*
1. colocar sinais heredoc
2. excluir arquivo heredoc na hora da edição e execução
3. implementar execução de multiplos heredoc(s)
4. implementar exit code pro heredoc
*/
// Criar o exit code do heredoc
void	ft_heredoc(char	*ks, t_data *data)
{
	char	*str;
	int		fds[2];
	int		pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		run_signals(1);
		fds[0] = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		fds[1] = dup(1);
		str = readline("> ");
		while ((str != NULL) && ft_strncmp(ks, str, (ft_strlen(ks) + 1)))
		{
			dup2(fds[0], 1);
			ft_printf("%s\n", str);
			dup2(fds[1], 1);
			free(str);
			str = readline("> ");
		}
		finish_fork(data);
	}
	waitpid(pid, &status, 0);
}

void	finish_fork(t_data *data)
{
	clean_exit(data, 0);
}
