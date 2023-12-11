/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:03:28 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/10 22:05:19 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
int	check_cd(t_data *data)
{
	if (!ft_strncmp(data->cmd_args[0], "..", 2))
	{
		if (ft_strncmp(data->cmd_args[0], "../", 3))
		{
			if (!ft_strncmp(data->cmd_args[0], "..", 3))
				return (TRUE);
		}
		else if (!ft_strncmp(data->cmd_args[0], "../", 3))
			return (TRUE);
	}
	return (printf("NEET A RETURN VALUE HERE LINE 27 ft_cd\n"));
}

int	check_valid_dir(char *str)
{
	if (!access(str, F_OK))
	{
		if (!access(str, X_OK))
		{
			printf("nothing done yet.");
		}
	}
	return (printf("NEET A RETURN VALUE HERE LINE 43 ft_cd\n"));
}
*/

void	ft_cd(t_data *data)
{
	char	*go_home;

	data->exit_code = 1;
	if (data->cmd->cmd[2])
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
