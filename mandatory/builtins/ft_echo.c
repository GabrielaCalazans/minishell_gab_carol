/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:04:33 by ckunimur          #+#    #+#             */
/*   Updated: 2023/11/28 19:37:48 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(t_data *data)
{
	int		i;
	t_cmd	*temp;

	i = 1;
	temp = data->cmd;
	printf("%s", temp->cmd[i]);
	i++;
	if (ft_array_size(data->cmd->cmd) > 1 && ft_strncmp(data->cmd->cmd[1], "-n", 3) == 0)
	{
		while (temp->cmd[i])
		{
			printf(" %s", temp->cmd[i]);
			i++;
		}
	}
	else
	{
		while (temp->cmd[i])
		{
			printf(" %s", temp->cmd[i]);
			i++;
		}
		printf("\n");
	}
}
