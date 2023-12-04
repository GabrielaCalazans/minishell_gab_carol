/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:13:16 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/04 19:42:23 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_append(char *file, t_data *data)
{
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == 0)
		{
			printf("ta entrani\n");
			data->fd[0] = open(file, O_WRONLY | O_APPEND);
		}
		else
		{
			printf("error1\n");
			return ;
		}
	}
	else
		data->fd[0] = (open(file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (data->fd[0] == -1)
	{
		printf("error!2\n");
		return ;
	}
	dup2(data->fd[0], 1);
}
