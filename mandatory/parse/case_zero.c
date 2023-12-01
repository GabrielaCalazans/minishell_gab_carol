/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_zero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:06:03 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/01 16:51:39 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	nb_words(t_token *tokens)
{
	t_token	*tmp;
	int		words;

	tmp = tokens;
	words = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (is_word(tmp->type, 2))
			words++;
		tmp = tmp->next;
	}
	return (words);
}

char	**get_words(t_token *tokens, int len)
{
	char	**words;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	words = ft_calloc((len + 1), sizeof(char *));
	if (!words)
		ft_error_parse(1);
	while (tmp && tmp->type != PIPE)
	{
		if (i == 0 && tmp->type == 10)
			words[i++] = ft_strdup(tmp->token);
		else if (is_word(tmp->type, 2) && i != 0)
		{
			if (tmp->type == QUOTED_WORD)
				words[i++] = trim_process(tmp->token, find_type(tmp->token));
			else
				words[i++] = ft_strdup(tmp->token);
		}
		tmp = tmp->next;
	}
	words[i] = NULL;
	return (words);
}
