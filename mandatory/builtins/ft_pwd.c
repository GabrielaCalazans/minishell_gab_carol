/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:06:02 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/15 14:24:33 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_data *data)
{
	char	current_dir[1024];

	(void)data;
	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
	{
		printf("%s\n", current_dir);
		data->exit_code = 0;
	}
	else
	{
		data->exit_code = 1;
		perror("getcwd");
	}
}
