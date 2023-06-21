# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 18:54:14 by mdjemaa           #+#    #+#              #
#    Updated: 2023/06/19 12:44:00 by mdjemaa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

NAME := minishell

CC := gcc
CFLAGS := -Wall -Wextra -Werror -g
INCLUDES = -I Includes -I /Users/$$USER/.brew/opt/readline/include
LIB = -lreadline -L /Users/$$USER/.brew/opt/readline/lib -lft -L ./libft
SANITIZE := -fsanitize=address

SRC :=	Sources/minishell.c\
		Sources/ms_cd.c\
		Sources/ms_crash.c\
		Sources/ms_debug.c\
		Sources/ms_dollar_replace_00.c\
		Sources/ms_dollar_replace_01.c\
		Sources/ms_echo.c\
		Sources/ms_env_utils_00.c\
		Sources/ms_env_utils_01.c\
		Sources/ms_env.c\
		Sources/ms_exec00.c\
		Sources/ms_exec01.c\
		Sources/ms_exit.c\
		Sources/ms_export_00.c\
		Sources/ms_export_01.c\
		Sources/ms_export_02.c\
		Sources/ms_free.c\
		Sources/ms_hashignore.c\
		Sources/ms_lexing.c\
		Sources/ms_parsing_00.c\
		Sources/ms_parsing_01.c\
		Sources/ms_parsing_02.c\
		Sources/ms_parsing_03.c\
		Sources/ms_pwd.c\
		Sources/ms_redir_infile.c\
		Sources/ms_redir_outfile.c\
		Sources/ms_redirections.c\
		Sources/ms_signals.c\
		Sources/ms_split.c\
		Sources/ms_statics.c\
		Sources/ms_unset.c\

OBJ := $(SRC:.c=.o)

all: lib $(NAME)

lib:
	@$(MAKE) -C ./libft/

.c.o:
	@printf '$(GREEN)Compiling: $(RESET)$<\n'
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o) 

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) $(SANITIZE)
	@printf '$(RED)- $(NAME) done -$(RESET)\n'

clean:
	@printf '$(YELLOW)Cleaning $(NAME) $(RESET)\n'
	@rm -f $(OBJ)

ftclean:
	@$(MAKE) clean -C ./libft/

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)

ftre: ftclean lib



