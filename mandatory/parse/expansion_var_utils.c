/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:42:48 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/10 16:39:46 by dapaulin         ###   ########.fr       */
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
	if (str)
		free(str);
	return (new_str[1]);
}

void	check_quotes(int *flag, int *i, char *str)
{
	char	*aux;

	aux = NULL;
	if (str[(*i)] == '\"')
		*flag = (*flag) ^ 1;
	if (str[(*i)] == '\'' && (*flag) == 0)
	{
		aux = ft_strchr(&str[++(*i)], '\'');
		*i += aux - &str[(*i)] + 1;
	}
}
