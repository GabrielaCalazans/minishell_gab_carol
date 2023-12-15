/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:59:35 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/01 16:16:00 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	word_len(char *str, int back)
{
	int	len;
	int	type;

	len = 0;
	type = find_type(str);
	while (str[len] != '\0' && is_worbks_case(type, str[len]))
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

int	len_flag(char *str)
{
	int	len;

	len = 0;
	if (str[len] == '-')
	{
		len++;
		while (str[len] != '\0')
		{
			if (!ft_isalpha(str[len]))
				break ;
			len++;
		}
	}
	return (len);
}

int	len_var(char *str)
{
	int	len;

	len = 0;
	if (str[len] == '$')
	{
		len++;
		while (str[len] != '\0')
		{
			if (is_space(str[len]))
				break ;
			len++;
		}
	}
	return (len);
}

int	ft_lensize(char *str)
{
	int	i;

	i = 0;
	if (is_hd_c(str) || is_e_c(str))
		i += 2;
	if (is_flag(str))
		i = len_flag(str);
	if (is_dollar(str) == DOLLAR)
		i = len_var(str);
	return (i);
}
