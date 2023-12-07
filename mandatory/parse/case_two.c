/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 22:05:41 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/07 16:04:13 by ckunimur         ###   ########.fr       */
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
		else
		{
			if (tmp && tmp->next)
				tmp = tmp->next;
			else
				break ;
		}
	}
	return (words);
}

char	**get_words_two(t_token *tokens)
{
	t_token	*tmp;
	char	*aux;
	char	**words;
	int		i;
	int		len;

	i = 0;
	len = nb_words_dr(tokens);
	if (len < 1)
		return (NULL);
	tmp = tokens;
	words = malloc(sizeof(char **) * (len + 1));
	if (!words)
		ft_error_parse(1);
	while (tmp && tmp->type != PIPE)
	{
		if (i == 0 && tmp->type == 10)
			words[i++] = ft_strdup(tmp->token);
		else if (is_word(tmp->type, 2) && i != 0)
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
					words[i++] = ft_strdup(trim_process(tmp->token, find_type(tmp->token)));
			}
		}
		if (is_drd_case(tmp->type))
			tmp = move_two(tmp->next);
		else
		{
			if (tmp && tmp->type != PIPE)
				tmp = tmp->next;
		}
	}
	words[i] = NULL;
	return (words);
}
