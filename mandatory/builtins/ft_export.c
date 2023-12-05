/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:44 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/05 16:56:26 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export(t_data *data)
{
	t_env	*env_node;
	t_cmd	*tmp;
	int		i;

	i = 1;
	env_node = data->env_node;
	tmp = data->cmd;
	if (!data->cmd->cmd[1])
	{
		while (env_node != NULL)
		{
			if (env_node->value)
				ft_printf("declare -x %s=%s\n", env_node->var, env_node->value);
			else
				ft_printf("declare -x %s\n", env_node->var);
			env_node = env_node->next;
		}
		return ;
	}
	if (is_valid_var(data))
	{
		perror("invalid var\n");
		data->exit_code = 1;
		return ;
	}
	while (tmp->cmd[i])
	{
		env_node = have_var(data, tmp->cmd[i]);
		if (env_node == NULL)
			create_var(data, tmp->cmd[i]);
		else
			change_value(env_node, tmp->cmd[i]);
		i++;
	}
}

int	is_valid_var(t_data	*data)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (data->cmd->cmd[i])
	{
		if ((data->cmd->cmd[i][0] >= '0' && data->cmd->cmd[i][0] <= '9') || data->cmd->cmd[i][0] == '=')
			return (1);
		while (data->cmd->cmd[i][j] && data->cmd->cmd[i][j] != '=')
		{
			if ((data->cmd->cmd[i][j] >= 'A' && data->cmd->cmd[i][j] <= 'Z') \
				|| (data->cmd->cmd[i][j] >= 'a' && data->cmd->cmd[i][j] <= 'z') \
				|| (data->cmd->cmd[i][j] >= '0' && data->cmd->cmd[i][j] <= '9') \
				|| data->cmd->cmd[i][j] == '_')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

t_env	*have_var(t_data *data, char *arg)
{
	t_env	*env_node;

	env_node = data->env_node;
	while (env_node != NULL)
	{
		if (ft_strncmp(arg, env_node->var, \
			ft_strlen(env_node->var)))
			env_node = env_node->next;
		else
			return (env_node);
	}
	return (NULL);
}

void	create_var(t_data *data, char *arg)
{
	link_end(&data->env_node, linkar(arg));
}

void	change_value(t_env *env_node, char *arg)
{
	char	**split;

	split = ft_split(arg, '=');
	free(env_node->value);
	if (split[0] && split[1])
		env_node->value = split[1];
	else
		env_node->value = NULL;
	free(split[0]);
	free(split);
}
