/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:26 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/09 21:35:50 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_data *data)
{
	long	err;

	err = 1;
	if (!data->cmd->cmd[1])
	{
		ft_clear_data(data);
		ft_clear_env(data->env_node);
		free(data);
		rl_clear_history();
		ft_printf("exit\n");
		// close(0);
		// close(1);
		// close(2);
		exit(err);
	}
	else if (data->cmd->cmd[2])
	{
		perror("exit: too many arguments\n");
		data->exit_code = 1;
	}
	else if (data->cmd->cmd[1])
	{
		if (ft_atoi(data->cmd->cmd[1]) == 0 && (data->cmd->cmd[1][0] != '0'))
		{
			err = 2;
			perror("numeric argument is required\n");
		}
		else if (ft_strlen(data->cmd->cmd[1]) < 19)
			err = ft_atoi(data->cmd->cmd[1]);
		// printf("error: %li\n", err);
		data->exit_code = err;
		ft_clear_data(data);
		ft_clear_env(data->env_node);
		free(data);
		rl_clear_history();
		ft_printf("exit\n");
		exit(err);
	}
}
