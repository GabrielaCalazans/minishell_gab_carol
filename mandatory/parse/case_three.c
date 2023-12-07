/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:47:31 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/06 19:37:43 by gacalaza         ###   ########.fr       */
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
		{
			if (tmp && tmp->type != PIPE)
				tmp = tmp->next;
		}
	}
	return (words);
}

void	process_tokens(t_token *tokens, int *i, char **words)
{
	t_token	*tmp;
	char	*aux;

	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		
		if (i == 0 && tmp->type == 10)
			words[(*i)++] = ft_strdup(tmp->token);
		else if (is_word(tmp->type, 2) && i != 0)
		{
			if (tmp->type == QUOTED_WORD)
			{
				if (tmp->next)
				{
					words[(*i)] = ft_strdup(trim_process(tmp->token, find_type(tmp->token)));
					tmp = tmp->next;
					while (tmp && is_word(tmp->type, 3))
					{
						aux = ft_strdup(words[(*i)]);
						free(words[(*i)]);
						words[(*i)] = ft_strjoin(aux, trim_process(tmp->token, find_type(tmp->token)));
						free(aux);
						tmp = tmp->next;
					}
					(*i)++;
				}
				else
					words[(*i)++] = ft_strdup(trim_process(tmp->token, find_type(tmp->token)));
			}
			else
			{
				if (tmp->next)
				{
					words[(*i)] = ft_strdup(tmp->token);
					tmp = tmp->next;
					while (tmp && is_word(tmp->type, 3))
					{
						aux = ft_strdup(words[(*i)]);
						free(words[(*i)]);
						words[(*i)] = ft_strjoin(aux, trim_process(tmp->token, find_type(tmp->token)));
						free(aux);
						tmp = tmp->next;
					}
					(*i)++;
				}
				else
					words[(*i)++] = ft_strdup(trim_process(tmp->token, find_type(tmp->token)));
			}
		}
		if (tmp && is_drd_case(tmp->type))
			tmp = move_two(tmp->next);
		if (tmp && is_rd_case(tmp->type))
			tmp = move_one(tmp->next);
		else
		{
			if (tmp && tmp->type != PIPE)
				tmp = tmp->next;
		}
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
	words = malloc(sizeof(char *) * (len + 1));
	if (!words)
	{
		ft_error_parse(1);
		exit(1);
	}
	process_tokens(tokens, &i, words);
	words[len] = NULL;
	return (words);
}
