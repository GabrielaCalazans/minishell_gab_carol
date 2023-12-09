/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:36:31 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/08 20:45:53 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_data(t_data *data, char *envp[], char *argv[])
{
	(void)argv;
	data->tokens = NULL;
	data->rdct = NULL;
	data->env_node = NULL;
	data->cmd = NULL;
	data->n_cmd = 0;
	data->fd = NULL;
	data->rdct_fds[0] = -1;
	data->rdct_fds[1] = -1;
	data->exit_code = 0;
	create_env(&data, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	if (argc != 1)
		return (1);
	data = malloc(sizeof(t_data));
	set_data(data, envp, argv);
	while (1)
	{
		prompt(data);
		if (ft_strlen(data->prompt_in) != 0)
			mini_start(data);
		else
		{
			rl_clear_history();
			ft_clear_env(data->env_node);
			ft_clear_data(data);
			break;
		}
		ft_clear_data(data);
	}
	// rl_clear_history();
	// ft_clear_env(data->env_node);
	// ft_clear_data(data);
	printf("exit");
	free(data);
	return (0);
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