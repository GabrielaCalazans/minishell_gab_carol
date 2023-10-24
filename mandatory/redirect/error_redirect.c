/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:31:51 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/20 16:59:55 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error_redirect(int error)
{
	if (error == 1)
		printf("syntax error near unexpected token\n");
	else if (error == 3)
		printf("quoted error\n");
	else if (error == 4)
		printf("redirect file name error\n");
	else
	{
		printf("undefined error\n");
	}
}

int	is_syntax_error(int type)
{
	if (type == REDIRECT_IN || type == REDIRECT_OUT)
		return (C_ERROR);
	if (type == PIPE || type == APPEND || type == HEREDOC)
		return (C_ERROR);
	return (C_SUCCESS);
}

int	is_possible_error(int type)
{
	if (type == DOT || type == SLASH)
		return (C_ERROR);
	if (type == TILDE || type == BACKSLASH || type == ASTERISK)
		return (C_ERROR);
	return (0);
}

int	check_error(t_token *tokens)
{
	int		current;
	t_token	*temp;

	current = tokens->type;
	temp = tokens->next;
	while (temp)
	{
		if (temp->type == C_SPACE || temp->type == H_TAB)
			temp = jump_white_spaces(temp);
		if (temp->type == DOT)
			return (dot_case(temp));
		if (temp->type == TILDE)
			return (tilde_case(temp));
		if (temp->type == ASTERISK)
			return (asterick_case(temp));
		temp = temp->next;
	}
	return (0);
}
