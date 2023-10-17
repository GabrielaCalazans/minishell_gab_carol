/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:55:22 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/17 15:59:20 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	exec_cmd(t_data *ptr)
// {
// 	char	*path;
// 	char	**cmd_args;
// 	char	*env_var;
// 	pid_t	child_pid;

// 	path = find_path(ptr->cmd);
// 	cmd_args = find_args(ptr->cmd_args);
// }

void	exec_check(t_data *data)
{
 	if (is_builtins(data))
 		return (call_builtins(data->prompt_in));
 	else
 		printf("Se foda.");
}
