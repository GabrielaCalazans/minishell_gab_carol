/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:42:48 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/09 17:49:51 by gacalaza         ###   ########.fr       */
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
	while (tmp)
	{
		if (ft_strncmp(tmp->var, var, ft_strlen(tmp->var)) == 0)
		{
			if (is_fuckin_case(var[ft_strlen(tmp->var)], tmp->var[ft_strlen(tmp->var)]))
			{
				(*i) += ft_strlen(tmp->var);
				return (tmp->value);
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
	int		j;
	char	*value;
	char	*new_str;
	int		flag;
	char	*aux;

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
			{
				new_str = ft_substr(str, 0, i - 1);
				value = ft_itoa(data->exit_code);
				new_str = ft_strjoin(new_str, value);
				str = ft_strjoin(new_str, &str[++i]);
				free(value);
			}
			else if (can_expand(data, &str[i]))
			{
				new_str = ft_substr(str, 0, i - 1);
				value = get_var_value(data, &str[i], &i);
				new_str = ft_strjoin(new_str, value);
				str = ft_strjoin(new_str, &str[i]);
			}
			else
			{
				j = 0;
				// printf("STR:\n%c\n",str[i]);
				if (ft_isdigit(str[i + j]))
					break ;
				if (str[i] == 32 || str[i] == '\0')
					break ;
				while (has_variable(str[i + j]))
					j++;
				if (j > 0)
					new_str = ft_substr(str, 0, i - 1);
				else
					new_str = ft_substr(str, 0, i);
				i += j;
				str = ft_strjoin(new_str, &str[i]);
			}
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