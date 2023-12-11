/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:16:14 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/10 13:21:21 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Func to free the the lst
		// free(temp->cmd);
		// temp->cmd = NULL;
// ft_clear_datalst(&data);
// void	ft_clear_datalst(t_data **lst)
// {
// 	t_data	*temp;
// 	t_data	*next;

// 	temp = *lst;
// 	while (temp != NULL)
// 	{
// 		free(temp->prompt_in);
// 		temp->prompt_in = NULL;
// 		next = temp->next;
// 		free (temp);
// 		temp = next;
// 	}
// 	*lst = NULL;
// }

void	ft_clear_data(t_data *data)
{
	ft_clear_token(&data->tokens);
	data->tokens = NULL;
	ft_clear_rdct(&data->rdct);
	data->rdct = NULL;
	ft_clear_cmd_lst(&data->cmd);
	data->cmd = NULL;
	free(data->prompt_in);
	data->prompt_in = NULL;
	free(data->fd);
	data->fd = NULL;
}

void	ft_clear_env(t_env *env_node)
{
	t_env	*temp;	

	temp = NULL;
	while (env_node->next != NULL)
	{
		temp = env_node->next;
		free(env_node->var);
		free(env_node->value);
		free(env_node);
		env_node = temp;
	}
	if (env_node != NULL)
	{
		free(env_node->var);
		free(env_node->value);
		free(env_node);
	}
}
