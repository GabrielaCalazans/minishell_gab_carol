/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:04:43 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/03 22:08:19 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	lexer(t_data *data)
{
	if (ft_strncmp(data->tokens->type, "pipe", 5) == 0)
		printf("heya\n");
	return (1);
}
