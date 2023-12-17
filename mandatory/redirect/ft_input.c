/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:17:01 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/16 19:53:50 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_input(char *file, t_data *data, int check)
{
	if (access(file, F_OK) == -1)
	{
		perror(file);
		data->exit_code = 1;
		if (check == 1)
			clean_exit(data, 0);
		return (1);
	}
	data->rdct_fds[0] = open(file, O_RDONLY);
	if (data->rdct_fds[0] == -1)
	{
		perror(file);
		data->exit_code = 1;
		if (check == 1)
			clean_exit(data, 0);
		return (1);
	}
	dup2(data->rdct_fds[0], 0);
	close(data->rdct_fds[0]);
	return (0);
}
