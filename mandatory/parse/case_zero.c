/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_zero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:06:03 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/09 19:48:19 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	nb_words(t_token *tokens)
{
	t_token	*tmp;
	int		words;

	tmp = tokens;
	words = 0;
	while (tmp && tmp != NULL && tmp->type != PIPE)
	{
		if (is_word(tmp->type, 2))
		{
			while (tmp && tmp != NULL && is_word(tmp->type, 3))
				tmp = tmp->next;
			words++;
		}
		if (tmp && tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return (words);
}

char	**get_words(t_token *tokens, int len)
{
	char	**words;
	char	*aux;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	aux = NULL;
	words = ft_calloc((len + 1), sizeof(char *));
	if (!words)
		ft_error_parse(1);
	while (tmp && tmp->type != PIPE)
	{
		if (is_word(tmp->type, 2))
		{
			if (tmp->type == QUOTED_WORD)
			{
				if (tmp->next)
				{
					words[i] = ft_strdup(trim_process(tmp->token, find_type(tmp->token)));
					tmp = tmp->next;
					while (tmp && is_word(tmp->type, 3))
					{
						aux = ft_strdup(words[i]);
						free(words[i]);
						words[i] = ft_strjoin(aux, trim_process(tmp->token, find_type(tmp->token)));
						free(aux);
						tmp = tmp->next;
					}
					i++;
				}
				else
					words[i++] = ft_strdup(trim_process(tmp->token, find_type(tmp->token)));
			}
			else
			{
				if (tmp->next)
				{
					words[i] = ft_strdup(tmp->token);
					tmp = tmp->next;
					while (tmp && is_word(tmp->type, 3))
					{
						aux = ft_strdup(words[i]);
						free(words[i]);
						words[i] = ft_strjoin(aux, trim_process(tmp->token, find_type(tmp->token)));
						free(aux);
						tmp = tmp->next;
					}
					i++;
				}
				else
					words[i++] = trim_process(tmp->token, find_type(tmp->token));
			}
		}
		if (tmp && tmp->type != PIPE)
			tmp = tmp->next;
	}
	words[i] = NULL;
	return (words);
}
