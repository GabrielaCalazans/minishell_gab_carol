/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:36:31 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/20 17:19:09 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function to print the linked list
void	printlist(void *head, int check)
{
	t_token	*temp1;
	t_rdct	*temp2;

	if (!head)
		printf("EMPTY");
	if (check == 1)
	{
		temp1 = (t_token *) head;
		while (temp1 != NULL)
		{
			printf("NODE - token: %s type: %d\n", temp1->token, temp1->type);
			temp1 = temp1->next;
		}
	}
	else
	{
		temp2 = (t_rdct *) head;
		while (temp2 != NULL)
		{
			printf("NODE - redirect: %i file_name: %s, size str:%zu\n",
				temp2->redirect, temp2->file, ft_strlen(temp2->file));
			temp2 = temp2->next;
		}
	}
	printf("\n");
}

void	set_data(t_data *data)
{
	data->tokens = NULL;
	data->rdct = NULL;
	data->env_node = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	(void)argv;
	(void)argc;
	if (argc != 1)
		return (1);
	set_data(data);
	create_env(&data, envp);
	prompt(data);
	return (0);
}

	// find_token(argv[1], &tokens);
	// printf("MAIN:");
	// printlist(tokens);
	// find_token("dasda*");
	// find_token("da s da *");
	// find_token("? *");
	// find_token("cat black dog > ");
	// find_token("cat oi, tudo bem? > oi.txt");
	// printf("%d\n", is_redirect('>'));
	// printf("%d\n", is_redirect('<'));
	// printf("%d\n", is_redirect('!'));