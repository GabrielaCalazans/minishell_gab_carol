/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:13:16 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/06 17:55:47 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_append(char *file, t_data *data)
{
	close(data->rdct_fds[1]);
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == 0)
			data->rdct_fds[1] = open(file, O_WRONLY | O_APPEND);
		else
		{
			printf("error1\n");
			return ;
		}
	}
	else
		data->rdct_fds[1] = (open(file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (data->rdct_fds[1] == -1)
	{
		printf("error!2\n");
		return ;
	}
	dup2(data->rdct_fds[1], 1);
}
