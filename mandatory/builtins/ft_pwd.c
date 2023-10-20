/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:06:02 by ckunimur          #+#    #+#             */
/*   Updated: 2023/10/18 15:00:40 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_pwd(t_data *data)
{
	t_env *env_node;

	env_node = data->env_node;
	while(env_node->next != NULL)
	{
		if (!ft_strncmp(env_node->var, "PWD", 4))
		{
			ft_printf("%s\n", env_node->value);
			return;
		}
		env_node = env_node->next;
		
}
}