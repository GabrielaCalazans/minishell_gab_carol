/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:04:43 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/27 20:45:56 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	lexer(t_data *data)
{
	if (data->tokens->type == 3)
		printf("heya\n");
	return (1);
}

int	is_a_quote(int type)
{
	if (type == QUOTE_DOUBLE)
		return (QUOTE_DOUBLE);
	if (type == QUOTE_SINGLE)
		return (QUOTE_SINGLE);
	return (FALSE);
}

int	has_quotes(t_data *data)
{
	t_token	*tmp;
	int		check;

	tmp = data->tokens;
	check = 0;
	while (tmp)
	{
		if (is_a_quote(tmp->type))
			check = has_another_quote(tmp, tmp->type);
		if (check > 0)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

int	has_pipe(t_data *data)
{
	t_token	*tmp;
	int		check;

	tmp = data->tokens;
	check = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			check++;
		tmp = tmp->next;
	}
	return (check);
}
