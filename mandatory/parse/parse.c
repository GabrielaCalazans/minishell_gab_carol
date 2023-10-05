/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:42:19 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/05 16:56:31 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	parse_big_str(char *str)
// {
// 	int	pipe;
// 	if (n_pipes(str) > 0)
// }

int	has_pipe(char *str)
{
	while (*str)
	{
		if (*str == '|')
			return (1);
		str++;
	}
	return (0);
}

int	n_pipes(char *str)
{
	int	pipes;

	pipes = 0;
	while (*str)
	{
		if (*str == '|')
			pipes++;
		str++;
	}
	return (pipes);
}

// int	main(void)
// {
// 	printf("%d\n", n_pipes("Hhello|o asdam|skdm|ka"));
// 	return (0);
// }