/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:13:16 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/10 15:00:46 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_append(char *file, t_data *data, int check)
{
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == 0)
			data->rdct_fds[1] = open(file, O_WRONLY | O_APPEND);
		else
		{
			perror(file);
			if (check == 1)
				exit(1);
			data->exit_code = 1;
			return ;
		}
	}
	else
		data->rdct_fds[1] = (open(file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (data->rdct_fds[1] == -1)
	{
		perror(file);
		if (check == 1)
			exit(1);
		data->exit_code = 1;
		return ;
	}
	dup2(data->rdct_fds[1], 1);
	close(data->rdct_fds[1]);
}
