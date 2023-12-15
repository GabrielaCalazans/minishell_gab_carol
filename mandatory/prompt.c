/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:55:06 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/15 17:57:02 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*create_command_path(char *path, char *command)
{
	char	*tmp1;
	char	*tmp2;

	if (command == NULL)
		return (NULL);
	tmp1 = ft_strjoin(path, "/");
	if (!tmp1)
		return (NULL);
	tmp2 = ft_strjoin(tmp1, command);
	free(tmp1);
	if (!access(tmp2, F_OK) && !access(tmp2, X_OK))
		return (tmp2);
	free(tmp2);
	return (NULL);
}

void	set_path_command(t_data *data)
{
	char	**path;
	char	*command_path;
	int		i;

	if (!data->path)
		return ;
	path = ft_split(data->path, ':');
	i = 0;
	while (path[i])
	{
		command_path = create_command_path(path[i], data->cmd->cmd[0]);
		if (command_path)
		{
			printf("%s", data->cmd->cmd[0]);
			if (data->cmd->cmd[0])
				free(data->cmd->cmd[0]);
			data->cmd->cmd[0] = command_path;
			freearray(path);
			return ;
		}
		i++;
	}
	freearray(path);
}

void	get_path(t_data *data)
{
	t_env	*tmp;

	tmp = data->env_node;
	data->path = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PATH", 5) == 0)
		{
			data->path = tmp->value;
			break ;
		}
		tmp = tmp->next;
	}
}

int	command_count(t_data *data)
{
	int		command;
	t_cmd	*tmp;

	command = 0;
	tmp = data->cmd;
	while (tmp)
	{
		command++;
		tmp = tmp->next;
	}
	return (command);
}

void	prompt(t_data *data)
{
	char	*aux;

	run_signals(1);
	data->prompt_in = readline(PROMPT);
	if (data->prompt_in == NULL)
		return ;
	aux = ft_strdup(data->prompt_in);
	data->prompt_in = get_str_expand(data, data->prompt_in);
	signal(SIGINT, SIG_IGN);
	if (aux && *aux)
		add_history(aux);
	free(aux);
}
