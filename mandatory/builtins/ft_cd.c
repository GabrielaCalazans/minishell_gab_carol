/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:03:28 by ckunimur          #+#    #+#             */
/*   Updated: 2023/10/18 17:31:35 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_cd(t_data *data)
{
	if (!ft_strncmp(data->cmd_args[0], "..", 2))
	{
		if(ft_strncmp(data->cmd_args[0], "../", 3))
		{
			if (!ft_strncmp(data->cmd_args[0], "..", 3))
				return(TRUE);
		}
		else if (!ft_strncmp(data->cmd_args[0], "../", 3))
			return(TRUE);
	}
}

int	check_valid_dir(char *str)
{
	int i;

	i = 0;

	if (!access(str, F_OK))
	{
		if(!access(str, X_OK))
		{
			
		}
	}
}

void ft_cd(t_data *data)
{


}