/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:44 by ckunimur          #+#    #+#             */
/*   Updated: 2023/11/07 19:14:08 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export(t_data *data)
{
	t_env	*env_node;

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
		if (is_valid_var(data))
		{
			printf("invalid var\n");
			return ;
		}
		if (have_var(data))
		{
			change_value(data);
		}
		else
			create_var(data);
	}
}

int	is_valid_var(t_data	*data)
{
	int		i;

	i = 0;
	if (data->cmd[1][0] >= '0' && data->cmd[1][0] <= '9')
		return (1);
	while (data->cmd[1][i])
	{
		if ((data->cmd[1][i] >= 'A' && data->cmd[1][i] <= 'Z') \
			|| (data->cmd[1][i] >= 'a' && data->cmd[1][i] <= 'z') \
			|| (data->cmd[1][i] >= '0' && data->cmd[1][i] <= '9') \
			|| data->cmd[1][i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

int	have_var(t_data *data)
{
	t_env	*env_node;

	env_node = data->env_node;
	while (env_node != NULL)
	{
		if (ft_strncmp(data->cmd[1], env_node->var, \
			ft_strlen(data->cmd[1] + 1)))
			env_node = env_node->next;
		else
			return (1);
	}
	return (0);
}

void	create_var(t_data *data)
{
	(void)data;
	printf ("criando var\n");
}

void	change_value(t_data *data)
{
	(void)data;
	printf ("mudando variavel\n");
}
