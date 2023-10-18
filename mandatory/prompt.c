/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:55:06 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/17 21:12:22 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Adiciona o comando à história se não estiver vazio
// add_history(tmp->prompt_input);
// Agora 'input' contém o comando digitado pelo usuário
// VERIFICAR LEAK DE MEMORIA??
void	set_path_command(t_data *data)
{
	char	**path;
	char	*tmp1;
	char	*tmp2;
	int		i = 0;
	
	path = ft_split(data->path, ':');
	while(path[i])
	{
		tmp1 = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp1, data->cmd[0]);
		if (tmp1)
			free(tmp1);
		if (!access(tmp2, F_OK))
		{
			if(!access(tmp2, X_OK))
			{
				if (data->cmd[0])
					free(data->cmd[0]);
				data->cmd[0] = tmp2;
				ft_clean_lst(path);
				return;
			}
		}
		if (tmp2)
			free(tmp2);
		i++;
	}
}
/*
[] pipe
[] exit code
[x] path command 
[] mult pipes
*/
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

void	prompt(t_data *data)
{
	extern char **environ;
	while (1)
	{
		data->prompt_in = readline(PROMPT);
		if (data->prompt_in[0] != '\0')
		{
			add_history(data->prompt_in);
			printf("prompt %s\n", data->prompt_in);
		}
		data->cmd = ft_split(data->prompt_in, ' ');
		data->path = "/nfs/homes/ckunimur/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/nfs/homes/ckunimur/.local/bin";
		if (data->prompt_in[0] != '\0')
			start_token(data);
		//printf("%s\n", data->cmd[0]);
		data->env = environ;
		if (!exec_builtin(data))
			execution(data);
		free(data->prompt_in);
		data->prompt_in = NULL;
	}
	rl_clear_history();
}

/*
	PATH=
	/nfs/homes/ckunimur/bin
	:/usr/local/sbin:/usr/local/bin
	:/usr/sbin:
	/usr/bin
	:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/nfs/homes/ckunimur/.local/bin
*/