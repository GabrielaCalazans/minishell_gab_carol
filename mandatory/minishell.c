/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:36:31 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/15 20:24:09 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_data(t_data *data, char *envp[])
{
	data->prompt_in = NULL;
	data->env = NULL;
	data->path = NULL;
	data->fd = NULL;
	data->n_cmd = 0;
	data->cmd = NULL;
	data->rdct = NULL;
	data->head_cmd = NULL;
	data->head_rdct = NULL;
	data->tokens = NULL;
	data->env_node = NULL;
	data->rdct_fds[0] = -1;
	data->rdct_fds[1] = -1;
	data->bkp_fd[0] = dup(0);
	data->bkp_fd[1] = dup(1);
	data->exit_code = 0;
	data->pid = NULL;
	create_env(&data, envp);
	ft_set_env(data);
}

void	mini_start(t_data *data)
{
	get_path(data);
	data->no_exec = 0;
	if (ft_strlen(data->prompt_in) != 0)
		start_token(data);
	if (!data->no_exec)
	{
		if (has_redirect(data->tokens) || has_dredirect(data->tokens))
			create_redirect_lst(data);
		parsing_it(data);
		data->n_cmd = command_count(data);
		data->head_cmd = data->cmd;
		data->head_rdct = data->rdct;
		find_heredoc(data);
		execution(data);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	if (argv && argc > 1)
	{
		ft_putstr_fd("Minishell can't take arguments\n", 1);
		return (EXIT_FAILURE);
	}
	data = malloc(sizeof(t_data));
	set_data(data, envp);
	while (1)
	{
		prompt(data);
		if (data->prompt_in && ft_strlen(data->prompt_in) != 0)
			mini_start(data);
		else if (data->prompt_in == NULL || data->prompt_in[0] != '\0')
			clean_exit(data, 1);
		else
			data->exit_code = 0;
		ft_clear_data(data);
	}
	free(data);
	return (0);
}
