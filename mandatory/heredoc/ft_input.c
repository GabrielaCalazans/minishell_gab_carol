/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:17:01 by ckunimur          #+#    #+#             */
/*   Updated: 2023/11/30 08:47:27 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_input(t_data *data)
{
	if (access(data->cmd->cmd[1], F_OK) == -1)
	{
		printf("error\n");
		return ;
	}
	data->fds[0] = open(data->cmd->cmd[1], O_RDONLY);
	if (data->fds[0] == -1)
	{
		printf("error!\n");
		return ;
	}
	dup2(data->fds[0], 0);
	close(data->fds[0]);
}
