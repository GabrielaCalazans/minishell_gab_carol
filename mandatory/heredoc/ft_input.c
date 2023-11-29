/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:17:01 by ckunimur          #+#    #+#             */
/*   Updated: 2023/11/27 12:09:19 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_input(t_data *data)
{
	if (access(data->cmd_args[0], F_OK) == -1)
	{
		printf("error\n");
		return ;
	}
	data->fds[0] = open(data->cmd_args[0], O_RDONLY);
	if (data->fds[0] == -1)
	{
		printf("error!\n");
		return ;
	}
	dup2(data->fds[0], 0);
	close(data->fds[0]);
}