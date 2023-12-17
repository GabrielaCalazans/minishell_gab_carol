/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:06 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/16 21:43:32 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_data *data)
{
	t_env	*env_node;

	if (data->cmd->cmd[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(data->cmd->cmd[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		return ;
	}
	env_node = data->env_node;
	while (env_node != NULL)
	{
		if (env_node->value)
			printf("%s=%s\n", env_node->var, env_node->value);
		env_node = env_node->next;
	}
	data->exit_code = 0;
}

void	ft_set_env(t_data *data)
{
	t_env	*tmp;
	char	*aux;
	int		len;
	int		i;

	i = 0;
	tmp = data->env_node;
	len = ft_size_lst_env(data);
	data->env = ft_calloc(sizeof(char **), (len + 1));
	while (tmp && i < len)
	{
		aux = NULL;
		if (tmp->value)
		{
			aux = ft_strjoin(tmp->var, "=");
			data->env[i] = ft_strjoin(aux, tmp->value);
			i++;
			free(aux);
		}
		tmp = tmp->next;
	}
	data->env[i] = NULL;
}
