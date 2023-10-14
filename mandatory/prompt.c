/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinekunimura <carolinekunimura@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:55:06 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/13 11:44:43 by carolinekun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Adiciona o comando à história se não estiver vazio
// add_history(tmp->prompt_input);
// Agora 'input' contém o comando digitado pelo usuário
void	prompt(t_data *data)
{
	while (1)
	{
		if (data->prompt_in[0] != '\0')
		{
			add_history(data->prompt_in);
			printf("prompt %s\n", data->prompt_in);
			exec_check(data->prompt_in);
		}
		if (data->prompt_in[0] != '\0')
			start_token(data);
		free(data->prompt_in);
		data->prompt_in = NULL;
	}
	rl_clear_history();
}
