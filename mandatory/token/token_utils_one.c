/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:58:55 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/10 18:19:10 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	return (0);
}

int	is_questionmark(char c)
{
	if (c == '?')
		return (QUESTION);
	return (0);
}
