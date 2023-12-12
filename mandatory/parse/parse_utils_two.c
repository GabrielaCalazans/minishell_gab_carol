/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:14:38 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/12 01:24:35 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_triming(char const *s1, char const *set)
{
	size_t	size_s1;
	char	*newstr;

	if (ft_strlen(s1) == 0)
	{
		newstr = (char *)ft_calloc(sizeof(char), 1);
		return (newstr);
	}
	size_s1 = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (NULL);
	newstr = (char *)malloc(sizeof(char) * size_s1);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, &s1[1], size_s1);
	return (newstr);
}

char	*trim_process(char *word, int type)
{
	char	*name;
	char	*aux;

	aux = NULL;
	name = ft_strdup(word);
	if (type == QUOTE_DOUBLE)
	{
		aux = name;
		name = ft_triming(name, "\"");
		if (aux)
			free(aux);
	}
	if (type == QUOTE_SINGLE)
	{
		aux = name;
		name = ft_triming(name, "\'");
		if (aux)
			free(aux);
	}
	return (name);
}

char	**trim_quote(char **words)
{
	int	i;
	int	type;

	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		type = find_type(words[i]);
		if (type == 8 || type == 9)
			words[i] = trim_process(words[i], type);
		i++;
	}
	return (words);
}

void	*ft_error_parse(int error)
{
	if (error == 1)
		printf("erro malloc\n");
	else if (error == 2)
		printf("not a valid identifier\n");
	else if (error == 3)
		printf("ERROR! Missing quote\n");
	else if (error == 5)
		printf("ERROR! get_all_words\n");
	else if (error == 6)
		printf("ERROR! Missing backslash key\n");
	else
	{
		printf("undefined error\n");
	}
	return (NULL);
}

void	return_error_parse(char *str)
{
	perror(str);
	exit (1);
}
