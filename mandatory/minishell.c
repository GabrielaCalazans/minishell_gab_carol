/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:36:31 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/17 15:51:26 by ckunimur         ###   ########.fr       */
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

	(void)envp;
	data = get_data();
	data->state = PROMPT; // deve se mudada para INIT quando estiver pronto
	data->prompt_in = argv[1];
	if (argc != 1)
		return (1);
	while (1)
	{
//		if (data->state == INIT)
//			init(envp);
		if (data->state == PROMPT)
			prompt();
//		if (data->state == PARSER)
//			parser();
		if (data->state == BUILTINS)
			call_builtins();
//		if (data->state == EXIT)
//			printf("Cabô\n");
//		if (data->state == EXECUTE)
//			execute(envp);
//		if (data->state == EXIT)
//			exit_program(0);
}
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