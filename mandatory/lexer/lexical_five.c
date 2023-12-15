/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_five.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:47:47 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/01 18:48:53 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_drd_case(int type)
{
	if (type == HEREDOC)
		return (TRUE);
	if (type == APPEND)
		return (TRUE);
	return (FALSE);
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

int	is_redrt_case(int type)
{
	if (type == REDIRECT_IN || type == REDIRECT_OUT)
		return (TRUE);
	if (type == HEREDOC || type == APPEND)
		return (TRUE);
	return (FALSE);
}

int	is_rd_case(int type)
{
	if (type == REDIRECT_IN)
		return (TRUE);
	if (type == REDIRECT_OUT)
		return (TRUE);
	return (FALSE);
}
