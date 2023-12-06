/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:55:06 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/06 16:05:26 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Adiciona o comando à história se não estiver vazio
// add_history(tmp->prompt_input);
// Agora 'input' contém o comando digitado pelo usuário
// VERIFICAR LEAK DE MEMORIA??
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
			ft_clean_lst(path);
			return ;
		}
		i++;
	}
	ft_clean_lst(path);
}

void	get_path(t_data *data)
{
	t_env	*tmp;

	tmp = data->env_node;
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

void	mini_start(t_data *data)
{
	extern char	**environ;

	data->env = environ;
	get_path(data);
	if (ft_strlen(data->prompt_in) != 0)
		start_token(data);
	if (has_redirect(data->tokens) || has_dredirect(data->tokens))
	{
		printf("has_redirect\n");
		create_redirect_lst(data);
		//define_rdct(data);
	}
	parsing_it(data);
	data->n_cmd = command_count(data);
	find_heredoc(data);
	// ABRAKADABRA printf("commands: %i\n", data->n_cmd);
	execution(data);
	return ;
}

void	prompt(t_data *data)
{
	run_signals(1);
	data->prompt_in = readline(PROMPT);
	signal(SIGINT, SIG_IGN);
	// printf("ABRAKADABRA token: '%s'", data->prompt_in);
	if (data->prompt_in == NULL)
	{
		ft_clear_data(data);
		ft_clear_env(data->env_node);
		rl_clear_history();
		free(data);
		exit(1);
	}
	if (data->prompt_in && *data->prompt_in)
	{
		add_history(data->prompt_in);
		// printf("ABRAKADABRA PROMPT: %s\n", data->prompt_in);
	}
}
