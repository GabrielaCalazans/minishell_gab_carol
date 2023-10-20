/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:08:47 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/20 16:59:55 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*take_quoted_name(t_token *tokens, int len)
{
	char	*name;
	t_token	*temp;
	size_t	word_size;

	temp = tokens->next;
	if (!has_another_quote(tokens, tokens->type))
	{
		ft_error_redirect(2);
		return (NULL);
	}
	word_size = quoted_word_size(temp, len);
	name = ft_strdup(temp->token);
	name = get_name_quoted(temp, name, len);
	if (ft_strlen(name) != word_size)
	{
		ft_error_redirect(3);
		return (NULL);
	}
	return (name);
}

char	*find_file_name(t_token *tokens)
{	
	t_token	*temp;

	temp = tokens;
	if (check_file_name(tokens))
	{
		ft_error_redirect(4);
		return (NULL);
	}
	while (temp)
	{
		if (temp->type == C_SPACE || temp->type == H_TAB)
		{
			while (temp->type == C_SPACE || temp->type == H_TAB)
				temp = temp->next;
		}
		if (temp->type == QUOTE_DOUBLE || temp->type == QUOTE_SINGLE)
			return (take_quoted_name(temp,
					has_another_quote(temp, temp->type)));
		if (temp->type == WORD)
			return (ft_strdup(temp->token));
		temp = temp->next;
	}
	ft_error_redirect(4);
	return (NULL);
}

void	sub_create_redirect_lst(t_data *data, t_token *token)
{
	t_rdct	*newnode;

	newnode = createnode_rdct(find_file_name(token->next), token->type);
	ft_add_back_rdct(&data->rdct, newnode);
}

void	create_redirect_lst(t_data *data)
{
	t_token	*temp;

	if (first_check(data->tokens))
	{
		ft_error_redirect(C_ERROR);
		return ;
	}
	temp = data->tokens;
	while (temp)
	{
		if (temp->type == 1 || temp->type == 2)
			sub_create_redirect_lst(data, &*temp);
		temp = temp->next;
	}
	printlist(data->rdct, 2);
}
