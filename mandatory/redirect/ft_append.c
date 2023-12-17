/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:13:16 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/16 19:55:30 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_append_error(char *file, t_data *data, int check)
{
	if (data->rdct_fds[1] == -1)
	{
		perror(file);
		data->exit_code = 1;
		if (check == 1)
			clean_exit(data, 0);
		return (1);
	}
	dup2(data->rdct_fds[1], 1);
	close(data->rdct_fds[1]);
	return (0);
}

int	ft_append(char *file, t_data *data, int check)
{
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == 0)
			data->rdct_fds[1] = open(file, O_WRONLY | O_APPEND);
		else
		{
			perror(file);
			data->exit_code = 1;
			if (check == 1)
				clean_exit(data, 0);
			return (1);
		}
	}
	else
		data->rdct_fds[1] = (open(file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (ft_append_error(file, data, check));
}
