/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:32:44 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/01 16:21:41 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_quotes(t_data *data)
{
	t_token	*tmp;
	int		check;

	tmp = data->tokens;
	check = 0;
	while (tmp)
	{
		if (is_a_quote(tmp->type))
			check = has_another_quote(tmp, tmp->type);
		if (check > 0)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

int	has_another_quote(t_token *tokens, int type)
{
	t_token	*temp;
	int		len;

	temp = tokens->next;
	len = 0;
	while (temp)
	{
		if (temp->type == type)
			return (len);
		len++;
		temp = temp->next;
	}
	return (FALSE);
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

int	has_d_redirec_p(t_token *tokens)
{
	t_token	*temp;
	int		r_rdrcts;

	temp = tokens;
	r_rdrcts = 0;
	while (temp)
	{
		if (temp->type == HEREDOC || temp->type == APPEND)
			r_rdrcts++;
		if (temp->type == PIPE)
			break ;
		temp = temp->next;
	}
	return (r_rdrcts);
}
