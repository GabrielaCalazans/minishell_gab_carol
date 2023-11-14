/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:47:31 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/13 20:55:45 by gacalaza         ###   ########.fr       */
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
			words++;
		if (tmp->next && is_drd_case(tmp->type))
			tmp = move_two(tmp->next);
		if (tmp->next && is_rd_case(tmp->type))
			tmp = move_one(tmp->next);
		else
		{
			if (tmp->next)
				tmp = tmp->next;
			else
				break ;
		}
	}
	return (words);
}

// char	**get_words_t(t_token *tokens)
// {
// 	t_token	*tmp;
// 	int		i;
// 	char	**words;

// 	i = 0;
// 	tmp = tokens;
// 	words = malloc(sizeof(char **) * (nb_words_dr(tokens) + 1));
// 	if (!words)
// 		ft_error_parse(1);
// 	while (tmp && tmp->type != PIPE)
// 	{
// 		if (is_word(tmp->type, 2))
// 			words[i++] = ft_strdup(tmp->token);
// 		if (is_drd_case(tmp->type))
// 			tmp = move_drd(tmp->next);
// 		if (is_rd_case(tmp->type))
// 			tmp = move_rd(tmp->next);
// 		else
// 		{
// 			if (tmp->next)
// 				tmp = tmp->next;
// 			else
// 				break ;
// 		}
// 	}
// 	words[i] = NULL;
// 	return (words);
// }

void	process_tokens(t_token *tokens, int *i, char **words)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (is_word(tmp->type, 2))
			words[(*i)++] = ft_strdup(tmp->token);
		if (tmp && is_drd_case(tmp->type))
			tmp = move_two(tmp->next);
		if (tmp && is_rd_case(tmp->type))
			tmp = move_one(tmp->next);
		else
		{
			if (tmp->next)
				tmp = tmp->next;
			else
				break ;
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
