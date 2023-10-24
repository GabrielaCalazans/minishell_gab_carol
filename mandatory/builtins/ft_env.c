/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:06 by ckunimur          #+#    #+#             */
/*   Updated: 2023/10/24 15:38:32 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



void	ft_env(t_data *data)
{
	t_env	*env_node;

	env_node = data->env_node;
	while (env_node->next != NULL)
	{
		ft_printf("%s=%s\n", env_node->var, env_node->value);
		env_node = env_node->next;
	}
}
// void	create_env(t_data **data, char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 		link_end(&(*data)->env_node, criate_list(envp[i++]));
// }

// void ft_env(t_data *data)
// {
// 	t_env *env_ptr;

// 	env_ptr = data->env_node;
// 	while (env_ptr != NULL)
// 	{
// 		printf("%s = %s \n", env_ptr->var, env_ptr->value);
// 		env_ptr = env_ptr->next;
// 	}
// }
