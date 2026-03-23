CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -I./includes/ -g3
LDFLAGS = -lreadline
OBJ_DIR = obj
SRC =	./main.c \
		./main_utils.c \
		./main_utils_bis.c \
		./signals.c \
		./parsing/parsing.c \
		./parsing/tokenizer/tokenizer.c \
		./parsing/tokenizer/quotes_parse/join_quotes.c \
		./parsing/utils/c_history_utils.c \
		./parsing/tokenizer/quotes_parse/join_quotes_utils.c \
		./parsing/tokenizer/quotes_parse/join_quotes_utils_bis.c \
		./parsing/tokenizer/utils/preprocess_strings.c \
		./parsing/tokenizer/quotes_parse/process_quotes.c \
		./parsing/tokenizer/create_token/create_token.c \
		./parsing/tokenizer/create_token/define_token.c \
		./parsing/tokenizer/utils/split_quote_aware.c \
		./parsing/tokenizer/define_role.c \
		./parsing/tokenizer/utils/test.c \
		./parsing/tokenizer/utils/test_bis.c \
		./parsing/automate/automate.c \
		./parsing/automate/ft_automate.c \
		./parsing/automate/check_redir.c \
		./parsing/automate/check_redir_bis.c \
		./exec/built-ins/cd.c \
		./exec/built-ins/cd_utils.c \
		./exec/built-ins/echo.c \
		./exec/built-ins/env.c \
		./exec/built-ins/exit.c \
		./exec/built-ins/export.c \
		./exec/built-ins/pwd.c \
		./exec/built-ins/unset.c \
		./exec/cmd_env/cmd/fill_cmd_list.c \
		./exec/cmd_env/cmd/fill_new_node.c \
		./exec/cmd_env/cmd/find_path.c \
		./exec/cmd_env/cmd/get_args.c \
		./exec/cmd_env/cmd/print_cmdlist.c \
		./exec/cmd_env/env/fill_envp.c \
		./exec/cmd_env/env/utils_envp.c \
		./exec/cmd_env/expand_unquote/expand.c \
		./exec/cmd_env/expand_unquote/expand_utils.c \
		./exec/cmd_env/expand_unquote/unquote.c \
		./exec/cmd_env/heredoc/heredoc.c \
		./exec/cmd_env/heredoc/exec_heredoc.c \
		./exec/exec/exec_main.c \
		./exec/exec/exec_cmd.c \
		./exec/exec/pipe.c \
		./exec/exec/child.c \
		./exec/exec/redirections.c \
		./exec/exec/utils_exec.c \
		./exec/free/utils_free.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DIRS = $(sort $(dir $(OBJ)))

MAKE = make -C

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(BLUE)Compiling $(NAME)...$(RESET)"
	@$(MAKE) all_libft --no-print-directory
	@$(CC) $(CFLAGS) $(OBJ) ./all_libft/libft/libft.a -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)Compilation successful!$(RESET)"


$(OBJ_DIR)/%.o: %.c | $(DIRS)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(DIRS):
	@mkdir -p $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) all_libft clean --no-print-directory

fclean: clean
	@echo "$(RED)Cleaning executable $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) all_libft fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re $(DIRS) rc 
rc:
	@make re --no-print-directory && make clean --no-print-directory


RESET  = \033[0m
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
BOLD   = \033[1m
