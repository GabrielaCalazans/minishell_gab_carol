/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:12:20 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/28 20:17:40 by gacalaza         ###   ########.fr       */
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
		exit (1);
	}
	token = ft_substr(str, 0, len);
	if (check == 1)
		type = find_type(&str[i]);
	else
		type = QUOTED_WORD;
	newnode = createnode(token, type);
	return (newnode);
}

	// if (find_type(&str[0]) == 12 || find_type(&str[0]) == 13)
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
	return (newnode);
}

int	sub_creating_token(t_data *data, t_token *newnode, int check, int i, int back)
{
	if (check == WORD)
	{
		newnode = create_word_token(&data->prompt_in[i],
				word_len(&data->prompt_in[i], back), 1);
		if (!newnode)
			return (C_ERROR);
		ft_add_back(&data->tokens, newnode);
	}
	if (check == QUOTE_DOUBLE || check == QUOTE_SINGLE)
	{
		newnode = create_word_token(&data->prompt_in[i],
				qword_len(&data->prompt_in[i], check, back), 2);
		if (!newnode)
			return (C_ERROR);
		ft_add_back(&data->tokens, newnode);
	}
	if (check > 0 && !is_word_q(check))
	{
		newnode = create_token(&data->prompt_in[i]);
		if (!newnode)
			return (C_ERROR);
		ft_add_back(&data->tokens, newnode);
	}
	return (C_SUCCESS);
}

void	sub_start_tokens(t_data *data, t_token *newnode, int check, int i)
{
	int	back;

	back = 0;
	while (data->prompt_in[i] != '\0' && data->prompt_in[i])
	{
		check = find_type(&data->prompt_in[i]);
		if (check == BACKSLASH)
		{
			back = 1;
			check = WORD;
		}
		if (check == WORD)
		{
			if (sub_creating_token(data, newnode, check, i, back))
				break ;
			i += word_len(&data->prompt_in[i], back);
			back = 0;
		}
		if (check == QUOTE_DOUBLE || check == QUOTE_SINGLE)
		{
			check = find_type(&data->prompt_in[i]);
			if (sub_creating_token(data, newnode, check, i, back))
				break ;
			i += qword_len(&data->prompt_in[i], check, back);
		}
		if (check > 0 && !is_word_q(check))
		{
			if (sub_creating_token(data, newnode, check, i, back))
				break ;
			if (ft_lensize(&data->prompt_in[i]))
				i += ft_lensize(&data->prompt_in[i]);
			else
				i++;
		}
	}
}

void	start_token(t_data *data)
{
	int		check;
	int		i;
	t_token	*newnode;

	i = 0;
	check = 0;
	newnode = NULL;
	if (!data->prompt_in)
	{
		printf("NO STR");
		return ;
	}
	sub_start_tokens(data, newnode, check, i);
	printlist(data->tokens, 1);
}
