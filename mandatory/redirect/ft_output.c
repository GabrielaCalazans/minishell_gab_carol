/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:17:28 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/09 14:51:30 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_output(char *file, t_data *data, int check)
{
	(void)check;
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == 0)
			data->rdct_fds[1] = open(file, O_WRONLY | O_TRUNC);
		else
		{
			perror(file);
			data->exit_code = 1;
			return ;
		}
	}
	else
		data->rdct_fds[1] = (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (data->rdct_fds[1] == -1)
	{
		perror(file);
		data->exit_code = 1;
		return ;
	}
	dup2(data->rdct_fds[1], 1);
	close(data->rdct_fds[1]);
}
