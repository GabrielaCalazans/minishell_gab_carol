/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:11:03 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/15 14:23:40 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Func to create a new node
t_rdct	*createnode_rdct(char **files, int *redirects, int nbr_rdcts, int index)
{
	t_rdct	*newnode;

	newnode = (t_rdct *)ft_calloc(sizeof(t_rdct), 1);
	if (!newnode)
	{
		perror("malloc");
		return (NULL);
	}
	if (files)
	{
		newnode->files = ft_arraydup(files);
		newnode->redirects = ft_intdup(redirects, nbr_rdcts);
		newnode->nbr_rdcts = nbr_rdcts;
	}
	newnode->index = index;
	if (!newnode->redirects || !newnode->files)
	{
		//perror("ft_strdup");
		ft_clear_rdct(&newnode);
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
