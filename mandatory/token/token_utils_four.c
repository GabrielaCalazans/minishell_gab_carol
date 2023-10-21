/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_four.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:05:39 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/21 15:42:00 by gacalaza         ###   ########.fr       */
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
	return (FALSE);
}

int	is_r_bracket(char c)
{
	if (c == '(')
		return (R_BRACKET_O);
	if (c == ')')
		return (R_BRACKET_C);
	return (FALSE);
}

int	is_heredoc_case(t_data *data, int i)
{
	if (find_type(&data->prompt_in[i]) == HEREDOC
		|| find_type(&data->prompt_in[i]) == APPEND)
		return (TRUE);
	return (FALSE);
}
