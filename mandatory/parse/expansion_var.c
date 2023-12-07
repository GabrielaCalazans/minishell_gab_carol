/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:42:48 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/06 18:08:44 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// PENSAR COMO RETIRAR AS ASPAS DUPLAS EM CASO DE VARIAVEL EXPANSÃO
// INDEX ṔARA STRUCTS DE CMD E RDCT
int	can_expand(t_data *data, char *var)
{
	t_env	*tmp;

	tmp = data->env_node;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, var, ft_strlen(tmp->var) + 1))
			tmp = tmp->next;
		else
			return (1);
	}
	return (0);
}

int	has_variable(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (can_expand(data, &str[i]))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

char	*get_var_value(t_data *data, char *var)
{
	t_env	*tmp;

	tmp = data->env_node;
	while (tmp)
	{
		if ((ft_strncmp(tmp->var, var, ft_strlen(tmp->var) + 1)) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

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
	while (j++ < i)
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

char	*get_str_expand(t_data *data, char *str)
{
	int		i;
	char	*value;

	value = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (can_expand(data, &str[++i]))
			{
				printf("VALUE i: %i", i);
				value = get_var_value(data, &str[i]);
				str = get_str_expand_process(str, &str[i], value, i);
			}
		}
		i++;
	}
	return (str);
}

char	**process_vars(t_data *data, char **words)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
	{
		if (has_variable(data, words[i]))
			words[i] = get_str_expand(data, words[i]);
		i++;
	}
	return (words);
}

int	check_vars(t_data *data, char **words)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
	{
		if (has_variable(data, words[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

// char	*revise_str(t_data *data, char *word)
// {

// }
