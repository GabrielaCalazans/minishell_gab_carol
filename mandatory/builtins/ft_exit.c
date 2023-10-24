/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:26 by ckunimur          #+#    #+#             */
/*   Updated: 2023/10/24 19:40:01 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_data *data)
{
	long err;

	err = 1;
	if (!data->cmd_args[1])
	{
		if(data->cmd_args[0])
			err = ft_atoi(data->cmd_args[0]);
		if((!err && (ft_strlen(data->cmd_args[0]) > 2) )|| !ft_isdigit(ft_atoi(data->cmd_args[0])))
		{
			if(!(ft_strlen(data->cmd_args[0]) > 19))
			{
				err = 2;
				ft_printf("numeric argument is required\n");
			}
		}
	}
	else
		printf("exit\nexit: too many argments");
	ft_clear_data(data);
	exit(err);
}
