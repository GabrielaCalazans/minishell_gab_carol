/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:14:38 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/26 22:04:43 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_cmd(char **words)
{
	char	*cmd;

	cmd = ft_strdup(words[0]);
	return (cmd);
}

char	**get_args(char **words, int len)
{
	char	**args;

	args = NULL;
	if (len > 1)
		return (ft_arraydup((&words[1])));
	return (args);
}

int	has_d_redirec_p(t_token *tokens)
{
	t_token	*temp;
	int		r_rdrcts;

	temp = tokens;
	r_rdrcts = 0;
	while (temp)
	{
		if (temp->type == HEREDOC || temp->type == APPEND)
			r_rdrcts++;
		if (temp->type == PIPE)
			break ;
		temp = temp->next;
	}
	return (r_rdrcts);
}

void	*ft_error_parse(int error)
{
	if (error == 1)
		printf("erro malloc\n");
	else if (error == 2)
		printf("DEU RUIM.\n");
	else if (error == 3)
		printf("ERROR! Missing quote\n");
	else if(error == 5)
		printf("ELSE\n");
	else if (error == 6)
		printf("ERROR! Missing backslash key\n");
	else
	{
		printf("undefined error\n");
	}
	return (NULL);
}
