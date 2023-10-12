/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:58:59 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/12 16:06:12 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Func to find the size of the lst
int	ft_size(t_token *lst)
{
	int	len;

	len = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

// Func to free the the lst
void	ft_clear(t_token **lst)
{
	t_token	*temp;
	t_token	*next;

	temp = *lst;
	while (temp != NULL)
	{
		free(temp->token);
		temp->token = NULL;
		next = temp->next;
		free (temp);
		temp = next;
	}
	*lst = NULL;
}
