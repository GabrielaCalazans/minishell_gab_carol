/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:39:09 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/01 18:46:18 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_flag(char *str)
{
	if (ft_strlen(str) > 1)
	{
		if (str[0] == '-' && ft_isalpha(str[1]))
			return (FLAG);
	}
	return (0);
}

int	is_slash(char c)
{
	if (c == '/')
		return (SLASH);
	if (c == '\\')
		return (BACKSLASH);
	return (0);
}

int	is_questionmark(char c)
{
	if (c == '?')
		return (QUESTION);
	return (0);
}

int	is_slashcase(int type)
{
	if (type == BACKSLASH || type == SLASH)
		return (TRUE);
	return (FALSE);
}

int	is_worbks_case(int type, char c)
{
	(void)c;
	if (type == WORD || type == BACKSLASH)
		return (TRUE);
	return (FALSE);
}
