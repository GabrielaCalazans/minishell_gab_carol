/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:11:03 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/19 16:34:39 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Func to create a new node
t_rdct	*createnode_rdct(char *file, int redirect)
{
	t_rdct	*newnode;

	newnode = (t_rdct *)malloc(sizeof(t_rdct));
	if (!newnode)
		perror("malloc");
	newnode->file = ft_strdup(file);
	newnode->redirect = redirect;
	if (!newnode->redirect || !newnode->file)
	{
		perror("strdup");
		free(newnode);
		return (NULL);
	}
	newnode->next = NULL;
	return (newnode);
}

// Func to find the last node
t_rdct	*ft_last_rdct(t_rdct *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

// Func to add node at the end of the lst
void	ft_add_back_rdct(t_rdct **lst, t_rdct *new)
{
	t_rdct	*temp;

	if (*lst)
	{
		temp = ft_last_rdct(*lst);
		temp->next = new;
	}
	else
		*lst = new;
}

// Func to add node at the beging of the lst
void	ft_add_front_rdct(t_rdct **lst, t_rdct *new)
{
	if (*lst)
	{
		new->next = *lst;
		*lst = new;
	}
	else
		*lst = new;
}
