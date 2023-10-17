/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:36:27 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/17 15:57:59 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <termios.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define PROMPT_MSG	"CHORA $> "

# define REDIRECT_IN	1
# define REDIRECT_OUT	2
# define PIPE			3
# define FLAG			4
# define SLASH			5
# define QUESTION		6
# define DOLLAR			7
# define QUOTE_DOUBLE	8
# define QUOTE_SINGLE	9
# define WORD			10
# define M_SPACE		11
# define APPEND			12
# define HEREDOC		13
# define AMPERSAND		14
# define ASTERISK		15
# define R_BRACKET_O	16
# define R_BRACKET_C	17
# define INIT			18
# define PROMPT			19
# define PARSER			20
# define BUILTINS		21
# define EXECUTE		22
# define EXIT			23

// **cmd; // aqui comando e flags
// **cmd_args; // aqui str
// **heredoc; // heredoc e seu delimitador/palavra
// **rdct; // lista redirect e seu arquivo

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}				t_token;

typedef struct s_data
{
	int				state;
	char			*prompt_in;
	char			**cmd;
	char			**cmd_args;
	char			**heredoc;
	struct s_rdct	**rdct;
	char			**env;
	t_token			*tokens;
	struct s_data	*next;
}			t_data;

extern t_data	s_data;

typedef struct s_rdct
{
	char			*redirect;
	char			*file;
	struct s_rdct	*next;
}				t_rdct;

typedef struct s_prompt
{
	char			*prompt_input;
}				t_prompt;

//prompt
void		prompt();
int			check_only_space(char *str);
void		validate_prompt(t_data *data);
int			check_quotes(char *line);

// builtins
void	ft_pwd(void);
int		is_builtins(t_data *data);
void	call_builtins();

//utils
t_data	*get_data(void);

//execution
void	exec_check(t_data *ptr);

// TOKENS
void	start_token(t_data *data);
int		is_redirect(char c);
int		is_pipe(char c);
int		is_flag(char c);
int		is_slash(char c);
int		is_questionmark(char c);
int		is_dollar(char c);
int		is_quote(char c);
int		is_space(char c);
int		is_heredoc(char *str, int check);
int		find_type(char *str);
int		is_redirect(char c);
int		find_type(char *str);
char	*define_type(char *str);
int		word_len(char *str);

// DEALING LIST
t_token	*createnode(char *token, int type);
void	ft_add_back(t_token **lst, t_token *new);
int		ft_size(t_token *lst);
void	ft_clear(t_token **lst);

// LEXER
int		lexer(t_data *data);

// PRINT LIST
void	printlist(t_token *head);

// CLEAR DATA
void	ft_clear_data(t_data *data);

#endif
