/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:04:33 by ckunimur          #+#    #+#             */
/*   Updated: 2023/10/24 19:39:38 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(t_data *data)
{
	int		i;
	t_data	*temp;

	i = 1;
	temp = data;
	printf("%s", temp->cmd[i]);
	i++;
	while (temp->cmd[i])
	{
		printf(" %s", temp->cmd[i]);
		i++;
	}
	printf("\n");
//	if (temp->cmd[1] == NULL)
//		printf("\n");
}
