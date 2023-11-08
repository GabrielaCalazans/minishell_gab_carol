/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:06:02 by ckunimur          #+#    #+#             */
/*   Updated: 2023/11/08 18:04:05 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_data *data)
{
	char	current_dir[1024];

	(void)data;
	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
		printf("%s\n", current_dir);
	else
		perror("getcwd");
}
