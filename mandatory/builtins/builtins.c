/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:03:30 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/10 14:52:53 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtins(char *check)
{
	if (check == NULL)
		return (0);
	if (ft_strncmp(check, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(check, "cd", 3) == 0)
		return (2);
	if (ft_strncmp(check, "pwd", 4) == 0)
		return (3);
	if (ft_strncmp(check, "export", 7) == 0)
		return (4);
	if (ft_strncmp(check, "unset", 6) == 0)
		return (5);
	if (ft_strncmp(check, "env", 4) == 0)
		return (6);
	if (ft_strncmp(check, "exit", 5) == 0)
		return (7);
	return (0);
}

int	exec_builtin(t_data *data)
{
	int					index;
	const t_builtins	builtins[8] = {
	{"error", NULL},
	{"echo", ft_echo},
	{"cd", ft_cd},
	{"pwd", ft_pwd},
	{"export", ft_export},
	{"unset", ft_unset},
	{"env", ft_env},
	{"exit", ft_exit}
	};

	index = 0;
	if (data->cmd)
		index = is_builtins(data->cmd->cmd[0]);
	if (index != 0)
		builtins[index].built_in(data);
	return (index);
}
