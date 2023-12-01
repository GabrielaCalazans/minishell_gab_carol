/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:41:14 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/01 11:41:18 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	*ft_intdup(int *array, int size)
{
	int		*array_copy;
	int		i;

	if (array == NULL)
		return (NULL);
	i = 0;
	array_copy = (int *)malloc(sizeof(int) * size);
	if (array_copy == NULL)
		return (NULL);
	while (i < size)
	{
		array_copy[i] = array[i];
		i++;
	}
	return (array_copy);
}
