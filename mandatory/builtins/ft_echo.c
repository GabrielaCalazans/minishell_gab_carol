/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:04:33 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/12 06:04:22 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	has_n_flag(char *cmd_param)
{
	int	i;

	if (cmd_param[0] != '-')
		return (0);
	i = 1;
	while (cmd_param[i])
	{
		if (cmd_param[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_data *data)
{
	int		i;
	int		flag;
	t_cmd	*temp;

	i = 1;
	temp = data->cmd;
	if (temp->cmd[1] == NULL)
		printf("\n");
	else
	{
		flag = has_n_flag(temp->cmd[1]);
		if (flag)
			i++;
		if (temp->cmd[i])
			printf("%s", temp->cmd[i++]);
		while (temp->cmd[i])
			printf(" %s", temp->cmd[i++]);
		if (!flag)
			printf("\n");
	}
	data->exit_code = 0;
}
