# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dapaulin <dapaulin@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/28 16:01:26 by gacalaza          #+#    #+#              #
#    Updated: 2023/12/10 22:01:47 by dapaulin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ==== Name of the program =====
NAME =	minishell

# ======= Sources ========
SRCS = minishell.c prompt.c execution.c printlist.c signal.c print_array.c

TOKEN = token.c token_utils_one.c token_utils_two.c token_utils_three.c
TOKEN += token_lst.c token_lst_utils.c

REDIRECT = redirect.c redirect_utils_two.c redirect_utils_one.c redirect_lst.c
REDIRECT += redirect_lst_utils.c error_redirect.c error_redirect_utils.c
REDIRECT += ft_heredoc.c ft_append.c ft_input.c ft_output.c

LEXER = lexical_analyzer.c lexical_one.c lexical_two.c lexical_three.c
LEXER += lexical_four.c lexical_five.c lexical_six.c

PARSE = parse.c parse_utils.c parse_utils_two.c
PARSE += case_zero.c case_one.c case_two.c case_three.c
PARSE += cmd_lst.c cmd_lst_utils.c expansion_var.c expansion_var_utils.c

BUILTINS = builtins.c ft_pwd.c ft_echo.c ft_env.c ft_export.c
BUILTINS += ft_cd.c ft_exit.c ft_unset.c builtins_utils.c

CLEAR_DATA = clear_data.c

UTILS = utils.c env.c arrays.c ft_intdup.c

# ====== Folders and Paths ========
LIBFT_DIR		= ./libft/
INCL_DIR		= ./include/
LIBFT			= $(addprefix $(LIBFT_DIR), libft.a)
HEADERM			= $(addprefix $(INCL_DIR), minishell.h)
SRCS_MAIN		= $(addprefix ./mandatory/, $(SRCS))
TOKEN_DIR		= $(addprefix ./token/, $(TOKEN))
TOKEN_F			= $(addprefix ./mandatory/, $(TOKEN_DIR))
LEXER_DIR		= $(addprefix ./lexer/, $(LEXER))
LEXER_F			= $(addprefix ./mandatory/, $(LEXER_DIR))
PARSE_DIR		= $(addprefix ./parse/, $(PARSE))
PARSE_F			= $(addprefix ./mandatory/, $(PARSE_DIR))
BUILTINS_DIR	= $(addprefix ./builtins/, $(BUILTINS))
BUILTINS_F		= $(addprefix ./mandatory/, $(BUILTINS_DIR))
REDIRECT_DIR	= $(addprefix ./redirect/, $(REDIRECT))
REDIRECT_F		= $(addprefix ./mandatory/, $(REDIRECT_DIR))
CLEAR_DATA_F	= $(addprefix ./mandatory/, $(CLEAR_DATA))
UTILS_DIR		= $(addprefix ./utils/, $(UTILS))
UTILS_F			= $(addprefix ./mandatory/, $(UTILS_DIR))

MANDATORY	:= $(SRCS_MAIN) $(TOKEN_F) $(LEXER_F) $(UTILS_F)
MANDATORY	+= $(BUILTINS_F) $(REDIRECT_F) $(CLEAR_DATA_F) $(PARSE_F)

# ========== OBJS ============
OBJS = $(MANDATORY:.c=.o)

# OBJ_DIR		= ./mandatory/objs/
# OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
# # Creating objs_dir
# $(shell mkdir -p $(OBJ_DIR))
# # Compiling Objects and Moving to OBJ_DIR
# $(OBJ_DIR)%.o: $(MANDATORY)%.c
# 	$(CC) $(FLAGS) -I $(INCL_DIR) -c $< -o $@

# ====== Flags ========
FLAGS = -Wall -Wextra -Werror -g3
LIBS = -lreadline
VALGRIND		=	valgrind \
					--leak-check=full \
					--show-leak-kinds=all \
					--quiet \
					--suppressions=readline.supp \
					--keep-debuginfo=yes \
					--trace-children=yes \
					--trace-children-skip='*/bin/*,*/sbin/*' \
					--track-fds=yes

# =================== Rules ==========================

# # Compiling Mandatory or Bonus Objs
%.o:		%.c
			$(CC) $(FLAGS) -I $(INCL_DIR) -c $< -o $@

all:	comp_libft $(NAME)

$(OBJS): $(HEADERM)

$(NAME): $(OBJS)
	@cc $(FLAGS) -I $(INCL_DIR) $^ $(LIBFT) $(LIBS) -o $@

comp_libft:
			@make -C $(LIBFT_DIR) --no-print-directory

run:		all
			./$(NAME)

valgrind:	all
			$(VALGRIND) ./$(NAME)

norminette:	all
			norminette

bonus:		comp_libf $(BONUS)pu

re:			fclean all

rebonus:	fclean bonus

clean:
			@rm -rf $(OBJS)
			@make -C $(LIBFT_DIR) clean

fclean:		clean
			@rm -rf $(NAME)
			@make -C $(LIBFT_DIR) fclean
