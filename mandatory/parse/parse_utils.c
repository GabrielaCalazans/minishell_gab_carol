/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:14:38 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/08 20:23:39 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cmd_pipe(t_data *data, int index)
{
	t_token	*tmp;
	char	**all_words;

	tmp = data->tokens;
	all_words = get_all_words(data->tokens);
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->next == NULL)
		{
			finalizepipe_cmd(data, all_words, index);
			if (tmp->next != NULL && all_words != NULL)
				all_words = fixwords(tmp->next, all_words);
			index++;
		}
		tmp = tmp->next;
	}
}

char	*get_cmd(char **words)
{
	char	*cmd;

	cmd = ft_strdup(words[0]);
	return (cmd);
}

char	**get_args(char **words, int len)
{
	char	**args;

	args = NULL;
	if (len > 1)
		return (ft_arraydup((&words[1])));
	return (args);
}

int	count_backs(int len, char *str)
{
	int	i;
	int	backs;

	i = 0;
	backs = 0;
	while (i < len)
	{
		if (str[i] == '\\' && str[i + 1] != '\\')
			backs++;
		if (i + 1 == len)
			break ;
		i++;
	}
	return (backs);
}

char	*process_backs(char *str, int len)
{
	int		i;
	int		j;
	int		backs;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = NULL;
	backs = count_backs(len, str);
	if (backs > 0)
	{
		new_str = malloc(sizeof (char) * (len - backs) + 1);
		if (!new_str)
			return_error_parse("malloc");
		while (j < (len - backs))
		{
			if (str[++i] == '\\')
				new_str[j++] = str[i];
			else
				new_str[j++] = str[i];
		}
		new_str[j] = '\0';
	}
	return (new_str);
}
