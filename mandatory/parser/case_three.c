/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:47:31 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/16 19:36:03 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	nb_words_three(t_token *tokens)
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
		if (tmp->next && is_drd_case(tmp->type))
			tmp = move_two(tmp->next);
		if (tmp && tmp->next && is_rd_case(tmp->type))
			tmp = move_one(tmp->next);
		else
			if (tmp && tmp->type != PIPE)
				tmp = tmp->next;
	}
	return (words);
}

void	process_tokens(t_token *tokens, int *i, char **words)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (is_word(tmp->type, 2))
			words[(*i)++] = get_name(&tmp);
		if (tmp && is_drd_case(tmp->type))
			tmp = move_two(tmp->next);
		if (tmp && is_rd_case(tmp->type))
			tmp = move_one(tmp->next);
		else
			if (tmp && tmp->type != PIPE)
				tmp = tmp->next;
	}
}

char	**get_words_three(t_token *tokens)
{
	int		i;
	int		len;
	char	**words;

	i = 0;
	len = nb_words_three(tokens);
	if (len < 1)
		return (NULL);
	words = ft_calloc(sizeof(char *), (len + 1));
	if (!words)
	{
		ft_error_parse(1);
		exit(1);
	}
	process_tokens(tokens, &i, words);
	return (words);
}
