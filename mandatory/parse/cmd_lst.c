/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:11:03 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/12 02:41:57 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Func to create a new node
t_cmd	*createnode_cmd(char **cmd, int index)
{
	t_cmd	*newnode;

	newnode = (t_cmd *)malloc(sizeof(t_cmd));
	if (!newnode)
	{
		perror("malloc");
		free(newnode);
	}
	if (cmd)
	{
		newnode->cmd = ft_arraydup(cmd);
		if (!newnode->cmd)
		{
			perror("ft_arraydup-cmd");
			ft_clear_cmd_lst(&newnode);
			return (NULL);
		}
	}
	else
		newnode->cmd = NULL;
	newnode->index = index;
	newnode->next = NULL;
	return (newnode);
}

// Func to find the last node
t_cmd	*ft_last_cmd(t_cmd *lst)
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
void	ft_add_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if (*lst)
	{
		temp = ft_last_cmd(*lst);
		temp->next = new;
	}
	else
		*lst = new;
}

// Func to add node at the beging of the lst
void	ft_add_front_cmd(t_cmd **lst, t_cmd *new)
{
	if (*lst)
	{
		new->next = *lst;
		*lst = new;
	}
	else
		*lst = new;
}
