/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:11:09 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/28 15:14:08 by gacalaza         ###   ########.fr       */
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

int	qword_len(char *str, int type)
{
	int	len;

	len = 0;
	str++;
	while (*str)
	{
		len++;
		if (type == find_type(str))
		{
			len++;
			return (len);
		}
		str++;
	}
	return (FALSE);
}
