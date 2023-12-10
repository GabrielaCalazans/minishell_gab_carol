/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:26 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/10 15:25:26 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_exit(t_data *data)
{
	ft_clear_data(data);
	ft_clear_env(data->env_node);
	free(data);
	rl_clear_history();
	ft_printf("exit\n");
	exit(data->exit_code);
}

void	ft_exit(t_data *data)
{
	data->exit_code = 1;
	if (!data->cmd->cmd[1])
		clean_exit(data);
	else if (data->cmd->cmd[2])
	{
		perror("exit: too many arguments\n");
		data->exit_code = 1;
	}
	else if (data->cmd->cmd[1])
	{
		if (ft_atoi(data->cmd->cmd[1]) == 0 && (data->cmd->cmd[1][0] != '0'))
		{
			data->exit_code = 2;
			perror("numeric argument is required\n");
		}
		else if (ft_strlen(data->cmd->cmd[1]) < 19)
			data->exit_code = ft_atoi(data->cmd->cmd[1]);
		clean_exit(data);
	}
}
