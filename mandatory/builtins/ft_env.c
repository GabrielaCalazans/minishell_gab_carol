/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:06 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/05 15:40:35 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_data *data)
{
	t_env	*env_node;

	env_node = data->env_node;
	while (env_node != NULL)
	{
		ft_printf("%s=%s\n", env_node->var, env_node->value);
		env_node = env_node->next;
	}
}
