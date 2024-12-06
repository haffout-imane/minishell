NAME = minishell

CC = cc

INCLUDES = -I $(HOME)/.homebrew/opt/readline/include

LDFLAGS = -L$(HOME)/.homebrew/opt/readline/lib -lreadline

CFLAGS = -Wall -Wextra -Werror

SRC = ./minishell.c \
		./minishell_utils.c \
		./signals.c \
		./utils/utils.c \
		./utils/utils2.c \
		./utils/utils3.c \
		./utils/linked_list.c \
		./parsing/ft_split_utils2.c \
		./parsing/ft_split_utils.c \
		./parsing/ft_split.c \
		./builtin/echo.c \
		./builtin/pwd.c \
		./builtin/cd.c \
		./builtin/export.c \
		./builtin/export_utils.c \
		./builtin/unset.c \
		./builtin/exit.c \
		./builtin/builtin.c \
		./builtin/env.c \
		./parsing/split_commands_utils.c \
		./parsing/split_commands.c \
		./parsing/wild_utils.c \
		./parsing/input.c \
		./parsing/expand_wildcards2.c \
		./parsing/expand_wildcards.c \
		./parsing/wildcards_utils3.c \
		./parsing/wildcards_utils2.c \
		./parsing/wildcards_utils.c \
		./parsing/wildcards.c \
		./parsing/count.c \
		./parsing/my_env.c \
		./parsing/init_utils.c \
		./parsing/init.c \
		./parsing/free.c \
		./parsing/env_utils.c \
		./parsing/env.c \
		./executing/paths.c \
		./executing/execute.c \
		./executing/heredoc.c \
		./executing/redirection_utils.c \
		./executing/redirection.c \
		./executing/execution_utils.c \

OBJ = $(SRC:.c=.o)

BLUE=\033[0;34m
NC=\033[0m

all: $(NAME)
	@echo "$(BLUE)"
	@echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	@echo "*                                                                                                             *"
	@echo "*   ██████   ██████ █████ ██████   █████ █████  █████████  █████   █████ ██████████ █████       █████         *"
	@echo "*  ░░██████ ██████ ░░███ ░░██████ ░░███ ░░███  ███░░░░░███░░███   ░░███ ░░███░░░░░█░░███       ░░███          *"
	@echo "*   ░███░█████░███  ░███  ░███░███ ░███  ░███ ░███    ░░░  ░███    ░███  ░███  █ ░  ░███        ░███          *"
	@echo "*   ░███░░███ ░███  ░███  ░███░░███░███  ░███ ░░█████████  ░███████████  ░██████    ░███        ░███          *"
	@echo "*   ░███ ░░░  ░███  ░███  ░███ ░░██████  ░███  ░░░░░░░░███ ░███░░░░░███  ░███░░█    ░███        ░███          *"
	@echo "*   ░███      ░███  ░███  ░███  ░░█████  ░███  ███    ░███ ░███    ░███  ░███ ░   █ ░███      █ ░███      █   *"
	@echo "*   █████     █████ █████ █████  ░░█████ █████░░█████████  █████   █████ ██████████ ███████████ ███████████   *"
	@echo "*  ░░░░░     ░░░░░ ░░░░░ ░░░░░    ░░░░░ ░░░░░  ░░░░░░░░░  ░░░░░   ░░░░░ ░░░░░░░░░░ ░░░░░░░░░░░ ░░░░░░░░░░░    *"
	@echo "*                                                                                                             *"
	@echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	@echo "$(NC)"

$(NAME): $(OBJ) ./minishell.h
	@echo "$(BLUE)"
	@echo "Creating object files..."
	@echo "$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(BLUE)"
	@echo "Cleaning up..."
	@echo "$(NC)"
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
