/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:42:48 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/11 15:59:21 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_fuckin_case(char c, char a)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (0);
	else if (a == '\0')
		return (1);
	return (0);
}

int	can_expand(t_data *data, char *var)
{
	t_env	*tmp;

	tmp = data->env_node;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, var, ft_strlen(tmp->var)) == 0)
		{
			if (is_fuckin_case(var[ft_strlen(tmp->var)], \
				tmp->var[ft_strlen(tmp->var)]))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*get_var_value(t_data *data, char *var, int *i)
{
	t_env	*tmp;

	tmp = data->env_node;
	if (*var == '?')
		return (ft_itoa(data->exit_code));
	while (tmp)
	{
		if (ft_strncmp(tmp->var, var, ft_strlen(tmp->var)) == 0)
		{
			if (is_fuckin_case(var[ft_strlen(tmp->var)], \
				tmp->var[ft_strlen(tmp->var)]))
			{
				(*i) += ft_strlen(tmp->var);
				return (ft_strdup(tmp->value));
			}
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

int	has_variable(char c)
{
	if (ft_isalpha(c))
		return (TRUE);
	if (ft_isdigit(c))
		return (TRUE);
	if (c == 95)
		return (TRUE);
	return (FALSE);
}

char	*get_str_expand(t_data *data, char *str)
{
	int		i;
	int		flag;
	int		identify_break;

	i = 0;
	flag = 0;
	identify_break = 0;
	while (str[i] && str[i] != '\0')
	{
		check_quotes(&flag, &i, str);
		if (str[i] == '$')
		{
			if (str[++i] == '?')
				str = join_strings(data, str, &i, 1);
			else if (can_expand(data, &str[i]))
				str = join_strings(data, str, &i, 0);
			else
				str = dont_find_variable_expand(str, &i, &identify_break);
			if (identify_break)
				break ;
		}
		i++;
	}
	return (str);
}
