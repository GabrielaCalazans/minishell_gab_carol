/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:44 by ckunimur          #+#    #+#             */
/*   Updated: 2023/10/31 16:37:11 by ckunimur         ###   ########.fr       */
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
		if (create_var(data, data->env_node));
			printf("nova var\n");
	}
}

int	create_var(t_data *data, t_env *env_node)
{
	while (env_node->next != NULL && ft_strncmp(data->cmd[1], env_node->var, ft_strlen(data->cmd[1])))
	{
		if (ft_strncmp(data->cmd[1], env_node->var, ft_strlen(data->cmd[1])))
		{
			printf("Não achei\n");
			return(1);
		}
		else if (!ft_strncmp(data->cmd[1], env_node->var, ft_strlen(data->cmd[1])))
		{
			printf("Achei %s\n", env_node->var);
			return(1);
		}
		env_node = env_node->next;
	}
	return(0);
}