/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 22:05:41 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/10 21:56:21 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// fun to jump double redirect's file name
t_token	*move_two(t_token *tokens)
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
		if (tmp->type != WORD && tmp->type != SLASH
			&& is_special_case(tmp->type, 3))
			break ;
		if (tmp->next)
			tmp = tmp->next;
		else
			return (NULL);
	}
	return (tmp);
}

int	nb_words_dr(t_token *tokens)
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
		if (tmp && tmp->next && is_drd_case(tmp->type))
			tmp = move_two(tmp->next);
		else if (tmp && tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return (words);
}

char	**get_words_two(t_token *tokens)
{
	t_token	*tmp;
	char	**words;
	int		i;
	int		len;

	i = 0;
	len = nb_words_dr(tokens);
	if (len < 1)
		return (NULL);
	tmp = tokens;
	words = ft_calloc(sizeof(char **), (len + 1));
	if (!words)
		ft_error_parse(1);
	while (tmp && tmp->type != PIPE)
	{
		if (is_word(tmp->type, 2))
			words[i++] = get_name(&tmp);
		if (tmp && is_drd_case(tmp->type))
			tmp = move_two(tmp->next);
		else
			if (tmp && tmp->type != PIPE)
				tmp = tmp->next;
	}
	return (words);
}
