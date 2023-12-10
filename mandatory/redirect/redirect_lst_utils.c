/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_lst_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:33:10 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/09 19:53:09 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Func to find the size of the lst
int	ft_size_rdct(t_rdct *lst)
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
void	ft_clear_rdct(t_rdct **lst)
{
	t_rdct	*temp;
	t_rdct	*next;

	temp = *lst;
	while (temp != NULL)
	{
		freearray(temp->files);
		temp->files = NULL;
		free(temp->redirects);
		next = temp->next;
		free(temp);
		temp = next;
	}
	*lst = NULL;
}
