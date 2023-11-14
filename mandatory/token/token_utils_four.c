/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_four.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:05:39 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/10 18:25:14 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	is_r_bracket(char c)
{
	if (c == '(')
		return (R_BRACKET_O);
	if (c == ')')
		return (R_BRACKET_C);
	return (0);
}

int	is_hd_c(char *str)
{
	if (find_type(str) == HEREDOC
		|| find_type(str) == APPEND)
		return (1);
	return (0);
}

int	is_e_c(char *str)
{
	if (find_type(&str[0]) == EXIT_STATUS)
		return (1);
	return (0);
}
