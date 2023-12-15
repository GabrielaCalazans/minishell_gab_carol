/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:44 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/15 15:09:37 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	only_export(t_data *data, t_env **env_node)
{
	if (!data->cmd->cmd[1])
	{
		while ((*env_node) != NULL)
		{
			if ((*env_node)->value)
				ft_printf("declare -x %s=\"%s\"\n", (*env_node)->var, \
				(*env_node)->value);
			else
				ft_printf("declare -x %s=\"\"\n", (*env_node)->var);
			(*env_node) = (*env_node)->next;
		}
		data->exit_code = 1;
		return (1);
	}
	data->exit_code = 0;
	return (0);
}

void	ft_export(t_data *data)
{
	t_env	*env_node;
	t_cmd	*tmp;
	int		i;

	i = 1;
	env_node = data->env_node;
	tmp = data->cmd;
	if (only_export(data, &env_node))
		return ;
	if (is_valid_var(data))
	{
		ft_putendl_fd(" not a valid identifier", 2);
		data->exit_code = 1;
		return ;
	}
	while (tmp->cmd[i])
	{
		env_node = have_var(data, tmp->cmd[i]);
		if (env_node == NULL)
			link_lst(&data->env_node, append_env(tmp->cmd[i]));
		else
			change_value(env_node, tmp->cmd[i]);
		i++;
	}
	env_node = node_last(data->env_node);
	freearray(data->env);
	data->env = NULL;
	ft_set_env(data);
	data->exit_code = 0;
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

t_env	*append_env(char *arg)
{
	t_env	*new_node;
	char	**split;

	new_node = ft_calloc(sizeof(t_env), 1);
	split = ft_split(arg, '=');
	new_node->var = split[0];
	if (split[1])
		new_node->value = split[1];
	free(split);
	new_node->next = NULL;
	return (new_node);
}
