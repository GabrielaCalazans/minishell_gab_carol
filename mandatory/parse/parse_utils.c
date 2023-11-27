/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:14:38 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/27 20:27:25 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_rd_case(int type)
{
	if (type == REDIRECT_IN)
		return (TRUE);
	if (type == REDIRECT_OUT)
		return (TRUE);
	return (FALSE);
}

int	is_drd_case(int type)
{
	
	if (type == HEREDOC)
		return (TRUE);
	if (type == APPEND)
		return (TRUE);
	return (FALSE);
}

int	is_word(int type, int check)
{
	if (check == 1)
	{
		if (type == WORD)
			return (TRUE);
		if (type == EXIT_STATUS)
			return (TRUE);
	}
	if (check == 2)
	{
		if (type != REDIRECT_IN && type != REDIRECT_OUT
			&& type != HEREDOC && type != APPEND
			&& type != C_SPACE)
			return (TRUE);
	}
	return (FALSE);
}

void	print_array(char **array, char *type)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		printf("%s[%i]: %s\n", type, i, array[i]);
		i++;
	}
	printf("\n");
}
