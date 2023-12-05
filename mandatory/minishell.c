/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:36:31 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/05 11:30:08 by ckunimur         ###   ########.fr       */
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
		mini_start(data);
		ft_clear_data(data);
	}
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