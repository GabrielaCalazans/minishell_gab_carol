/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_five.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:25:07 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/10 18:25:28 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
