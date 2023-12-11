/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:12:20 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/10 19:51:27 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_word_token(char *str, int len, int check)
{
	t_token	*newnode;
	char	*token;
	int		type;
	int		i;

	i = 0;
	if (len < 1 && check == 2)
	{
		ft_error_parse(3);
		return (NULL);
	}
	token = ft_substr(str, 0, len);
	if (check == 1)
		type = find_type(&str[i]);
	else
		type = QUOTED_WORD;
	newnode = createnode(token, type);
	free(token);
	return (newnode);
}

t_token	*create_token(char *str)
{
	t_token	*newnode;
	char	*token;
	int		type;
	int		len;

	len = 1;
	if (is_hd_c(str) || is_e_c(str))
		len += 1;
	if (is_flag(str))
		len = len_flag(str);
	if (is_dollar(str))
		len = len_var(str);
	token = ft_substr(str, 0, len);
	type = find_type(&str[0]);
	newnode = createnode(token, type);
	free(token);
	return (newnode);
}

int	sub_creating_token(t_data *data, t_token *newnode, t_tk_p *p)
{
	if (p->check == WORD)
	{
		newnode = create_word_token(&data->prompt_in[p->i],
				word_len(&data->prompt_in[p->i], p->back), 1);
		if (!newnode)
			return (C_ERROR);
		ft_add_back(&data->tokens, newnode);
	}
	if (p->check == QUOTE_DOUBLE || p->check == QUOTE_SINGLE)
	{
		newnode = create_word_token(&data->prompt_in[p->i],
				qword_len(&data->prompt_in[p->i], p->check, p->back), 2);
		if (!newnode)
			return (C_ERROR);
		ft_add_back(&data->tokens, newnode);
	}
	if (p->check > 0 && !is_word_q(p->check))
	{
		newnode = create_token(&data->prompt_in[p->i]);
		if (!newnode)
			return (C_ERROR);
		ft_add_back(&data->tokens, newnode);
	}
	return (C_SUCCESS);
}

void	sub_start_tokens(t_data *data, t_token *newnode, t_tk_p *p)
{
	while (data->prompt_in[p->i] != '\0' && data->prompt_in[p->i])
	{
		p->check = find_type(&data->prompt_in[p->i]);
		if (p->check == BACKSLASH)
			backs_case(p);
		if (p->check == WORD)
		{
			if (sub_creating_token(data, newnode, p))
				break ;
			def_len(data, p, 2);
		}
		if (p->check == QUOTE_DOUBLE || p->check == QUOTE_SINGLE)
		{
			p->check = find_type(&data->prompt_in[p->i]);
			if (sub_creating_token(data, newnode, p))
				break ;
			p->i += qword_len(&data->prompt_in[p->i], p->check, p->back);
		}
		if (p->check > 0 && !is_word_q(p->check))
		{
			if (sub_creating_token(data, newnode, p))
				break ;
			def_len(data, p, 1);
		}
	}
}

void	start_token(t_data *data)
{
	t_token	*newnode;
	t_tk_p	*params;

	newnode = NULL;
	params = inicialize_tokenparams();
	if (!data->prompt_in)
	{
		printf("NO STR");
		return ;
	}
	sub_start_tokens(data, newnode, params);
	free(params);
}
