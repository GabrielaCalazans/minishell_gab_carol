/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:04:33 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/10 15:05:19 by dapaulin         ###   ########.fr       */
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
	if (ft_array_size(data->cmd->cmd) > 1
		&& ft_strncmp(data->cmd->cmd[1], "-n", 3) == 0)
	{
		printf("%s", temp->cmd[++i]);
		i++;
		while (temp->cmd[i])
			printf(" %s", temp->cmd[i++]);
	}
	else
	{
		printf("%s", temp->cmd[i++]);
		while (temp->cmd[i])
			printf(" %s", temp->cmd[i++]);
		printf("\n");
	}
}
