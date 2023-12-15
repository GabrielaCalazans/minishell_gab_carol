/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redirect_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:48:47 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/09 16:47:19 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	is_special_case(int type, int check)
{
	if (check == 1)
	{
		if (type != 11 && type != 4)
			return (TRUE);
	}
	if (check == 2)
	{
		if (type == FLAG)
			return (TRUE);
	}
	if (check == 3)
	{
		if (type != FLAG && type != DOLLAR
			&& type != EXIT_STATUS)
			return (TRUE);
	}
	return (FALSE);
}

void	*return_error(void)
{
	ft_error_redirect(4);
	return (NULL);
}
