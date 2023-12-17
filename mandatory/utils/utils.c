/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:37:10 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/17 13:24:22 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_clean_lst(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
	{
		free(lst[i]);
		i++;
	}
	free(lst);
}

void	error_msg(t_data *data, char *str, int fd, int code)
{
	ft_putendl_fd(str, fd);
	data->exit_code = code;
}

void	finish_node(t_data *data)
{
	freearray(data->env);
	data->env = NULL;
	ft_set_env(data);
	data->exit_code = 0;
}
