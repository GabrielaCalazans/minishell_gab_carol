/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:38:24 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/10 15:03:22 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_file_name(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (tokens == NULL)
		return (C_ERROR);
	while (temp)
	{
		if (temp->type == C_SPACE || temp->type == H_TAB)
		{
			while (temp->type == C_SPACE || temp->type == H_TAB)
				temp = temp->next;
		}
		if (is_syntax_error(temp->type) && is_special_case(temp->type, 1))
			return (C_ERROR);
		if (temp->type == WORD || temp->type == QUOTED_WORD
			|| is_special_case(temp->type, 2))
			break ;
		temp = temp->next;
	}
	return (C_SUCCESS);
}

int	first_check(t_token *tokens)
{
	t_token	*temp;
	int		check;

	temp = tokens;
	check = 0;
	while (temp)
	{
		if ((temp->type == REDIRECT_IN || temp->type == REDIRECT_OUT))
		{
			if (temp->next)
			{
				temp = temp->next;
				check += check_file_name(temp);
			}
		}
		temp = temp->next;
	}
	return (check);
}

size_t	quoted_word_size(t_token *tokens, int len)
{
	size_t	word_size;
	t_token	*temp;
	int		i;

	i = 0;
	word_size = 0;
	temp = tokens;
	while (len > i && temp)
	{
		if (temp->type == QUOTE_DOUBLE || temp->type == QUOTE_SINGLE)
			break ;
		word_size += ft_strlen(temp->token);
		temp = temp->next;
		i++;
	}
	return (word_size);
}

char	*take_q_name(t_token *tokens)
{
	int		type;
	char	*name;

	type = find_type(tokens->token);
	name = ft_strdup(tokens->token);
	if (type == QUOTE_DOUBLE)
		name = ft_strtrim(name, "\"");
	if (type == QUOTE_SINGLE)
		name = ft_strtrim(name, "\'");
	return (name);
}

char	*get_name(t_token *tokens)
{
	t_token	*tmp;
	char	*new;
	char	*aux;

	tmp = tokens;
	new = NULL;
	aux = NULL;
	if (tmp->type == QUOTED_WORD)
	{
		if (tmp)
		{
			new = ft_strdup(trim_process(tmp->token, find_type(tmp->token)));
			tmp = tmp->next;
			while (tmp && is_word(tmp->type, 3))
			{
				aux = ft_strdup(new);
				free(new);
				new = ft_strjoin(aux, trim_process(tmp->token, find_type(tmp->token)));
				free(aux);
				tmp = tmp->next;
			}
		}
		else
		{
			new = ft_strdup(trim_process(tmp->token, find_type(tmp->token)));
		}
	}
	else
	{
		if (tmp)
		{
			new = ft_strdup(tmp->token);
			tmp = tmp->next;
			while (tmp && is_word(tmp->type, 3))
			{
				aux = ft_strdup(new);
				free(new);
				new = ft_strjoin(aux, trim_process(tmp->token, find_type(tmp->token)));
				free(aux);
				tmp = tmp->next;
			}
		}
		else
		{
			new = ft_strdup(trim_process(tmp->token, find_type(tmp->token)));
		}
	}
	return (new);
}
