/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:17:28 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/16 19:55:06 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_output_error(char *file, t_data *data, int check)
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

int	ft_output(char *file, t_data *data, int check)
{
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == 0)
			data->rdct_fds[1] = open(file, O_WRONLY | O_TRUNC);
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
		data->rdct_fds[1] = (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	return (ft_output_error(file, data, check));
}
