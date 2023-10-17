/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:03:30 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/17 15:59:41 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtins(t_data *data)
{
	printf("is_builtins");
	if (ft_strncmp(&data->prompt_in[1], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(&data->prompt_in[1], "cd", 3) == 0)
		return (2);
	if (ft_strncmp(&data->prompt_in[1], "pwd", 4) == 0)
		return (3);
	if (ft_strncmp(&data->prompt_in[1], "export", 7) == 0)
		return (4);
	if (ft_strncmp(&data->prompt_in[1], "unset", 6) == 0)
		return (5);
	if (ft_strncmp(&data->prompt_in[1], "env", 4) == 0)
		return (6);
	if (ft_strncmp(&data->prompt_in[1], "exit", 5) == 0)
		return (7);
	else
		return (0);
}

void	call_builtins()
{
	t_data	*data;

	data = get_data();
	printf("call_builtins");
// 	if (is_builtins(ptr->cmd[0]) == 1)
// 		ft_echo(ptr);
// 	if (is_builtins(ptr->cmd[0]) == 2)
// 		ft_cd(ptr);
 	if (is_builtins(data) == 3)
 		ft_pwd();
// 	if (is_builtins(ptr->cmd[0]) == 4)
// 		ft_export(ptr);
// 	if (is_builtins(ptr->cmd[0]) == 5)
// 		ft_unset(ptr);
// 	if (is_builtins(ptr->cmd[0]) == 6)
// 		ft_env(ptr);
// 	if (is_builtins(ptr->cmd[0]) == 7)
// 		ft_exit(ptr);
 	else
 		printf("Them, all, eventually, went to shit");
}