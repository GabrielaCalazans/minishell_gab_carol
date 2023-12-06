/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:04:33 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/06 17:19:36 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(t_data *data)
{
	int		i;
	t_cmd	*temp;

	i = 1;
	temp = data->cmd;
	if (temp->cmd[1] == NULL)
		return ;
	if (ft_strncmp(temp->cmd[i], "$?", 3) == 0)
	{
		free(temp->cmd[i]);
		temp->cmd[i] = ft_itoa(data->exit_code);
	}
	printf("%s", temp->cmd[i]);
	i++;
	if (ft_array_size(data->cmd->cmd) > 1
		&& ft_strncmp(data->cmd->cmd[1], "-n", 3) == 0)
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
