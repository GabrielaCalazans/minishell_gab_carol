/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:14:38 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/27 12:10:29 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_d_redirec_p(t_token *tokens)
{
	t_token	*temp;
	int		r_rdrcts;

	temp = tokens;
	r_rdrcts = 0;
	while (temp)
	{
		if (temp->type == HEREDOC || temp->type == APPEND)
			r_rdrcts++;
		if (temp->type == PIPE)
			break ;
		temp = temp->next;
	}
	return (r_rdrcts);
}

void	*ft_error_parse(int error)
{
	if (error == 1)
		printf("erro malloc\n");
	else if (error == 2)
		printf("DEU RUIM.\n");
	else if (error == 3)
		printf("ELSE\n");
	else if (error == 4)
		printf("ELSE\n");
	else
	{
		printf("undefined error\n");
	}
	return (NULL);
}

int	is_rd_case(int type)
{
	if (type == REDIRECT_IN)
		return (TRUE);
	if (type == REDIRECT_OUT)
		return (TRUE);
	return (FALSE);
}

int	is_drd_case(int type)
{
	if (type == HEREDOC)
		return (TRUE);
	if (type == APPEND)
		return (TRUE);
	return (FALSE);
}

int	is_word(int type, int check)
{
	if (check == 1)
	{
		if (type == WORD)
			return (TRUE);
		if (type == QUOTED_WORD)
			return (TRUE);
	}
	if (check == 2)
	{
		if (type == WORD)
			return (TRUE);
		if (type == QUOTED_WORD)
			return (TRUE);
		if (!is_special_case(type, 3))
			return (TRUE);
	}
	return (FALSE);
}

void	ft_clear_cmd(t_data *data)
{
	data->cmd = freearray(data->cmd);
	data->cmd = NULL;
	data->cmd_args = freearray(data->cmd_args);
	data->cmd_args = NULL;
}

char	*trim_process(char *word, int type)
{
	char	*name;

	name = ft_strdup(word);
	if (type == QUOTE_DOUBLE)
		name = ft_strtrim(name, "\"");
	if (type == QUOTE_SINGLE)
		name = ft_strtrim(name, "\'");
	return (name);
}

char	**trim_quote(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		if (find_type(words[i]) == 8
			|| find_type(words[i]) == 9)
			words[i] = trim_process(words[i], find_type(words[i]));
		i++;
	}
	return (words);
}

void	get_cmd(t_data *data, char **words)
{
	int	len;
	int	check;

	len = ft_array_size(words);
	check = 0;
	ft_clear_cmd(data);
	if (len > 1)
	{
		if (find_type(words[0]) == 10 && find_type(words[1]) == 4)
		{
			data->cmd = ft_arraydup_size(words, 2);
			check = 1;
		}
		else
			data->cmd = ft_arraydup_size(words, 1);
	}
	if (check == 1 && len > 2)
		data->cmd_args = ft_arraydup(trim_quote(&words[2]));
	if (len > 1 && check == 0)
		data->cmd_args = ft_arraydup(trim_quote(&words[1]));
	if (len < 2)
		data->cmd = ft_arraydup_size(words, 1);
}
