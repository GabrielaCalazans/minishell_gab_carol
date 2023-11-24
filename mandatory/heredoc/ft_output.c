/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:17:28 by ckunimur          #+#    #+#             */
/*   Updated: 2023/11/24 20:18:03 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_output(t_data *data)
{
	int fd;

	if (access(data->cmd_args[0], F_OK) == 0)
	{
		if (access(data->cmd_args[0], W_OK) == 0)
			fd = open(data->cmd_args[0], O_WRONLY | O_TRUNC); 
		else
		{
			printf("error1\n");
			return;
		}
	}
	else
		fd = (open(data->cmd_args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (fd == -1)
	{
		printf("error!2\n");
		return;
	}
	dup2(fd, 1);
}
