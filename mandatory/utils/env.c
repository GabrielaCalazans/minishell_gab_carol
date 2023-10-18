/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:39:53 by ckunimur          #+#    #+#             */
/*   Updated: 2023/10/18 14:38:40 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*create_list(char *str)
{
	t_env	*aux;
	char	**split;
	aux = malloc(sizeof(t_env));
	split = ft_split(str, '=');
	aux->var = ft_strdup(split[0]);
	aux->value = ft_strdup(split[1]);
	aux->next = NULL;
	ft_clean_lst(split);
	return (aux);
}

t_env	*node_last(t_env *list)
{
	t_env	*last;

	last = list;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	linkar(t_env **list, t_env *current)
{
	if (list == NULL)
		return ;
	if (*list == NULL)
	{
		*list = current;
		return ;
	}
	current->next = *list;
	*list = current;
}

void	link_end(t_env **list, t_env *current)
{
	t_env	*aux;

	if (list == NULL)
		return ;
	if (*list == NULL)
	{
		*list = current;
		return ;
	}
	aux = node_last(*list);
	aux->next = current;
}