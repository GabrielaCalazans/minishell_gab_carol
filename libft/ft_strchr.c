/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:44:35 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/09 17:36:29 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	count;
	int	size;

	size = ft_strlen(str);
	count = 0;
	if ((unsigned char)c == '\0')
		return (&((char *)str)[ft_strlen(str)]);
	while (count < size)
	{
		if (str[count] == (unsigned char)c)
			return ((char *)str + count);
		count++;
	}
	if (*str == (unsigned char)c)
		return ((char *)str);
	return (NULL);
}
