NAME = minishell
CC = clang
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
FLAGS = -lreadline

LIB = libft/libft.a
FT_PRINTF = ft_printf/ft_printf.a

SRCDIR = sources
ENVDIR = env
EXECDIR = exec
LEXERDIR = lexer
PARSDIR = parsing
UTILS = utils
BUILDIR = builtins
OBJDIR = objects

SRC =	$(SRCDIR)/minishell.c \
		$(SRCDIR)/get_env.c \
		$(SRCDIR)/$(ENVDIR)/env_set.c \
		$(SRCDIR)/$(ENVDIR)/env_utils.c \
		$(SRCDIR)/$(EXECDIR)/exec.c \
		$(SRCDIR)/$(EXECDIR)/open_files.c \
		$(SRCDIR)/$(BUILDIR)/builtins.c \
		$(SRCDIR)/$(BUILDIR)/builtins_utils.c \
		$(SRCDIR)/$(BUILDIR)/cd.c \
		$(SRCDIR)/$(BUILDIR)/echo.c \
		$(SRCDIR)/$(BUILDIR)/env.c \
		$(SRCDIR)/$(BUILDIR)/exit.c \
		$(SRCDIR)/$(BUILDIR)/export.c \
		$(SRCDIR)/$(BUILDIR)/pwd.c \
		$(SRCDIR)/$(BUILDIR)/unset.c \
		$(SRCDIR)/$(EXECDIR)/exec_utils.c\
		$(SRCDIR)/$(EXECDIR)/redirect.c \
		$(SRCDIR)/$(LEXERDIR)/env_var_handling.c \
		$(SRCDIR)/$(LEXERDIR)/env_var_utils.c \
		$(SRCDIR)/$(LEXERDIR)/envp_check.c \
		$(SRCDIR)/$(LEXERDIR)/lexer_utils.c \
		$(SRCDIR)/$(LEXERDIR)/quotes_handler_utils.c \
		$(SRCDIR)/$(LEXERDIR)/quotes_handler.c \
		$(SRCDIR)/$(LEXERDIR)/token_generator.c \
		$(SRCDIR)/$(LEXERDIR)/token_utils.c \
		$(SRCDIR)/$(LEXERDIR)/var_validation.c \
		$(SRCDIR)/$(PARSDIR)/args_handling.c \
		$(SRCDIR)/$(PARSDIR)/cmd_list_utils.c \
		$(SRCDIR)/$(PARSDIR)/create_commands.c \
		$(SRCDIR)/$(PARSDIR)/execute.c \
		$(SRCDIR)/$(PARSDIR)/expand_variables.c \
		$(SRCDIR)/$(PARSDIR)/fd_utils.c \
		$(SRCDIR)/$(PARSDIR)/file_io.c \
		$(SRCDIR)/$(PARSDIR)/heredoc_utils.c \
		$(SRCDIR)/$(PARSDIR)/heredoc_var_utils.c \
		$(SRCDIR)/$(PARSDIR)/parse_append.c \
		$(SRCDIR)/$(PARSDIR)/parse_heredoc_utils.c \
		$(SRCDIR)/$(PARSDIR)/parse_heredoc.c \
		$(SRCDIR)/$(PARSDIR)/parse_io.c \
		$(SRCDIR)/$(PARSDIR)/parse_path.c \
		$(SRCDIR)/$(PARSDIR)/parse_pipe.c \
		$(SRCDIR)/$(PARSDIR)/parse_word.c \
		$(SRCDIR)/$(PARSDIR)/parsing.c \
		$(SRCDIR)/$(PARSDIR)/signal.c \
		$(SRCDIR)/$(UTILS)/free.c \
		$(SRCDIR)/$(UTILS)/errors.c \
		$(SRCDIR)/delete_this/tests.c

OBJ := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIB) $(FT_PRINTF)
	@echo "$(GREEN)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(FT_PRINTF) $(LIB) $(FLAGS)
	@echo "$(GREEN)Done!$(NC)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p  $(@D)
	@echo "$(GREEN)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(LIB):
	@$(MAKE) -s -C libft

$(FT_PRINTF):
	@$(MAKE) -s -C ft_printf

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@$(MAKE) clean -s -C libft
	@$(MAKE) clean -s -C ft_printf
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(RED)Full clean...$(NC)"
	@rm -f $(NAME)
	@$(MAKE) fclean -s -C libft
	@$(MAKE) fclean -s -C ft_printf

re: fclean all

supp:
	valgrind --leak-check=full --gen-suppressions=all ./$(NAME)

minigrind :
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re supp minigrind
