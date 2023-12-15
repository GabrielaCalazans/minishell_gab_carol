/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:36:27 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/15 19:06:58 by gacalaza         ###   ########.fr       */
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

# define PROMPT	"minishell $> "
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
# define QUOTED_WORD	23
# define EXIT_STATUS	24
# define C_ERROR		1
# define C_SUCCESS		0
# define HEREDOC_FILE	"/tmp/.heredoc"

// **cmd; // aqui comando e flags
// **cmd_args; // aqui str
// **heredoc; // heredoc e seu delimitador/palavra
// **rdct; // lista redirect e seu arquivo

typedef struct s_tk_p
{
	int		check;
	int		type;
	int		i;
	int		back;
}			t_tk_p;

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_rdct
{
	int				nbr_rdcts;
	int				*redirects;
	char			**files;
	int				index;
	struct s_rdct	*next;
}				t_rdct;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}		t_env;

typedef struct s_cmd
{
	char			**cmd;
	int				index;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_data
{
	char			*prompt_in;
	char			**env;
	char			*path;
	int				*fd;
	int				no_exec;
	int				n_cmd;
	int				*pid;
	int				amount_heredocs;
	t_cmd			*cmd;
	t_rdct			*rdct;
	t_token			*tokens;
	t_env			*env_node;
	int				rdct_fds[2];
	int				bkp_fd[2];
	int				exit_code;
	t_rdct			*head_rdct;
	t_cmd			*head_cmd;
}			t_data;

typedef struct s_prompt
{
	char	*prompt_input;
}			t_prompt;

typedef struct s_builtins {
	char	*name;
	void	(*built_in)(t_data *);
}	t_builtins;

typedef struct s_params
{
	char	**files;
	int		*redirects;
	int		inside_pipe;
	int		len;
	int		index;
	int		i;
}	t_params;

void		prompt(t_data *data);
//void	call_builtins(t_data *ptr);
void		mini_start(t_data *data);

//utils
void		ft_clean_lst(char **lst);

//BUILTINS
int			is_builtins(char *check);
int			exec_builtin(t_data *data);
void		ft_cd(t_data *data);
void		ft_echo(t_data *data);
void		ft_env(t_data *data);
void		ft_exit(t_data *data);
void		ft_export(t_data *data);
void		ft_pwd(t_data *data);
void		ft_unset(t_data *data);
//void		print_echo(t_data *data, int i);

//ENV
t_env		*create_node(char *str);
t_env		*node_last(t_env *list);
t_env		*append_env(char *arg);
void		link_lst(t_env **list, t_env *current);
void		create_env(t_data **data, char **envp);
int			ft_size_lst_env(t_data *data);
void		ft_set_env(t_data *data);

//EXPORT
t_env		*have_var(t_data *data, char *arg);
void		change_value(t_env *env_node, char *arg);
int			is_valid_var(t_data	*data);

//EXECUTION
int			run_one_builtin(t_data *data);
void		run_only_redirects(t_data *data);
int			run_process(t_data *data, int **pid);
void		run_waitpid(t_data *data, int **pid, int len);
void		execution(t_data *data);
void		set_path_command(t_data *data);
void		config_pipe(t_data *data);
void		execute_pid(t_data *data, int i, int ord);

//HEREDOC
void		ft_heredoc(char	*key_str, t_data *data);
int			ft_input(char *file, t_data *data, int check);
int			ft_output(char *file, t_data *data, int check);
int			ft_append(char *file, t_data *data, int check);
void		find_heredoc(t_data *data);
void		finish_fork(t_data *data);

//PIPE
void		dup_pipe(int i, int ord, t_data *data);
void		close_fd(t_data *data, int n_fd);

// TOKENS
void		start_token(t_data *data);
int			find_type(char *str);
char		*define_type(char *str);
int			word_len(char *str, int back);
int			qword_len(char *str, int type, int back);
int			ft_lensize(char *str);
int			len_flag(char *str);
int			len_var(char *str);
t_tk_p		*inicialize_tokenparams(void);
void		backs_case(t_tk_p *p);
void		def_len(t_data *data, t_tk_p *p, int check);

// DEALING LIST
t_token		*createnode(char *token, int type);
void		ft_add_back(t_token **lst, t_token *new);
int			ft_size(t_token *lst);
void		ft_clear_token(t_token **lst);

// REDIRECT
char		*exec_trim_process(t_token **tmp, char *value);
t_params	*inicialize_rd_params(void);
t_token		*jump_white_spaces(t_token *tokens);
void		create_redirect_lst(t_data *data);
void		ft_error_redirect(int error);
int			is_syntax_error(int type);
int			is_possible_error(int type);
int			is_special_case(int type, int check);
int			check_error(t_token *tokens);
int			tilde_case(t_token *tokens);
int			asterick_case(t_token *tokens);
int			check_file_name(t_token *tokens);
char		*take_q_name(t_token *tokens);
char		*find_file_name(t_token *tokens);
char		*get_name(t_token **tokens);
int			first_check(t_token *tokens);
size_t		quoted_word_size(t_token *tokens, int len);
char		*get_name_quoted(t_token *tokens, char *name, int len);
char		*word_case(t_token *tokens);
char		**freearray(char **array);
char		**ft_arraydup(char **array);
char		**ft_dup_size(char **array, int size);
int			ft_array_size(char **array);
int			*ft_intdup(int *array, int size);
void		*return_error(void);
int			run_redirect(t_data *data, int index, int check);

// DEALING REDIRECT LIST
t_rdct		*createnode_rdct(char **files, int *redirects,
				int nbr_rdcts, int index);
t_rdct		*ft_last_rdct(t_rdct *lst);
void		ft_add_back_rdct(t_rdct **lst, t_rdct *new);
void		ft_add_front_rdct(t_rdct **lst, t_rdct *new);
void		ft_clear_rdct(t_rdct **lst);
int			ft_size_rdct(t_rdct *lst);

// PARSE
void		parsing_it(t_data *data);
char		**get_args(char **words, int len);
char		*get_cmd(char **words);
char		**get_words(t_token *tokens, int len);
char		**get_words_one(t_token *tokens);
t_token		*move_one(t_token *tokens);
char		**get_words_two(t_token *tokens);
t_token		*move_two(t_token *tokens);
char		**get_all_words(t_token *tokens);
char		**get_words_three(t_token *tokens);
int			nb_words(t_token *tokens);
char		*trim_process(char *word, int type);
char		**trim_quote(char **words);
char		**fixwords(t_token *tokens, char **words);
void		finalizepipe_cmd(t_data *data, char	**all_words, int index);
void		cmd_pipe(t_data *data, int index);
void		*ft_error_parse(int error);
void		return_error_parse(char *str);
char		*process_backs(char *str, int len);
char		*process_vars(t_data *data, char *words);
int			check_vars(t_data *data, char *words);
char		*get_str_expand(t_data *data, char *str);

// EXPASION
int			has_variable(char c);
char		*get_var_value(t_data *data, char *var, int *i);
char		*join_strings(t_data *data, char *str, int *i, int must_increment);
char		*dont_find_variable_expand(char *str, int *i);
void		check_quotes(int *flag, int *i, char *str);

// PARSE LIST
t_cmd		*createnode_cmd(char **cmd, int index);
t_cmd		*ft_last_cmd(t_cmd *lst);
int			ft_size_cmd(t_cmd *lst);
void		ft_clear_cmd_lst(t_cmd **lst);
void		ft_add_back_cmd(t_cmd **lst, t_cmd *new);
void		ft_add_front_cmd(t_cmd **lst, t_cmd *new);

// LEXER
int			has_pipe(t_token *tokens);
int			has_redirect(t_token *tokens);
int			has_rdrct_pipe(t_token *tokens);
int			has_dredirect(t_token *tokens);
int			has_d_redirec_p(t_token *tokens);
int			has_asquote_str(char *str, int type);
int			has_another_quote(t_token *tokens, int type);
int			is_backs(char *str, int len, int type);
int			is_worbks_case(int type, char c);
int			is_word(int type, int check);
int			is_rd_case(int type);
int			is_drd_case(int type);
int			is_path(t_token *tokens);
int			is_redrt_case(int type);
int			is_redirect(char c);
int			is_a_quote(int type);
int			is_pipe(char c);
int			is_flag(char *str);
int			is_slash(char c);
int			is_slashcase(int type);
int			is_questionmark(char c);
int			is_dollar(char *str);
int			is_quote(char c);
int			is_space(char c);
int			is_special_char(char c);
int			is_r_bracket(char c);
int			is_heredoc(char *str, int check);
int			is_hd_c(char *str);
int			is_e_c(char *str);
int			is_word_q(int check);

// PRINT LIST
void		printlist(void *head, int check);
void		print_array(char **array, char *type);
void		printarray(char **array);

// CLEAR DATA
void		ft_clear_data(t_data *data);
void		ft_clear_env(t_env *env_node);

// SIGNAL
void		run_signals(int sig);

// PROMPT
void		get_path(t_data *data);
int			command_count(t_data *data);
void		clean_exit(t_data *data, int check);
#endif
