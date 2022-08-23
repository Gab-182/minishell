# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 06:52:30 by gabdoush          #+#    #+#              #
#    Updated: 2022/08/18 14:50:21 by gabdoush         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef VERPOSE
.SILENT:
endif


NAME = minishell

FILES = main.c\
		\
		./executer/hereDoc.c\
		./executer/ft_dup2.c\
		./executer/executer.c\
		./executer/get_path.c\
		./executer/check_cmd.c\
		./executer/fork_child.c\
		./executer/print_path.c\
		./executer/redirection.c\
		./executer/signal_handler.c\
		./executer/redirection_utils.c\
		\
		./parser/parser.c\
		./parser/env_ft.c \
		./parser/ft_split.c \
		./parser/ft_split_og.c \
		./parser/copy_and_split_cmd.c \
		./parser/check_and_alloc_op.c \
		./parser/copy_op_and_filename.c \
		./parser/utils0.c \
		./parser/utils1.c \
		./parser/utils2.c \
		./parser/utils3.c \
		./parser/utils4.c \
		./parser/utils5.c \
		./parser/utils6.c \
		./parser/utils7.c \
		\
		./builtin/builtin_cmds/exit.c\
		./builtin/builtin_cmds/ft_cd.c\
		./builtin/builtin_cmds/ft_pwd.c\
		./builtin/builtin_cmds/ft_echo.c\
		\
		./builtin/builtin.c\
		./builtin/env_cmds/shlvl.c\
		./builtin/env_cmds/ft_env.c\
		./builtin/env_cmds/ft_unset.c\
		./builtin/env_cmds/ft_export.c\
		./builtin/env_cmds/env_utils.c\
		./builtin/env_cmds/env_utils_2.c\
		./builtin/env_cmds/export_utils.c\
		./builtin/env_cmds/export_utils_2.c\
		\
		./clean/free_cmds.c\
		./clean/struct_cleaner.c\

HEADERS = ./minishell.h\
		./libft/libft.h\

OBJ = $(FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror -lreadline -L /usr/local/Cellar/readline/8.1/lib -I /usr/local/Cellar/readline/8.1/include
# Linux_env
#FLAGS = -Wall -Wextra -Werror
sanitize = -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls

LIBFT = ./libft/libft.a

CC = gcc

#-------------------- Define Color-------------------#
ifneq (,$(findstring xterm,${TERM}))
	R            := $(shell tput -Txterm setaf 1)
	G            := $(shell tput -Txterm setaf 2)
	Y            := $(shell tput -Txterm setaf 3)
	LP           := $(shell tput -Txterm setaf 4)
	P            := $(shell tput -Txterm setaf 5)
	B            := $(shell tput -Txterm setaf 6)
	W            := $(shell tput -Txterm setaf 7)
	RS := $(shell tput -Txterm sgr0)
else
	R            := ""
	G            := ""
	Y            := ""
	LP           := ""
	P            := ""
	B            := ""
	W            := ""
	RS           := ""
endif
#-------------------- Define Color-------------------#


all: $(NAME) $(HEADER) $(FILES)

$(NAME): $(OBJ)
	@echo "$(Y)——————————————————————————————————————————————————————————————————————————————————$(RS)"
	@echo "$(G)【OK】$(RS) $(B)making libft.a....$(RS)"
	@make -C ./libft
	@echo "$(G)【OK】$(RS) $(B)Compiling with the flags....$(RS)"

#For mac
#	$(CC) -g $(sanitize) $(FLAGS) $(FILES) $(LIBFT) -lreadline -ltermcap -o minishell
# For Linux
	$(CC) -g $(FLAGS) $(FILES) $(LIBFT) -lreadline -o minishell

	@echo "$(G)【OK】$(B)❮minishell❯ CREATED$(RS)"
	@echo "$(Y)——————————————————————————————————————————————————————————————————————————————————$(RS)"
	@echo "\033c"

	@echo "$(R)≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡ $(RS)"
	@echo "$(R)║$(LP)░░░░░███░░░░███░██░███░░░██░██░░░░░░███████░██░░░██░███████░██░░░░░░██░░░░░░░░░░$(R)║$(RS)"
	@echo "$(R)║$(LP)░░░░░████░░████░██░████░░██░██░░░░░░██░░░░░░██░░░██░██░░░░░░██░░░░░░██░░░░░░░░░░$(R)║$(RS)"
	@echo "$(R)║$(LP)░░░░░██░████░██░██░██░██░██░██░░░░░░███████░███████░█████░░░██░░░░░░██░░░░░░░░░░$(R)║$(RS)"
	@echo "$(R)║$(LP)░░░░░██░░██░░██░██░██░░████░██░░░░░░░░░░░██░██░░░██░██░░░░░░██░░░░░░██░░░░░░░░░░$(R)║$(RS)"
	@echo "$(R)║$(LP)░░░░░██░░░░░░██░██░██░░░███░██░░░░░░███████░██░░░██░███████░███████░███████░░░░░$(R)║$(RS)"
	@echo "$(R)≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡ $(RS)"

	@echo "$                         $(LP)_________Created_By__________$(RS)"
	@echo "                        $(Y)𝔾𝕙𝕒𝕚𝕒𝕥𝕙 𝔸𝕓𝕕𝕠𝕦𝕤𝕙 && 𝕀𝕞𝕒𝕕 𝕊𝕒𝕒𝕕$(RS)"
	@echo "$                         $(LP)-----------------------------$(RS)"
	@echo "\n"

# --leak-check=full: "each individual leak will be shown in detail"
# --show-leak-kinds=all: Show all of "definite, indirect, possible, reachable" leak kinds in the "full" report.
# --verbose: Can tell you about unusual behavior of your program. Repeat for more verbosity.
leaks_fd:
	make re && make clean && valgrind --track-fds=yes  ./minishell
# --suppressions=supress_readline \
# --log-file=valgrind-out.txt 
leaks:
	make re && make clean \
	&& valgrind --leak-check=full \
	--track-origins=yes \
	--show-leak-kinds=all -s \
	./minishell

norm:
	norminette ./* ./libft/*

clean:
	@echo "$(Y)——————————————————————————————————————————————————————————————————————————————————$(RS)"
	@make -C ./libft clean
	@rm -rf $(OBJ)
#	@echo "\033c"
	@echo "$(G)【OK】 $(RS)        $(R)❮minishell❯ objects have been cleaned$(RS)"
	@echo "$(Y)——————————————————————————————————————————————————————————————————————————————————$(RS)"

fclean: clean
	@echo "$(Y)——————————————————————————————————————————————————————————————————————————————————$(RS)"
	@rm -rf minishell
	@make -C ./libft fclean
	@echo "\033c"
	@echo "$(G)【OK】 $(RS)        $(R)❮minishell excutable❯ DELETED$(RS)"
	@echo "$(Y)——————————————————————————————————————————————————————————————————————————————————$(RS)"

re: fclean all

.PHONY: all clean fclean re
