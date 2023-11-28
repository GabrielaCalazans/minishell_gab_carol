/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:11:09 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/28 20:22:19 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*cont_def_type(int i)
{
	if (i == 8)
		return (ft_strdup("double_quote"));
	if (i == 9)
		return (ft_strdup("single_quote"));
	if (i == 10)
		return (ft_strdup("word"));
	if (i == 11)
		return (ft_strdup("space"));
	if (i == 12)
		return (ft_strdup("append"));
	if (i == 13)
		return (ft_strdup("heredoc"));
	return ("error");
}

char	*define_type(char *str)
{
	int	i;

	i = find_type(str);
	if (i == 1)
		return (ft_strdup("redirect_in"));
	if (i == 2)
		return (ft_strdup("redirect_out"));
	if (i == 3)
		return (ft_strdup("pipe"));
	if (i == 4)
		return (ft_strdup("flag"));
	if (i == 5)
		return (ft_strdup("slash"));
	if (i == 6)
		return (ft_strdup("question"));
	if (i == 7)
		return (ft_strdup("dollar"));
	if (i > 7 && i < 14)
		return (cont_def_type(i));
	return ("error");
}

int	has_asquote_str(char *str, int type)
{
	int	i;

	i = 0;
	while (str[++i] != '\0')
	{
		if (type == is_quote(str[i]))
			return (i);
	}
	return (0);
}

int	is_thiscase(int type, char c)
{
	(void)c;
	if(type == WORD || type == BACKSLASH)
		return (TRUE);
	return (FALSE);
}

int	is_backs(char *str, int len, int type)
{
	if (type == BACKSLASH && str[len] != '\0')
		return (len + 1);
	if (type == BACKSLASH && str[len] == '\0')
	{
		ft_error_parse(6);
		exit(1);
	}
	return (0);
}

int	word_len(char *str, int back)
{
	int	len;
	int	type;

	len = 0;
	type = find_type(str);
	while (str[len] != '\0' && is_thiscase(type, str[len]))
	{
		if (type == BACKSLASH && str[len] != '\0')
			len = is_backs(str, len, type);
		if (type == is_quote(str[len]) && back == 0)
		{
			if (has_asquote_str(&str[len], type))
				len += has_asquote_str(&str[len], type) + 1;
			else
			{
				ft_error_redirect(3);
				exit (1);
			}
		}
		else
			len++;
		type = find_type(&str[len]);
	}
	return (len);
}

int	is_word_q(int check)
{
	if (check == WORD)
		return (TRUE);
	if (check == QUOTE_DOUBLE)
		return (TRUE);
	if (check == QUOTE_SINGLE)
		return (TRUE);
	return (FALSE);
}

int	qword_len(char *str, int type, int back)
{
	int	len;
	int	check;

	len = 0;
	check = 0;
	if (back == 1)
		return (1);
	while (str[len])
	{
		len++;
		check = find_type(&str[len]);
		if (type == check)
		{
			len++;
			return (len);
		}
		if (check == BACKSLASH)
		{
			len++;
		}
	}
	return (FALSE);
}
