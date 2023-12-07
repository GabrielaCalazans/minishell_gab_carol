/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:06:15 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/07 14:40:17 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(t_data *data)
{
	t_env	*env_node;
	t_env	*temp_node;

	//temp_node = ft_calloc(sizeof(t_env), 1);
	env_node = data->env_node;
	if (data->cmd->cmd[1])
	{
		temp_node = have_var(data, data->cmd->cmd[1]);
		if (temp_node == NULL)
			return ;
		while (env_node &&env_node->next != temp_node)
			env_node = env_node->next;
		if (temp_node == data->env_node)
		{
			env_node = data->env_node;
			data->env_node = env_node->next;
		}
		if (env_node && env_node->next)
			env_node->next = temp_node->next;
		temp_node->next = NULL;
		ft_clear_env(temp_node);
	}
	data->exit_code = 0;
}
