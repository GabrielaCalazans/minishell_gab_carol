/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:04:43 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/20 19:14:17 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	lexer(t_data *data)
{
	if (data->tokens->type == 3)
		printf("heya\n");
	return (1);
}

// int	is_valid_redirect(t_token tokens, char )
// {
// 	while (/* condition */)
// 	{
// 		/* code */
// 	}
// }
