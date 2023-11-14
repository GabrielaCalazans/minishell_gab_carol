/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:42:19 by gacalaza          #+#    #+#             */
/*   Updated: 2023/11/14 00:14:58 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	move_token_cont(t_data *data, t_token *newlist)
// {
// 	t_token	*head;
// 	head = data->tokens;
// 	while (head->next != NULL)
// 	{
// 		if (head->type != REDIRECT_IN && head->type != REDIRECT_OUT)
// 			head = head->next;
// 		else
// 			break ;
// 	}
// 	head->next = newlist;
// 	data->tokens = head;
// }
// t_token	*jump_word(t_token *tokens)
// {
// 	printf("CHEGUEI AQUI3");
// 	if (tokens == NULL)
// 		return (NULL);
// 	if (is_path(tokens))
// 	{
// 		if (tokens->next)
// 			tokens = tokens->next;
// 		while (tokens)
// 		{
// 			if (tokens->type != SLASH && tokens->type != WORD)
// 				break ;
// 			tokens = tokens->next;
// 		}
// 		return (tokens);
// 	}
// 	return (tokens);
// }
// void	process_rdct_move(t_token *tmp, t_token *prev, t_token *current)
// {
// 	while (tmp)
// 	{
// 		if (tmp->type == C_SPACE || tmp->type == H_TAB)
// 		{
// 			while (tmp->type == C_SPACE || tmp->type == H_TAB)
// 				tmp = tmp->next;
// 		}
// 		if (tmp->type == QUOTED_WORD)
// 		{
// 			tmp = tmp->next;
// 			break ;
// 		}
// 		if (tmp->type == WORD || tmp->type == SLASH)
// 		{
// 			tmp = jump_word(tmp);
// 			break ;
// 		}
// 		else
// 			break ;
// 	}
// 	if (tmp)
// 	{
// 		while (tmp)
// 		{
// 			current = tmp;
// 			ft_add_back(&prev, current);
// 			prev->next = NULL;
// 			tmp = tmp->next;
// 		}
// 	}
// 	// printlist(tmp, 1);
// 	printf("PREV");
// 	printlist(prev, 1);
// 	return ;
// }
// void	check_move(t_token *tmp, t_token *prev, int type, t_token *current)
// {
// 	printf("CHEGUEI AQUI2");
// 	if (type == REDIRECT_IN || type == REDIRECT_OUT)
// 		process_rdct_move(tmp, prev, current);
// }
// void	move_tokens(t_data *data, int type)
// {
// 	t_token	*tmp;
// 	t_token	*prev;
// 	t_token	*current;
// 	tmp = data->tokens;
// 	printf("cheguei aqui %s\t%i\n", tmp->token, tmp->type);
// 	prev = NULL;
// 	if (!tmp)
// 		return ;
// 	tmp = jump_white_spaces(tmp);
// 	while(tmp)
// 	{
// 		printf("cheguei aqui %s\t%i", tmp->token, tmp->type);
// 		if (tmp->type == type)
// 		{
// 			check_move(tmp, prev, type, current);
// 		}
// 		printf("cheguei aqui %s\t%i", tmp->token, tmp->type);
// 		if (tmp)
// 		{
// 			current = tmp;
// 			ft_add_back(&prev, current);
// 			prev->next = NULL;
// 			// printlist(prev, 1);
// 			tmp = tmp->next;
// 		}
// 		printf("cheguei aqui %s\t%i", tmp->token, tmp->type);
// 		// tmp = tmp->next;
// 	}
// }
// data->cmd_args = take_q_name(&*tmp);
// char	**case_redirec_only(t_token *tokens, int pipes)
// {
// 	t_token	*tmp;
// 	tmp = tokens;
// 	while (tmp)
// 	{
// 		if (tmp->type == PIPE)
// 			break ;
// 		if (tmp->token == WORD)
// 	}
// }

char	**get_all_words(t_token *tokens)
{
	char	**all_words;
	int		check;
	// int		pipes;

	check = 0;
	// pipes = has_pipe_yet(tokens);
	all_words = NULL;
	if (has_redirect_pipe(tokens))
		check = 1;
	if (has_d_redirec_p(tokens))
		check += 2;
	if (check == 0)
		all_words = get_words(tokens, nb_words(tokens));
	if (check == 1)
		all_words = get_words_one(tokens);
	if (check == 2)
		all_words = get_words_two(tokens);
	if (check == 3)
		all_words = get_words_three(tokens);
	if (!all_words)
		ft_error_parse(2);
	return (all_words);
}

void	print_array(char **array, char *type)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		printf("%s[%i]: %s\n", type, i, array[i]);
		i++;
	}
	printf("\n");
}

	// data->cmd = ft_arraydup(all_words);
void	parsing_it(t_data *data)
{
	char	**all_words;

	all_words = get_all_words(data->tokens);
	get_cmd(data, all_words);
	print_array(data->cmd, "cmd");
	print_array(data->cmd_args, "cmd_args");
}
