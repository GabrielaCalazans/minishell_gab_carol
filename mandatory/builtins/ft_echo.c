/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:04:33 by ckunimur          #+#    #+#             */
/*   Updated: 2023/10/24 13:24:35 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(t_data *data)
{
	int		i;
	t_data	*temp;

	i = 0;
	temp = data;
	printf("%s", temp->cmd_args[i]);
	i++;
	while (temp->cmd_args[i+1])
	{
		if (temp->cmd_args[1])
			printf("%s", temp->cmd_args[i]);
		else
			printf(" %s", temp->cmd_args[i]);
		i++;
	}
	if (data->cmd[1] == NULL)
		printf("\n");
}
