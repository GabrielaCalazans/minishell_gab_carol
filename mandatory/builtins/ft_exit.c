/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:26 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/14 22:25:19 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_exit(t_data *data, int check)
{
	int	exit_code;

	exit_code = data->exit_code;
	ft_clear_data(data);
	ft_clear_env(data->env_node);
	freearray(data->env);
	data->env = NULL;
	free(data);
	rl_clear_history();
	if (check)
		ft_printf("exit\n");
	exit(exit_code);
}

void	ft_exit(t_data *data)
{
	data->exit_code = 0;
	if (!data->cmd->cmd[1])
		clean_exit(data, 1);
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
		clean_exit(data, 1);
	}
}
