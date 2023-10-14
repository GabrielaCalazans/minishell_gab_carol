/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinekunimura <carolinekunimura@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:36:31 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/13 16:39:49 by carolinekun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function to print the linked list
/*
void	printlist(t_token *head)
{
	t_token	*temp;

	if (!head)
		printf("EMPTY");
	temp = head;
	while (temp != NULL)
	{
		printf("NODE - token: %s type: %d\n", temp->token, temp->type);
		temp = temp->next;
	}
	printf("\n");
}

void	set_data(t_data *data)
{
	data->tokens = NULL;
}
*/
int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	data->prompt_in = readline(PROMPT);
	data = get_data();
	(void)argv;
	(void)envp;
	(void)argc;
	if (argc != 1)
		return (1);
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