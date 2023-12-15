/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:42:48 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/15 17:08:40 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*join_strings(t_data *data, char *str, int *i, int must_increment)
{
	char	*new_str[3];
	char	*value;

	new_str[0] = ft_substr(str, 0, (*i) - 1);
	value = get_var_value(data, &str[(*i)], i);
	new_str[1] = ft_strjoin(new_str[0], value);
	if (must_increment)
		++(*i);
	new_str[2] = ft_strjoin(new_str[1], &str[(*i)]);
	if (new_str[0])
		free(new_str[0]);
	if (new_str[1])
		free(new_str[1]);
	if (value)
		free(value);
	return (new_str[2]);
}

char	*dont_find_variable_expand(char *str, int *i, int *identify_break)
{
	int		j;
	char	*new_str[2];

	j = 0;
	new_str[0] = NULL;
	new_str[1] = NULL;
	if ((ft_isdigit(str[(*i) + j])) || (str[(*i)] == 32 || str[(*i)] == '\0'))
	{
		*identify_break = 1;
		return (str);
	}
	while (has_variable(str[(*i) + j]))
		j++;
	if (j > 0)
		new_str[0] = ft_substr(str, 0, (*i) - 1);
	else
		new_str[0] = ft_substr(str, 0, (*i));
	(*i) += j;
	new_str[1] = ft_strjoin(new_str[0], &str[(*i)]);
	if (new_str[0])
		free(new_str[0]);
	return (new_str[1]);
}

void	check_quotes(int *flag, int *i, char *str)
{
	char	*aux;

	aux = NULL;
	if (str[(*i)] == '\"')
		*flag = (*flag) ^ 1;
	if (str[*i + 1] && str[(*i)] == '\'' && (*flag) == 0)
	{
		aux = ft_strchr(&str[++(*i)], '\'');
		if (aux)
			*i += aux - &str[(*i)] - 1;
	}
}

char	*get_name(t_token **tokens)
{
	t_token	**tmp;
	char	*new;
	char	*aux;

	tmp = tokens;
	new = trim_process((*tmp)->token, find_type((*tmp)->token));
	if (*tmp)
	{
		if ((*tmp)->type == QUOTED_WORD)
		{
			aux = new;
			new = exec_trim_process(tmp, new);
			if (aux)
				free(aux);
		}
		else
		{
			if (new)
				free(new);
			new = exec_trim_process(tmp, (*tmp)->token);
		}
	}
	return (new);
}
