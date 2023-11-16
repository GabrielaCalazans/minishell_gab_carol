/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinekunimura <carolinekunimura@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:37:52 by carolinekun       #+#    #+#             */
/*   Updated: 2023/11/16 10:56:47 by carolinekun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    heredoc(t_data *data)
{
    char *str;

    str = readline("> ");
    while (ft_strncmp(data->cmd[1], str, ft_strlen(data->cmd[1])) != 0)
    {
        printf("%s\n",str);   
    }
    exit(0);
}