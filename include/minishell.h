/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:36:27 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/21 15:51:22 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
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

# define PROMPT	"CHORA $> "
# define TRUE			1
# define FALSE			0
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
# define C_SPACE		11
# define APPEND			12
# define HEREDOC		13
# define AMPERSAND		14
# define ASTERISK		15
# define R_BRACKET_O	16
# define R_BRACKET_C	17
# define SEMICOLON		18
# define DOT			19
# define BACKSLASH		20
# define TILDE			21
# define H_TAB			22
# define C_ERROR		1
# define C_SUCCESS		0
# define TEST_PATH		"/nfs/homes/ckunimur/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/nfs/homes/ckunimur/.local/bin"

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

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}		t_env;

typedef struct s_data
{
	char			*prompt_in;
	char			**cmd;
	char			**cmd_args;
	char			**heredoc;
	struct s_rdct	*rdct;
	char			**env;
	char			*path;
	t_token			*tokens;
	t_env			*env_node;
	struct s_data	*next;
}			t_data;

typedef struct s_rdct
{
	int				redirect;
	char			*file;
	struct s_rdct	*next;
}				t_rdct;

typedef struct s_prompt
{
	char			*prompt_input;
}				t_prompt;

typedef struct s_builtins {
	char	*name;
	void	(*built_in)(t_data *);
}	t_builtins;

void	prompt(t_data *data);
int		is_builtins(char *check);
//void	call_builtins(t_data *ptr);

//utils

void	ft_clean_lst(char **lst);

//builtins
int		exec_builtin(t_data *data);
void	ft_cd(t_data *data);
void	ft_echo(t_data *data);
void	ft_env(t_data *data);
void	ft_exit(t_data *data);
void	ft_export(t_data *data);
void	ft_pwd(t_data *data);
void	ft_unset(t_data *data);

//env
t_env	*create_list(char *str);
t_env	*node_last(t_env *list);
void	linkar(t_env **lista, t_env *current);
void	link_end(t_env **list, t_env *current);
void	create_env(t_data **data, char **envp);

//EXECUTION
void	execution(t_data *data);
void	set_path_command(t_data *data);

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
int		is_heredoc_case(t_data *data, int i);
int		find_type(char *str);
int		is_redirect(char c);
int		find_type(char *str);
char	*define_type(char *str);
int		word_len(char *str);

// DEALING LIST
t_token	*createnode(char *token, int type);
void	ft_add_back(t_token **lst, t_token *new);
int		ft_size(t_token *lst);
void	ft_clear_token(t_token **lst);

// REDIRECT
void	create_redirect_lst(t_data *data);
t_token	*jump_white_spaces(t_token *tokens);
int		has_another_quote(t_token *tokens, int type);
int		has_redirect(t_token *tokens);
void	ft_error_redirect(int error);
int		is_syntax_error(int type);
int		is_possible_error(int type);
int		check_error(t_token *tokens);
int		dot_case(t_token *tokens);
int		tilde_case(t_token *tokens);
int		asterick_case(t_token *tokens);
int		check_file_name(t_token *tokens);
char	*take_quoted_name(t_token *tokens, int len);
char	*find_file_name(t_token *tokens);
int		first_check(t_token *tokens);
size_t	quoted_word_size(t_token *tokens, int len);
char	*get_name_quoted(t_token *tokens, char *name, int len);

// DEALING REDIRECT LIST
t_rdct	*createnode_rdct(char *file, int redirect);
t_rdct	*ft_last_rdct(t_rdct *lst);
void	ft_add_back_rdct(t_rdct **lst, t_rdct *new);
void	ft_add_front_rdct(t_rdct **lst, t_rdct *new);
void	ft_clear_rdct(t_rdct **lst);
int		ft_size_rdct(t_rdct *lst);

// LEXER
int		lexer(t_data *data);

// PRINT LIST
void	printlist(void *head, int check);

// CLEAR DATA
void	ft_clear_data(t_data *data);

#endif
