/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:04:43 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/10 16:58:01 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	lexer(t_data *data)
{
	if (ft_strncmp(data->tokens->type, "pipe", 5) == 0)
		printf("heya\n");
	return (1);
}

int	is_valid_redirect(t_token tokens, char )
{
	while (/* condition */)
	{
		/* code */
	}
	
}
