/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_six.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:48:16 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/12 04:07:26 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_r_bracket(char c)
{
	if (c == '(')
		return (R_BRACKET_O);
	if (c == ')')
		return (R_BRACKET_C);
	return (0);
}

int	is_path(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (tmp->next)
	{
		if (tmp->type == SLASH && tmp->next->type == WORD)
			return (TRUE);
		if (tmp->token[0] == '.' && tmp->next->type == SLASH)
		{
			tmp = tmp->next;
			if (tmp->next->type == WORD)
				return (TRUE);
		}
		tmp = tokens;
		if (tmp->type == WORD && tmp->next->type == SLASH)
			return (TRUE);
	}
	return (FALSE);
}

int	is_word(int type, int check)
{
	if (check == 1)
	{
		if (type == WORD)
			return (TRUE);
		if (type == EXIT_STATUS)
			return (TRUE);
	}
	if (check == 2)
	{
		if (type != REDIRECT_IN && type != REDIRECT_OUT
			&& type != HEREDOC && type != APPEND
			&& type != C_SPACE && type != H_TAB)
			return (TRUE);
	}
	if (check == 3)
	{
		if (type != REDIRECT_IN && type != REDIRECT_OUT
			&& type != HEREDOC && type != APPEND
			&& type != C_SPACE && type != PIPE)
			return (TRUE);
	}
	return (FALSE);
}
