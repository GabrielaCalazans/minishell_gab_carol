/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:17:01 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/07 15:16:53 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_input(char *file, t_data *data)
{
	//close(0);
	if (access(file, F_OK) == -1)
	{
		perror(file);
		exit(1);
	}
	data->rdct_fds[0] = open(file, O_RDONLY);
	//printf("oi\n");
	if (data->rdct_fds[0] == -1)
	{
		perror(file);
		exit(1) ;
	}
	dup2(data->rdct_fds[0], 0);
	//printf("oiee\n");
	close(data->rdct_fds[0]);
}
