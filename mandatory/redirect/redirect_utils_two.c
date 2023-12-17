/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:38:24 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/16 16:39:53 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_file_name(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (tokens == NULL)
		return (ERROR_R);
	while (temp)
	{
		if (temp->type == SPACE_E || temp->type == H_TAB)
		{
			while (temp->type == SPACE_E || temp->type == H_TAB)
				temp = temp->next;
		}
		if (is_syntax_error(temp->type) && is_special_case(temp->type, 1))
			return (ERROR_R);
		if (temp->type == WORD || temp->type == QUOTED_WORD
			|| is_special_case(temp->type, 2))
			break ;
		temp = temp->next;
	}
	return (SUCESS_S);
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

char	*exec_trim_process(t_token **tmp, char *value)
{
	char	*new;
	char	*aux[2];

	new = ft_strdup(value);
	(*tmp) = (*tmp)->next;
	while ((*tmp) && is_word((*tmp)->type, 3))
	{
		aux[0] = new;
		aux[1] = trim_process((*tmp)->token, find_type((*tmp)->token));
		new = ft_strjoin(aux[0], aux[1]);
		if (aux[0])
			free(aux[0]);
		if (aux[1])
			free(aux[1]);
		(*tmp) = (*tmp)->next;
	}
	return (new);
}
