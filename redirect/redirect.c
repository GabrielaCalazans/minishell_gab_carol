/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:08:47 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/11 17:05:31 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	find_file_name(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while(temp)
	{
		if (ft_strncmp(temp->type, "space", 6) == 0)
			temp = temp->next;
		
	}
}

int	is_syntax_error(int type, int type_next)
{
	if (type == 1 || type == 2)
		return (1);
	if (type == 3 || type == 5)
}

void	redirect_lst(t_token *tokens)
{
	
}