/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:12:20 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/03 22:17:44 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	word_len(char *str)
{
	int	len;

	len = 0;
	while (*str && find_type(str) == 10)
	{
		len++;
		str++;
	}
	return (len);
}

t_token	*create_word_token(char *str, int len)
{
	t_token	*newnode;
	char	*token;
	char	*type;
	int		i;

	i = 0;
	token = ft_substr(str, 0, len);
	type = define_type(&str[i]);
	newnode = createnode(token, type);
	return (newnode);
}

t_token	*create_token(char *str)
{
	t_token	*newnode;
	char	*token;
	char	*type;
	int		i;
	int		len;

	i = 0;
	len = 1;
	if (find_type(&str[i]) == 12 || find_type(&str[i]) == 13)
		len += 1;
	token = ft_substr(str, 0, len);
	type = define_type(&str[i]);
	newnode = createnode(token, type);
	return (newnode);
}

void	sub_start_tokens(t_data *data, t_token *newnode, int check)
{
	int	i;

	i = 0;
	while (data->prompt_in[i] != '\0' && data->prompt_in[i])
	{
		check = find_type(&data->prompt_in[i]);
		if (check == 10)
		{
			newnode = create_word_token(&data->prompt_in[i],
					word_len(&data->prompt_in[i]));
			if (!newnode)
				break ;
			ft_add_back(&data->tokens, newnode);
			i += word_len(&data->prompt_in[i]);
		}
		if (check > 0 && check != 10)
		{
			newnode = create_token(&data->prompt_in[i]);
			if (!newnode)
				break ;
			ft_add_back(&data->tokens, newnode);
			i++;
		}
	}
}

void	start_token(t_data *data)
{
	int		check;
	t_token	*newnode;

	check = 0;
	newnode = NULL;
	if (!data->prompt_in)
	{
		printf("NO STR");
		return ;
	}
	sub_start_tokens(data, newnode, check);
	lexer(data);
	printlist(data->tokens);
	ft_clear(&data->tokens);
}

// t_token	create_lst(char *str, t_token	**tokens)
// {
// 	int		check;
// 	int		i;
// }
