/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:08:47 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/09 17:00:24 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	finalizepipe(t_data *data, t_params *ptr)
{
	t_rdct	*newnode;

	newnode = createnode_rdct(ptr->files, ptr->redirects, ptr->len);
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
	ptr->len = has_rdct_yet(temp->next);
}

void	processredirect(t_token *temp, t_params *ptr)
{
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
	ptr->len = has_rdct_yet(temp);
	while (temp)
	{
		if ((temp->type == PIPE || !has_pipe_yet(temp)) && !has_rdct_yet(temp))
		{
			ptr->files[ptr->i] = NULL;
			finalizepipe(data, ptr);
			ptr->inside_pipe = 1;
		}
		if (ptr->inside_pipe == 1)
		{
			processclean(temp, ptr);
			if (ptr->len < 1)
				break ;
		}
		if (temp->type == REDIRECT_IN || temp->type == REDIRECT_OUT)
			processredirect(temp, ptr);
		temp = temp->next;
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
	printlist(data->rdct, 2);
}

// void	create_redirect_lst(t_data *data)
// {
// 	t_token	*temp;
// 	char	**files;
// 	int		*redirects;
// 	int		inside_pipe;
// 	int		len;
// 	int		i;

// 	i = 0;
// 	inside_pipe = 0;
// 	redirects = NULL;
// 	files = NULL;
// 	if (first_check(data->tokens))
// 	{
// 		ft_error_redirect(C_ERROR);
// 		return ;
// 	}
// 	temp = data->tokens;
// 	len = has_rdct_yet(temp);
// 	while (temp)
// 	{
// 		if ((temp->type == PIPE || !has_pipe_yet(temp)) && !has_rdct_yet(temp))
// 		{
// 			files[i] = NULL;
// 			finalizepipe(data, files, redirects, len);
// 			inside_pipe = 1;
// 		}
// 		if (inside_pipe == 1)
// 		{
// 			if (len > 0)
// 				files = freearray(files);
// 			free(redirects);
// 			redirects = NULL;
// 			files = NULL;
// 			len = has_rdct_yet(temp->next);
// 			if (len < 1)
// 				break ;
// 			i = 0;
// 			inside_pipe = 0;
// 		}
// 		if (temp->type == REDIRECT_IN || temp->type == REDIRECT_OUT)
// 		{
// 			if (inside_pipe == 0)
// 			{
// 				redirects = malloc(sizeof (int) * (len + 1));
// 				files = malloc(sizeof (char **) * (len + 1));
// 				if (!redirects || !files)
// 				{
// 					printf("Error malloc: create_redirect_lst 1");
// 					return ;
// 				}
// 				inside_pipe = 3;
// 			}
// 			if (i < len)
// 			{
// 				redirects[i] = temp->type;
// 				files[i] = find_file_name(temp->next);
// 				i++;
// 			}
// 		}
// 		temp = temp->next;
// 	}
// 	if (redirects)
// 		free(redirects);
// 	if (files)
// 		files = freearray(files);
// 	printlist(data->rdct, 2);
// }
