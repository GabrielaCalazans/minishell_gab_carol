/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:33:10 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/28 19:41:26 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Func to find the size of the lst
int	ft_size_cmd(t_cmd *lst)
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
void	ft_clear_cmd_lst(t_cmd **lst)
{
	t_cmd	*temp;
	t_cmd	*next;

	temp = *lst;
	while (temp != NULL)
	{
		freearray(temp->cmd);
		next = temp->next;
		free (temp);
		temp = next;
	}
	*lst = NULL;
}
