/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:26 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/11 16:45:28 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_exit(t_data *data)
{
	int	exit_code;

	exit_code = data->exit_code;
	ft_clear_token(&data->tokens);
	ft_clear_cmd_lst(&data->cmd);
	ft_clear_rdct(&data->rdct);
	ft_clear_env(data->env_node);
	free(data->fd);
	free(data->pid);
	free(data->prompt_in);
	free(data);
	rl_clear_history();
	ft_printf("exit\n");
	exit(exit_code);
}

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		else
			i++;
	}
	return (1);
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
		if (!ft_str_isdigit(data->cmd->cmd[1]))
		{
			data->exit_code = 2;
			perror("numeric argument is required\n");
		}
		else if (ft_strlen(data->cmd->cmd[1]) < 19)
			data->exit_code = ft_atoi(data->cmd->cmd[1]);
		clean_exit(data);
	}
}
