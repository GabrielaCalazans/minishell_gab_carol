/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinekunimura <carolinekunimura@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:49:36 by carolinekun       #+#    #+#             */
/*   Updated: 2023/10/12 17:36:03 by carolinekun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_pwd(void)
{
	printf("ft_pwd");
	char *pwd;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
		printf("error: \"!pwd\"");
	else
		ft_putstr_fd(pwd, 1); 
}