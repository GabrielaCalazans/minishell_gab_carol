/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:42:19 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/15 20:25:41 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	finalizepipe_cmd(t_data *data, char	**all_words, int index)
{
	t_cmd	*newnode;
	char	**cmd;

	cmd = NULL;
	if (all_words)
	{
		cmd = ft_arraydup(all_words);
		newnode = createnode_cmd(cmd, index);
	}
	else
		newnode = createnode_cmd(NULL, index);
	ft_add_back_cmd(&data->cmd, newnode);
	freearray(cmd);
}

char	**fixwords(t_token *tokens, char **words)
{
	if (words)
		freearray(words);
	words = get_all_words(tokens);
	return (words);
}

char	**get_all_words(t_token *tokens)
{
	char	**all_words;
	int		check;

	check = 0;
	all_words = NULL;
	if (has_rdrct_pipe(tokens))
		check = 1;
	if (has_d_redirec_p(tokens))
		check += 2;
	if (check == 0)
		all_words = get_words(tokens, nb_words(tokens));
	if (check == 1)
		all_words = get_words_one(tokens);
	if (check == 2)
		all_words = get_words_two(tokens);
	if (check == 3)
		all_words = get_words_three(tokens);
	if (!all_words)
		return (NULL);
	return (all_words);
}

char	**treat_backs(char **words)
{
	int	i;

	i = 0;
	if (words)
	{
		while (words[i] != NULL)
		{
			if (ft_strchr(words[i], '\\') != NULL && *words[i] != '\0')
				words[i] = process_backs(words[i], ft_strlen(words[i]));
			i++;
		}
	}
	return (words);
}

void	parsing_it(t_data *data)
{
	char	**all_words;
	int		index;

	index = 0;
	if (has_pipe(data->tokens) > 0)
		cmd_pipe(data, index);
	else
	{
		all_words = get_all_words(data->tokens);
		if (all_words != NULL)
			all_words = treat_backs(all_words);
		if (all_words == NULL)
			finalizepipe_cmd(data, NULL, index);
		if (all_words != NULL)
			finalizepipe_cmd(data, all_words, index);
		if (all_words != NULL)
			freearray(all_words);
	}
}
