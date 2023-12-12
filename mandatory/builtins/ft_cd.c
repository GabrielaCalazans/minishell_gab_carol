/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:03:28 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/12 09:02:27 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cd(t_data *data)
{
	char	*go_home;

	data->exit_code = 1;
	if (data->cmd->cmd && data->cmd->cmd[0]
		&& data->cmd->cmd[1] && data->cmd->cmd[2])
		perror("too many arguments");
	else if (data->cmd->cmd[1] == NULL)
	{
		go_home = getenv("HOME");
		if (go_home != NULL)
		{
			if (chdir(go_home) != 0)
				perror("cd");
		}
		else
			ft_putendl_fd("cd: could not determine home directory\n", 2);
	}
	else if (data->cmd->cmd[1] != NULL && chdir(data->cmd->cmd[1]) != 0)
		perror("cd");
	else
		data->exit_code = 0;
}
