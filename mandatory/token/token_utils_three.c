/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:11:09 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/01 16:15:47 by gacalaza         ###   ########.fr       */
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

int	find_type(char *str)
{
	if (0 < is_redirect(*str))
		return (is_heredoc(str, is_redirect(*str)));
	if (0 < is_pipe(*str))
		return (is_pipe(*str));
	if (0 < is_flag(str))
		return (is_flag(str));
	if (0 < is_dollar(str))
		return (is_dollar(str));
	if (0 < is_slash(*str))
		return (is_slash(*str));
	if (0 < is_quote(*str))
		return (is_quote(*str));
	if (0 < is_space(*str))
		return (is_space(*str));
	else
		return (WORD);
}

// Handle the error appropriately
t_tk_p	*inicialize_tokenparams(void)
{
	t_tk_p	*params;

	params = (t_tk_p *)malloc(sizeof(t_tk_p));
	if (!params)
	{
		printf("Error malloc: initialize_tokenparams");
		exit(1);
	}
	params->i = 0;
	params->type = 0;
	params->check = 0;
	params->back = 0;
	return (params);
}
