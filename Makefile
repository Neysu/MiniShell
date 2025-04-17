NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g
FLAGS = -lreadline

LIB = libft/libft.a
FT_PRINTF = ft_printf/ft_printf.a

SRCDIR = sources
EXECDIR = exec
PARSDIR = parsing
UTILS = utils
BUILDIR = builtins
OBJDIR = objects

SRC =	$(SRCDIR)/minishell.c \
		$(SRCDIR)/get_env.c \
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
		$(SRCDIR)/$(PARSDIR)/args_handling.c \
		$(SRCDIR)/$(PARSDIR)/cmd_list_utils.c \
		$(SRCDIR)/$(PARSDIR)/create_commands.c \
		$(SRCDIR)/$(PARSDIR)/env_var_handling.c \
		$(SRCDIR)/$(PARSDIR)/envp_check.c \
		$(SRCDIR)/$(PARSDIR)/expand_variables.c \
		$(SRCDIR)/$(PARSDIR)/parsing.c \
		$(SRCDIR)/$(PARSDIR)/quotes_handler.c \
		$(SRCDIR)/$(PARSDIR)/signal.c \
		$(SRCDIR)/$(PARSDIR)/lexer.c \
		$(SRCDIR)/$(PARSDIR)/token_utils.c \
		$(SRCDIR)/$(PARSDIR)/var_validation.c \
		$(SRCDIR)/$(UTILS)/free.c \
		$(SRCDIR)/$(UTILS)/errors.c \
		$(SRCDIR)/$(UTILS)/tests.c

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

.PHONY: all clean fclean re
