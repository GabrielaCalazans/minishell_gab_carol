/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_five.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:25:07 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/30 19:58:19 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	len_flag(char *str)
{
	int	len;

	len = 0;
	if (str[len] == '-')
	{
		len++;
		while (str[len] != '\0')
		{
			if (!ft_isalpha(str[len]))
				break ;
			len++;
		}
	}
	return (len);
}

int	len_var(char *str)
{
	int	len;

	len = 0;
	if (str[len] == '$')
	{
		len++;
		while (str[len] != '\0')
		{
			if (is_space(str[len]))
				break ;
			len++;
		}
	}
	return (len);
}

int	ft_lensize(char *str)
{
	int	i;

	i = 0;
	if (is_hd_c(str) || is_e_c(str))
		i += 2;
	if (is_flag(str))
		i = len_flag(str);
	if (is_dollar(str) == DOLLAR)
		i = len_var(str);
	return (i);
}

// void	paramsclean(t_token *temp, t_tokenp *ptr)
// {
// 	if (ptr->len > 0)
// 		ptr->files = freearray(ptr->files);
// 	free(ptr->redirects);
// 	ptr->redirects = NULL;
// 	ptr->files = NULL;
// 	ptr->i = 0;
// 	ptr->inside_pipe = 0;
// 	ptr->len = has_rdct_yet(temp->next) + has_d_redirec_p(temp->next);
// }

// Handle the error appropriately

t_tk_p	*inicialize_tokenparams(void)
{
	t_tk_p	*params;

	params = (t_tk_p *)malloc(sizeof(t_tk_p));
	if (!params)
	{
		printf("Error malloc: initialize_tokenparams");
		exit(1);
	}
	params->i = 0;
	params->type = 0;
	params->check = 0;
	params->back = 0;
	return (params);
}
