/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:51:16 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/01 18:53:15 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	maxlen(int args, int cmd)
{
	if (args > cmd)
		return (args);
	else
		return (cmd);
}

void	printlst_cmd(t_cmd *head)
{
	t_cmd	*temp;
	int		j;
	int		i;

	temp = head;
	j = 0;
	while (temp != NULL)
	{
		i = 1;
		printf("NODE[%i]-CMD: %s", j, temp->cmd[0]);
		if (temp->cmd[i] != NULL)
		{
			while (temp->cmd[i] != NULL)
			{
				printf(" ARGS: %s", temp->cmd[i]);
				i++;
			}
		}
		printf("\n");
		j++;
		temp = temp->next;
	}
}

void	printlst_rdct(t_rdct *head)
{
	t_rdct	*temp;
	int		j;
	int		i;

	temp = (t_rdct *)head;
	j = 0;
	while (temp != NULL)
	{
		i = 0;
		while (i < temp->nbr_rdcts)
		{
			printf("NODE[%i]-RDCT: %i file: %s, size str:%zu\n", j,
				temp->redirects[i], temp->files[i],
				ft_strlen(temp->files[i]));
			i++;
		}
		j++;
		temp = temp->next;
	}
}

// Function to print the linked list
void	printlist(void *head, int check)
{
	t_token	*temp1;

	if (!head)
	{
		printf("EMPTY LIST\n");
		return ;
	}
	if (check == 1)
	{
		temp1 = (t_token *)head;
		while (temp1 != NULL)
		{
			printf("TOKEN: %s type: %d\n", temp1->token, temp1->type);
			temp1 = temp1->next;
		}
	}
	else if (check == 3)
		printlst_cmd((t_cmd *)head);
	else
		printlst_rdct((t_rdct *)head);
	printf("\n");
}
