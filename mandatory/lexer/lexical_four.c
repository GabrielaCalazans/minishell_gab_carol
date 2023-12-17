/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:45:41 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/16 16:39:53 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_dollar(char *str)
{
	if (ft_strlen(str) > 1)
	{
		if (str[0] == '$' && str[1] == '?')
			return (EXIT_STATUS);
		if (str[0] == '$' && str[1] != '?')
			return (DOLLAR);
	}
	return (0);
}

int	is_quote(char c)
{
	if (c == '\"')
		return (QUOTE_DOUBLE);
	if (c == '\'')
		return (QUOTE_SINGLE);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ')
		return (SPACE_E);
	if (c == '\t')
		return (H_TAB);
	return (0);
}

int	is_heredoc(char *str, int check)
{
	if (check == 1)
	{
		if (str[0] == str[1])
			return (HEREDOC);
	}
	if (check == 2)
	{
		if (str[0] == str[1])
			return (APPEND);
	}
	return (check);
}

int	is_special_char(char c)
{
	if (c == '*')
		return (ASTERISK);
	if (c == '&')
		return (AMPERSAND);
	if (c == '~')
		return (TILDE);
	if (c == '.')
		return (DOT);
	if (c == ';')
		return (SEMICOLON);
	return (0);
}
