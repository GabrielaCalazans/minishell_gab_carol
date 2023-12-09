/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:08:47 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/08 22:28:30 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	finalizepipe(t_data *data, t_params *ptr)
{
	t_rdct	*newnode;

	newnode = createnode_rdct(ptr->files, ptr->redirects, ptr->len, ptr->index);
	ft_add_back_rdct(&data->rdct, newnode);
}

void	processclean(t_token *temp, t_params *ptr)
{
	if (ptr->len > 0)
		ptr->files = freearray(ptr->files);
	free(ptr->redirects);
	ptr->redirects = NULL;
	ptr->files = NULL;
	ptr->i = 0;
	ptr->inside_pipe = 0;
	ptr->len = has_rdrct_pipe(temp) + has_d_redirec_p(temp);
}

void	processredirect(t_token *temp, t_params *ptr)
{
	//printf("PROCESS i:%i, len:%i", ptr->i, ptr->len);
	if (ptr->inside_pipe == 0)
	{
		ptr->redirects = malloc(sizeof (int) * (ptr->len + 1));
		ptr->files = malloc(sizeof (char **) * (ptr->len + 1));
		if (!ptr->redirects || !ptr->files)
		{
			printf("Error malloc: create_redirect_lst 1");
			return ;
		}
		ptr->inside_pipe = 3;
	}
	if (ptr->i < ptr->len)
	{
		ptr->redirects[ptr->i] = temp->type;
		ptr->files[ptr->i] = find_file_name(temp->next);
		ptr->i++;
	}
}

void	processtoken(t_data *data, t_token *temp, t_params *ptr)
{
	ptr->len = has_rdrct_pipe(temp) + has_d_redirec_p(temp);
	//printf("token:%s, len:%i\n", temp->token, temp->type);
	while (temp)
	{
		//printf("ENTREI%s, type:%i\n", temp->token, temp->type);
		if ((temp->type == PIPE || !has_pipe(temp)) && (!has_rdrct_pipe(temp)
				&& !has_d_redirec_p(temp)))
		{
			if (ptr->files)
				ptr->files[ptr->i] = NULL;
			finalizepipe(data, ptr);
			ptr->inside_pipe = 1;
			if (temp->type == PIPE)
				ptr->index++;
		}
		// if (temp->prev != NULL && temp->next)
		temp = temp->next;
		if (ptr->inside_pipe == 1)
		{
			processclean(temp, ptr);
			if (ptr->len < 1)
				break ;
		}
		if (is_redrt_case(temp->type))
			processredirect(temp, ptr);
	}
}

void	create_redirect_lst(t_data *data)
{
	t_token		*temp;
	t_params	*params;

	if (first_check(data->tokens))
	{
		ft_error_redirect(C_ERROR);
		return ;
	}
	params = inicialize_rd_params();
	temp = data->tokens;
	processtoken(data, temp, params);
	if (params->redirects)
	{
		free(params->redirects);
		params->redirects = NULL;
	}
	if (params->files)
		params->files = freearray(params->files);
	free(params);
	//printlist(data->rdct, 2);
}
