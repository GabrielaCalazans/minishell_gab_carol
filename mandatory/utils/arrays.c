/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:37:56 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/16 19:26:16 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**freearray(char **array)
{
	size_t	i;
	size_t	sizearray;

	if (!array)
		return (NULL);
	sizearray = 0;
	while (array[sizearray] != NULL)
	{
		sizearray++;
	}
	i = 0;
	if (i < sizearray)
	{
		while (array[i] && array[i] != NULL)
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
	}
	free(array);
	return (NULL);
}

int	ft_array_size(char **array)
{
	int		length;

	length = 0;
	if (array == NULL)
		return (length);
	while (array[length] != NULL)
		length++;
	return (length);
}

char	**ft_copy_array(char **array, int length)
{
	int		i;
	char	**array_copy;

	if (length < 1)
		return (NULL);
	array_copy = (char **)ft_calloc(sizeof(char *), (length + 1));
	if (array_copy == NULL)
		return (NULL);
	i = -1;
	while (++i < length)
	{
		if (array[i] != NULL)
		{
			array_copy[i] = ft_strdup(array[i]);
			if (array_copy[i] == NULL)
			{
				array_copy = freearray(array_copy);
				return (NULL);
			}
		}
		else
			array_copy[i] = NULL;
	}
	array_copy[length] = NULL;
	return (array_copy);
}

char	**ft_arraydup(char **array)
{
	int		length;

	if (array == NULL)
		return (NULL);
	length = ft_array_size(array);
	return (ft_copy_array(array, length));
}

char	**ft_arraydup_size(char **array, int size)
{
	if (array == NULL)
		return (NULL);
	return (ft_copy_array(array, size));
}
