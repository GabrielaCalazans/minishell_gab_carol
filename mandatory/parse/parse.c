/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:42:19 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/30 19:18:29 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	finalizepipe_cmd(t_data *data, char	**all_words)
{
	t_cmd	*newnode;
	char	**cmd;
	int		len;

	if (!all_words)
	{
		ft_error_parse(5);
		return ;
	}
	len = ft_array_size(all_words);
	cmd = NULL;
	cmd = ft_arraydup(all_words);
	newnode = createnode_cmd(cmd);
	ft_add_back_cmd(&data->cmd, newnode);
}

char	**fixwords(t_token *tokens, char **words)
{
	if (words)
		freearray(words);
	words = get_all_words(tokens);
	if (!words)
		words = ft_error_parse(5);
	return (words);
}

void	cmd_pipe(t_data *data)
{
	t_token	*tmp;
	char	**all_words;

	tmp = data->tokens;
	all_words = get_all_words(data->tokens);
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->next == NULL)
		{
			finalizepipe_cmd(data, all_words);
			if (tmp->next != NULL)
				all_words = fixwords(tmp->next, all_words);
		}
		tmp = tmp->next;
	}
}

char	**get_all_words(t_token *tokens)
{
	char	**all_words;
	int		check;

	check = 0;
	all_words = NULL;
	if (has_redirect_pipe(tokens))
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
		ft_error_parse(2);
	return (all_words);
}

int	count_backs(int len, char *str)
{
	int	i;
	int	backs;

	i = 0;
	backs = 0;
	while(i < len)
	{
		if (str[i] == '\\' && str[i + 1] != '\\')
			backs++;
		if (i + 1 == len)
			break ;
		i++;
	}
	return (backs);
}

char	*process_backs(char *str)
{
	int		i;
	int		j;
	int		len;
	int		backs;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = NULL;
	len = ft_strlen(str);
	backs = count_backs(len, str);
	if (backs > 0)
	{
		new_str = malloc(sizeof (char) * (len - backs) + 1);
		if (!new_str)
		{
			perror("malloc");
			exit (1);
		}
		while (j < (len - backs))
		{
			if (str[i] == '\\')
			{
				i++;
				new_str[j] = str[i];
				j++;
			}
			else
			{
				new_str[j] = str[i];
				j++;
			}
			i++;
		}
		new_str[j] = '\0';
	}
	return (new_str);
}

char	**treat_backs(char **words)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
	{
		if (ft_strchr(words[i], '\\') != NULL)
			words[i] = process_backs(words[i]);
		i++;
	}
	return (words);
}

	// data->cmd = ft_arraydup(all_words);
void	parsing_it(t_data *data)
{
	char	**all_words;

	if (has_pipe(data) > 0)
		cmd_pipe(data);
	else
	{
		all_words = get_all_words(data->tokens);
		all_words = treat_backs(all_words);
		print_array(all_words, "all_words");
		finalizepipe_cmd(data, all_words);
	}
	printlist(data->cmd, 3);
}
