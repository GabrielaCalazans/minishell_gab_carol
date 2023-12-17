/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:16:14 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/16 17:08:30 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	ft_close_fds(void)
{
	int	i;

	i = 2;
	while (i < 1024)
	{
		close(i++);
	}
}

void	ft_clear_data(t_data *data)
{
	ft_clear_token(&data->tokens);
	data->tokens = NULL;
	ft_clear_rdct(&data->head_rdct);
	data->rdct = NULL;
	ft_clear_cmd_lst(&data->head_cmd);
	data->cmd = NULL;
	data->head_cmd = NULL;
	data->head_rdct = NULL;
	free(data->pid);
	data->pid = NULL;
	if (data->prompt_in)
		free(data->prompt_in);
	data->prompt_in = NULL;
	ft_close_fds();
	free(data->fd);
	data->fd = NULL;
}
