/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:58:55 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/01 15:51:13 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	backs_case(t_tk_p *p)
{
	if (p->check == BACKSLASH)
	{
		p->back = 1;
		p->check = WORD;
	}
}

void	def_len(t_data *data, t_tk_p *p, int check)
{
	if (check == 1)
	{
		if (ft_lensize(&data->prompt_in[p->i]))
			p->i += ft_lensize(&data->prompt_in[p->i]);
		else
			p->i++;
	}
	if (check == 2)
	{
		p->i += word_len(&data->prompt_in[p->i], p->back);
		p->back = 0;
	}
}
