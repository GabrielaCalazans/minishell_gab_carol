/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redirect_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:48:47 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/21 16:27:43 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: VALIDATE THE PATH TO '> ./bla/bla.txt' case
	// if (tokens->next->type == SLASH)
	// 	return (validate_path(tokens));
int	is_path(t_token *tokens)
{
	if (tokens->next->type == SLASH)
		return (TRUE);
	return (FALSE);
}

int	tilde_case(t_token *tokens)
{
	if (tokens->next->type != WORD)
		return (C_ERROR);
	return (0);
}

int	asterick_case(t_token *tokens)
{
	if (tokens->next->type != WORD)
		return (C_ERROR);
	return (0);
}
