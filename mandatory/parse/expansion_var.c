/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:42:48 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/17 18:35:06 by gacalaza         ###   ########.fr       */
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
	char	*aux;
	int		j;

	i = 0;
	flag = 0;
	while (str && str[i] != '\0')
	{
		check_quotes(&flag, &i, str);
		if (str[i] == '$')
		{
			aux = str;
			j = i;
			if (aux[++i] == '?')
			{
				str = join_strings(data, aux, &i, 1);
				if (aux)
					free(aux);
			}
			else if (can_expand(data, &aux[i]))
			{
				str = join_strings(data, aux, &i, 0);
				if (aux)
					free(aux);
			}
			else if (!aux[i])
				i++;
			else
			{
				str = dont_find_variable_expand(aux, &i);
				if (aux)
					free(aux);
				if ((size_t)i > ft_strlen(str))
				{
					i = 0;
					continue ;
				}
			}
			i = j;
		}
		i++;
	}
	return (str);
}

// char	*get_str_expand(t_data *data, char *str, char *aux)
// {
// 	int		i;
// 	int		j;

// 	i = -1;
// 	while (str && str[++i] != '\0')
// 	{
// 		check_quotes(&i, str);
// 		if (str[i] == '$')
// 		{
// 			j = i;
// 			if (aux[++i] == '?')
// 				str = join_strings(data, aux, &i, 1);
// 			else if (can_expand(data, &aux[i]))
// 				str = join_strings(data, aux, &i, 0);
// 			else if (!aux[i])
// 				i++;
// 			else
// 				str = dont_find_variable_expand(aux, &i);
// 			if ((size_t)i > ft_strlen(str) && aux[i - 1])
// 				i = 0;
// 			else
// 				i = j;
// 		}
// 	}
// 	return (str);
// }
