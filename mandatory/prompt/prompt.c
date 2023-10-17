/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:55:06 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/17 16:03:26 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static char	*read_line(t_data *data)
{
	char	*str;

	str = readline(PROMPT_MSG);
	// Se a função readline() retornar NULL, isso significa 
	// que a entrada foi encerrada (por exemplo, quando o usuário pressiona Ctrl+D), e o 
	// estado EXIT é definido em element, e a função retorna NULL.
	if (!str) 
	{
		data->state = EXIT;
		return(NULL);
	}
	else
	{
		if (*str != '\0')
		{
			add_history(str);
			return(str);
		}
		else
			free(str);
	}
	return (NULL);
}

int	check_quotes(char *line)
{
	int i;
	int uniquote;
	int duoquote;

	i = 0;
	uniquote = 0;
	duoquote = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 34)
			duoquote++; // vai iterando enquanto acha aspas e contando.
		if (line[i] == 39)
			uniquote++;
		i++;
	}
	// retorna a soma dos restos da divisão de uniquote por 2 e duoquote por 2. 
	// Isso resulta em 0 se as aspas estiverem balanceadas (número par de aspas), e 1 se 
	// houver um número ímpar de aspas abertas (desbalanceadas).
	return((uniquote % 2) + (duoquote % 2));
}

// verifica se uma string str consiste apenas em espaços em branco.
int	check_only_space(char *str)
{
	printf("check_only_spaces\n");
	if(!str)
		return (0);	
	while(*str)
	{
		if(*str != ' ')
			return(1);
		str++;
	}
	return(0);
}

void	validate_prompt(t_data *data)
{
	printf("validate_prompt\n");
	if(check_quotes(data->prompt_in))
	{
		data->state = EXIT;
		printf("aspas abertas");
		free(data->prompt_in);
		data->prompt_in = NULL;
	}
	if (check_only_space(data->prompt_in))
		data->state = PARSER;
	if (data->state == PROMPT && data->prompt_in)
		free(data->prompt_in);
}

void	prompt()
{
	t_data	*data;

	printf("prompt\n");
	data = get_data();
	data->prompt_in = read_line(data);
	validate_prompt(data);
}
