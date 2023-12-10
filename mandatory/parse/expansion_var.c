/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:42:48 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/10 16:07:07 by dapaulin         ###   ########.fr       */
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
			if (is_fuckin_case(var[ft_strlen(tmp->var)], tmp->var[ft_strlen(tmp->var)]))
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
			if (is_fuckin_case(var[ft_strlen(tmp->var)], tmp->var[ft_strlen(tmp->var)]))
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
	char	*new2;
	char	*new1;

	j = 0;
	new2 = NULL;
	new1 = NULL;
	if ((ft_isdigit(str[(*i) + j])) || (str[(*i)] == 32 || str[(*i)] == '\0'))
	{
		*identify_break = 1;
		return (str);
	}
	while (has_variable(str[(*i) + j]))
		j++;
	if (j > 0)
		new1 = ft_substr(str, 0, (*i) - 1);
	else
		new1 = ft_substr(str, 0, (*i));
	(*i) += j;
	new2 = ft_strjoin(new1, &str[(*i)]);
	if (new1)
		free(new1);
	if (str)
		free(str);
	return (new2);
}

char	*get_str_expand(t_data *data, char *str)
{
	int		i;
	char	*value;
	char	*new_str;
	int		flag;
	char	*aux;
	int		identify_break;

	identify_break = 0;
	value = NULL;
	new_str = NULL;
	i = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			flag = flag ^ 1;
		if (str[i] == '\'' && flag == 0)
		{
			aux = ft_strchr(&str[++i], '\'');
			i += aux - &str[i] + 1;
		}
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

// char	*process_vars(t_data *data, char *words)
// {
// 	char	*aux;

// 	if (has_variable(data, words))
// 	{
// 		aux = words;
// 		words = get_str_expand(data, aux);
// 		free(aux);
// 	}
// 	return (words);
// }

// int	check_vars(t_data *data, char *words)
// {
// 	if (has_variable(data, words))
// 		return (TRUE);
// 	return (FALSE);
// }

// char	*revise_str(t_data *data, char *word)
// {

// }

char	*get_str_expand_process(char *str, char *var, char *value, int i)
{
	int		j;
	int		k;
	int		len;
	char	*new_str;

	k = 0;
	j = 0;
	len = ((ft_strlen(str) - ft_strlen(var)) + ft_strlen(value));
	new_str = malloc(sizeof(char) * len + 1);
	while (j++ < i && str[j] != '$')
		new_str[j] = str[j];
	if (ft_strncmp(&str[i], var, ft_strlen(var) + 1) == 0)
	{
		while (value[k] != '\0')
			new_str[j++] = value[k++];
	}
	i += ft_strlen(var);
	while (str[i] && str[i] != '\0')
		new_str[j++] = str[i++];
	return (new_str);
}