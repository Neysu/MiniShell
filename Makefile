NAME = minishell
CC = clang
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
FLAGS = -lreadline
LIB = libft/libft.a
FT_PRINTF = ft_printf/ft_printf.a
SRCDIR = sources
EXECDIR = exec
PARSDIR = parsing
BUILTDIR = builtins
SRC = $(SRCDIR)/minishell.c \
		$(SRCDIR)/get_env.c \
		$(SRCDIR)/$(EXECDIR)/exec.c \
		$(SRCDIR)/$(EXECDIR)/exec_utils.c\
		$(SRCDIR)/$(EXECDIR)/redirect.c \
		$(SRCDIR)/$(BUILTDIR)/exit.c \
		$(SRCDIR)/$(BUILTDIR)/cd.c \
		$(SRCDIR)/$(BUILTDIR)/echo.c \
		$(SRCDIR)/$(BUILTDIR)/env.c \
		$(SRCDIR)/$(BUILTDIR)/pwd.c \
		$(SRCDIR)/$(BUILTDIR)/unset.c \
		$(SRCDIR)/$(BUILTDIR)/export.c \
		$(SRCDIR)/$(BUILTDIR)/builtins.c \
		$(SRCDIR)/$(BUILTDIR)/builtins_utils.c \
		$(SRCDIR)/$(PARSDIR)/parsing.c \
		$(SRCDIR)/$(PARSDIR)/lexer.c \
		$(SRCDIR)/$(PARSDIR)/envp_check.c \

OBJ := $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIB) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(FT_PRINTF) $(LIB) $(FLAGS)

$(LIB):
	$(MAKE) -C libft

$(FT_PRINTF):
	$(MAKE) -C ft_printf

clean:
	$(MAKE) clean -C libft
	$(MAKE) clean -C ft_printf
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft
	$(MAKE) fclean -C ft_printf

re: fclean all

.PHONY: all clean fclean re
