/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_zero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:06:03 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/10 19:52:44 by gacalaza         ###   ########.fr       */
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
		if (tmp->type == WORD || tmp->type == QUOTED_WORD)
			words++;
		tmp = tmp->next;
	}
	return (words);
}

char	**get_words(t_token *tokens, int len)
{
	t_token	*tmp;
	int		i;
	char	**words;

	i = 0;
	tmp = tokens;
	words = malloc(sizeof(char **) * (len + 1));
	if (!words)
		ft_error_parse(1);
	while (tmp && tmp->type != PIPE)
	{
		if (is_word(tmp->type, 2))
		{
			words[i] = ft_strdup(tmp->token);
			i++;
		}
		tmp = tmp->next;
	}
	words[i] = NULL;
	return (words);
}
