/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:44 by ckunimur          #+#    #+#             */
/*   Updated: 2023/10/30 19:26:20 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export(t_data *data)
{
	t_env *env_node;

	env_node = data->env_node;
	if (!data->cmd[1])
	{
		while (env_node->next != NULL)
		{
			ft_printf("declare -x %s=%s\n", env_node->var, env_node->value);
			env_node = env_node->next;
		}
	}
	else
	{
		while (env_node->next != NULL && ft_strncmp(data->cmd[1], env_node->var, ft_strlen(data->cmd[1])))
			env_node = env_node->next;
		if (ft_strncmp(data->cmd[1], env_node->var, ft_strlen(data->cmd[1])))
				printf("Não achei\n");
		else
			printf("Achei %s\n", env_node->var);
	}
}
