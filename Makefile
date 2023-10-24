# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/28 16:01:26 by gacalaza          #+#    #+#              #
#    Updated: 2023/10/20 17:17:29 by ckunimur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==== Name of the program =====
NAME =	minishell

# ======= Sources ========
SRCS = minishell.c prompt.c execution.c

TOKEN = token.c token_utils_one.c token_utils_two.c token_utils_three.c
TOKEN += token_lst.c token_lst_utils.c

LEXER = lexical.c

PARSE = parse.c

BUILTINS = builtins.c ft_pwd.c ft_echo.c ft_env.c ft_export.c ft_cd.c ft_exit.c ft_unset.c

UTILS = utils.c env.c

# ====== Folders and Paths ========
LIBFT_DIR	= ./libft/
INCL_DIR	= ./include/
LIBFT		= $(addprefix $(LIBFT_DIR), libft.a)
HEADERM		= $(addprefix $(INCL_DIR), minishell.h)
SRCS_MAIN	= $(addprefix ./mandatory/, $(SRCS))
TOKEN_DIR	= $(addprefix ./token/, $(TOKEN))
TOKEN_F		= $(addprefix ./mandatory/, $(TOKEN_DIR))
LEXER_DIR	= $(addprefix ./lexer/, $(LEXER))
LEXER_F		= $(addprefix ./mandatory/, $(LEXER_DIR))
PARSE_DIR	= $(addprefix ./parse/, $(PARSE))
PARSE_F		= $(addprefix ./mandatory/, $(PARSE_DIR))
BUILTINS_DIR	= $(addprefix ./builtins/, $(BUILTINS))
BUILTINS_F		= $(addprefix ./mandatory/, $(BUILTINS_DIR))
UTILS_DIR	= $(addprefix ./utils/, $(UTILS))
UTILS_F		= $(addprefix ./mandatory/, $(UTILS_DIR))

MANDATORY	:= $(SRCS_MAIN) $(TOKEN_F) $(LEXER_F) $(UTILS_F) $(BUILTINS_F)

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
					--trace-children=yes

# =================== Rules ==========================

# # Compiling Mandatory or Bonus Objs
%.o:		%.c
			$(CC) $(FLAGS) -I $(INCL_DIR) -c $< -o $@

all:		comp_libft $(NAME)

			$(OBJS): $(HEADERM)

			$(NAME): $(OBJS)
			cc $(FLAGS) -I $(INCL_DIR) $^ $(LIBFT) $(LIBS) -o $@


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
