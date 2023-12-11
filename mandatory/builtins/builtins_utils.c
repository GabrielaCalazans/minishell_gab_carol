/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 22:00:42 by dapaulin          #+#    #+#             */
/*   Updated: 2023/12/10 22:03:04 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var(t_data	*data)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (data->cmd->cmd[i])
	{
		if ((data->cmd->cmd[i][0] >= '0' && data->cmd->cmd[i][0] <= '9') \
			|| data->cmd->cmd[i][0] == '=')
			return (1);
		while (data->cmd->cmd[i][j] && data->cmd->cmd[i][j] != '=')
		{
			if ((data->cmd->cmd[i][j] >= 'A' && data->cmd->cmd[i][j] <= 'Z') \
				|| (data->cmd->cmd[i][j] >= 'a' && data->cmd->cmd[i][j] <= 'z') \
				|| (data->cmd->cmd[i][j] >= '0' && data->cmd->cmd[i][j] <= '9') \
				|| data->cmd->cmd[i][j] == '_')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}
