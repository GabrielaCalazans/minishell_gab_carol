/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:32:37 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/26 22:12:09 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_triming(char const *s1, char const *set)
{
	size_t	size_s1;
	char	*newstr;

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

	name = ft_strdup(word);
	printf("type:%d\n", type);
	if (type == QUOTE_DOUBLE)
		name = ft_triming(name, "\"");
	if (type == QUOTE_SINGLE)
		name = ft_triming(name, "\'");
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
