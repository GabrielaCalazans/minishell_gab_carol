/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:13:16 by ckunimur          #+#    #+#             */
/*   Updated: 2023/11/27 12:09:07 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_append(t_data *data)
{
	int	fd;

	if (access(data->cmd_args[0], F_OK) == 0)
	{
		if (access(data->cmd_args[0], W_OK) == 0)
		{
			printf("ta entrani\n");
			fd = open(data->cmd_args[0], O_WRONLY | O_APPEND);
		}
		else
		{
			printf("error1\n");
			return ;
		}
	}
	else
		fd = (open(data->cmd_args[0], O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (fd == -1)
	{
		printf("error!2\n");
		return ;
	}
	dup2(fd, 1);
}
