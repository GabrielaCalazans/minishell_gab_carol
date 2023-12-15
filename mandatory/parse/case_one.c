/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:35:31 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/14 20:32:07 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// fun to jump redirect's file name
t_token	*move_one(t_token *tokens)
{
	t_token	*tmp;

	tmp = jump_white_spaces(tokens);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp && tmp->type == QUOTED_WORD)
		{
			if (tmp->next)
			{
				while (tmp && is_word(tmp->type, 3))
					tmp = tmp->next;
			}	
			else
				return (NULL);
		}
		if (tmp && tmp->type != WORD && tmp->type != SLASH
			&& is_special_case(tmp->type, 3))
			break ;
		if (tmp && tmp->next)
			tmp = tmp->next;
		else
			return (NULL);
	}
	return (tmp);
}

int	nb_words_r(t_token *tokens)
{
	t_token	*tmp;
	int		words;

	tmp = tokens;
	words = 0;
	while (tmp && tmp->type != PIPE)
	{
		tmp = jump_white_spaces(tmp);
		if (tmp == NULL)
			break ;
		if (tmp && is_word(tmp->type, 2))
		{
			while (tmp && is_word(tmp->type, 3))
				tmp = tmp->next;
			words++;
		}
		if (tmp && tmp->next && is_rd_case(tmp->type))
			tmp = move_one(tmp->next);
		else
		{
			if (tmp && tmp->type != PIPE)
				tmp = tmp->next;
		}
	}
	return (words);
}

char	**get_words_one(t_token *tokens)
{
	char	**words;
	t_token	*tmp;
	int		i;
	int		len;

	i = 0;
	tmp = tokens;
	len = nb_words_r(tokens);
	if (len < 1)
		return (NULL);
	words = ft_calloc(sizeof(char **), (len + 1));
	if (!words)
		ft_error_parse(1);
	while (tmp && tmp->type != PIPE)
	{
		if (is_word(tmp->type, 2))
			words[i++] = get_name(&tmp);
		if (tmp && is_rd_case(tmp->type))
			tmp = move_one(tmp->next);
		else
			if (tmp && tmp->type != PIPE)
				tmp = tmp->next;
	}
	return (words);
}
