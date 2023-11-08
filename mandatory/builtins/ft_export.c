/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:44 by ckunimur          #+#    #+#             */
/*   Updated: 2023/11/08 17:21:10 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export(t_data *data)
{
	t_env	*env_node;

	env_node = data->env_node;
	if (!data->cmd[1])
	{
		while (env_node != NULL)
		{
			if (env_node->value)
				ft_printf("declare -x %s=%s\n", env_node->var, env_node->value);
			else
				ft_printf("declare -x %s\n", env_node->var);
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
		env_node = have_var(data);
		if (env_node == NULL)
			create_var(data);
		else
			change_value(env_node, data);
	}
}

int	is_valid_var(t_data	*data)
{
	int		i;

	i = 0;
	if (data->cmd[1][0] >= '0' && data->cmd[1][0] <= '9')
		return (1);
	while (data->cmd[1][i] && data->cmd[1][i] != '=')
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

t_env	*have_var(t_data *data)
{
	t_env	*env_node;

	env_node = data->env_node;
	while (env_node != NULL)
	{
		if (ft_strncmp(data->cmd[1], env_node->var, \
			ft_strlen(env_node->var)))
			env_node = env_node->next;
		else
			return (env_node);
	}
	return (NULL);
}

void	create_var(t_data *data)
{
	link_end(&data->env_node, linkar(data));
}

void	change_value(t_env *env_node, t_data *data)
{
	char **split;

	printf("mudando var\n");
	split = ft_split(data->cmd[1], '=');
	free(env_node->value);
	if (split[0] && split[1])
		env_node->value = split[1];
	else
		env_node->value = NULL;
	free(split[0]);
	free(split);
}
