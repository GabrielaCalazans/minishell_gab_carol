/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:00:10 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/01 16:53:07 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_a_quote(int type)
{
	if (type == QUOTE_DOUBLE)
		return (QUOTE_DOUBLE);
	if (type == QUOTE_SINGLE)
		return (QUOTE_SINGLE);
	return (FALSE);
}

int	is_word_q(int check)
{
	if (check == WORD)
		return (TRUE);
	if (check == QUOTE_DOUBLE)
		return (TRUE);
	if (check == QUOTE_SINGLE)
		return (TRUE);
	return (FALSE);
}

int	is_backs(char *str, int len, int type)
{
	if (type == BACKSLASH && str[len] != '\0')
		return (len + 1);
	if (type == BACKSLASH && str[len] == '\0')
	{
		ft_error_parse(6);
		exit(1);
	}
	return (0);
}

int	is_redirect(char c)
{
	if (c == '<')
		return (REDIRECT_IN);
	if (c == '>')
		return (REDIRECT_OUT);
	else
		return (0);
}

int	is_pipe(char c)
{
	if (c == '|')
		return (PIPE);
	return (0);
}
