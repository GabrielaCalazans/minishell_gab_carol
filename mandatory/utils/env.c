/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:39:53 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/14 21:36:01 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_env(t_data **data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		link_lst(&(*data)->env_node, create_node(envp[i]));
		i++;
	}
}

t_env	*create_node(char *str)
{
	t_env	*aux;
	char	**split;

	aux = malloc(sizeof(t_env));
	split = ft_split(str, '=');
	aux->var = ft_strdup(split[0]);
	aux->value = ft_strdup(split[1]);
	aux->next = NULL;
	freearray(split);
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

void	link_lst(t_env **list, t_env *current)
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

int	ft_size_lst_env(t_data *data)
{
	t_env	*tmp;
	int		len;

	len = 0;
	tmp = data->env_node;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}
