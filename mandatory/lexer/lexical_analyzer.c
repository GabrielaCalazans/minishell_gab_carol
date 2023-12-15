/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:04:43 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/01 14:33:24 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_pipe(t_token *tokens)
{
	t_token	*tmp;
	int		check;

	tmp = tokens;
	check = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			check++;
		tmp = tmp->next;
	}
	return (check);
}

int	has_rdrct_pipe(t_token *tokens)
{
	t_token	*tmp;
	int		redirects;

	tmp = tokens;
	redirects = 0;
	while (tmp)
	{
		if (tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OUT)
			redirects++;
		if (tmp->type == PIPE)
			break ;
		tmp = tmp->next;
	}
	return (redirects);
}

int	has_redirect(t_token *tokens)
{
	t_token	*temp;
	int		redirects;

	temp = tokens;
	redirects = 0;
	while (temp)
	{
		if (temp->type == 1 || temp->type == 2)
			redirects++;
		temp = temp->next;
	}
	return (redirects);
}

int	has_dredirect(t_token *tokens)
{
	t_token	*temp;
	int		redirects;

	temp = tokens;
	redirects = 0;
	while (temp)
	{
		if (temp->type == HEREDOC || temp->type == APPEND)
			redirects++;
		temp = temp->next;
	}
	return (redirects);
}
