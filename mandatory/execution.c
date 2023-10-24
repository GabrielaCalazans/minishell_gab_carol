/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:55:22 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/24 15:16:09 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execution(t_data *data)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		set_path_command(data);
		execve(data->cmd[0], data->cmd, data->env);
		printf("Error!\n");
		exit(1);
	}
	waitpid(-1, &status, 0);
}
// void	exec_cmd(t_data *ptr)
// {
// 	char	*path;
// 	char	**cmd_args;
// 	char	*env_var;
// 	pid_t	child_pid;

// 	path = find_path(ptr->cmd);
// 	cmd_args = find_args(ptr->cmd_args);
// }

// void	exec_check(t_data *ptr)
// {
// 	if (is_builtins(ptr->cmd[0]))
// 		return (call_builtins(ptr));
// 	else
// 		printf("Se foda.");
// }
