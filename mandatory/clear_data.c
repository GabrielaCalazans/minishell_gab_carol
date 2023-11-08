/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:16:14 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/08 17:31:00 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Func to free the the lst
		// free(temp->cmd);
		// temp->cmd = NULL;
// ft_clear_datalst(&data);
void	ft_clear_datalst(t_data **lst)
{
	t_data	*temp;
	t_data	*next;

	temp = *lst;
	while (temp != NULL)
	{
		free(temp->prompt_in);
		temp->prompt_in = NULL;
		next = temp->next;
		free (temp);
		temp = next;
	}
	*lst = NULL;
}

void	ft_clear_data(t_data *data)
{
	ft_clear_token(&data->tokens);
	data->tokens = NULL;
	ft_clear_rdct(&data->rdct);
	data->rdct = NULL;
	free(data->prompt_in);
	data->prompt_in = NULL;
}

void	ft_clear_env(t_env *env_node)
{
	t_env	*temp;	

	temp = NULL;
	while(env_node->next != NULL)
	{
		temp = env_node->next;
		free(env_node->var);
		free(env_node->value);
		free(env_node);
		env_node = temp;
	}
}