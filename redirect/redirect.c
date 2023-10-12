/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:08:47 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/12 15:52:59 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	find_file_name(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while(temp)
	{
		if (temp->type == 11)
		{
			while (temp->type == 11)
				temp = temp->next;
		}
		if (is_syntax_error(temp->type) && temp->type != 11)
			
		temp = temp->next;
	}
}

int	is_syntax_error(int type)
{
	if (type == 1 || type == 2)
		return (1);
	if (type == 3 || type == 5)
		return (1);
}

void	redirect_lst(t_token *tokens)
{
	
}