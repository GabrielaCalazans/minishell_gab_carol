/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_four.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:16:35 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/09 17:00:00 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_redirect_pipe(t_token *tokens)
{
	t_token	*temp;
	int		redirects;

	temp = tokens;
	redirects = 0;
	while (temp)
	{
		if (temp->type == 1 || temp->type == 2)
			redirects++;
		if (temp->type == PIPE)
			break ;
		temp = temp->next;
	}
	return (redirects);
}

char	*find_file_name(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (check_file_name(tokens))
		return_error();
	while (temp)
	{
		if (temp->type == C_SPACE || temp->type == H_TAB)
		{
			while (temp->type == C_SPACE || temp->type == H_TAB)
				temp = temp->next;
		}
		if (temp->type == QUOTED_WORD)
			return (take_q_name(temp));
		if (temp->type == EXIT_STATUS)
			return (ft_strdup("0"));
		if (temp->type == WORD || temp->type == SLASH
			|| is_special_case(temp->type, 2))
			return (word_case(temp));
		temp = temp->next;
	}
	ft_error_redirect(4);
	return (NULL);
}

int	has_pipe_yet(t_token *tokens)
{
	t_token	*tmp;
	int		check;

	tmp = tokens;
	check = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			check++;
		tmp = tmp->next;
	}
	return (check);
}

int	has_rdct_yet(t_token *tokens)
{
	t_token	*tmp;
	int		check;

	tmp = tokens;
	check = 0;
	while (tmp)
	{
		if (tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OUT)
			check++;
		if (tmp->type == PIPE)
			break ;
		tmp = tmp->next;
	}
	return (check);
}

// Handle the error appropriately
t_params	*inicialize_rd_params(void)
{
	t_params	*params;

	params = (t_params *)malloc(sizeof(t_params));
	if (!params)
	{
		printf("Error malloc: initialize_rd_params");
		exit(1);
	}
	params->i = 0;
	params->len = 0;
	params->inside_pipe = 0;
	params->files = NULL;
	params->redirects = NULL;
	return (params);
}
