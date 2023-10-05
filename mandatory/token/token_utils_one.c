/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:58:55 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/03 16:15:50 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redirect(char c)
{
	if (c == '<')
		return (1);
	if (c == '>')
		return (2);
	else
		return (0);
}

int	is_pipe(char c)
{
	if (c == '|')
		return (3);
	return (0);
}

int	is_flag(char c)
{
	if (c == '-')
		return (4);
	return (0);
}

int	is_slash(char c)
{
	if (c == '/')
		return (5);
	return (0);
}

int	is_questionmark(char c)
{
	if (c == '?')
		return (6);
	return (0);
}
