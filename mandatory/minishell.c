/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:36:31 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/10 13:23:28 by dapaulin         ###   ########.fr       */
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
	data->tokens = NULL;
	data->env_node = NULL;
	data->rdct_fds[0] = -1;
	data->rdct_fds[1] = -1;
	data->bkp_fd[0] = dup(0);
	data->bkp_fd[1] = dup(1);
	data->exit_code = 0;
	create_env(&data, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	if (argc != 1)
		return (1);
	data = malloc(sizeof(t_data));
	set_data(data, envp);
	while (1)
	{
		prompt(data);
		if (data->prompt_in && ft_strlen(data->prompt_in) != 0)
			mini_start(data);
		else if (data->prompt_in == NULL || data->prompt_in[0] != '\0')
		{
			rl_clear_history();
			ft_clear_env(data->env_node);
			ft_clear_data(data);
			break ;
		}
		ft_clear_data(data);
	}
	free(data);
	return (0);
	(void)argv;
}

	// find_token(argv[1], &tokens);
	// printf("MAIN:");
	// printlist(tokens);
	// find_token("dasda*");
	// find_token("da s da *");
	// find_token("? *");
	// find_token("cat black dog > ");
	// find_token("cat oi, tudo bem? > oi.txt");
	// printf("%d\n", is_redirect('>'));
	// printf("%d\n", is_redirect('<'));
	// printf("%d\n", is_redirect('!'));