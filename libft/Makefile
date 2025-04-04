# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Library name
NAME = libft.a

# Source files
SRC = \
	ft_is/ft_isalnum.c \
	ft_is/ft_isalpha.c \
	ft_is/ft_isascii.c \
	ft_is/ft_isdigit.c \
	ft_is/ft_isprint.c \
	ft_mem/ft_memchr.c \
	ft_mem/ft_memcmp.c \
	ft_mem/ft_memcpy.c \
	ft_mem/ft_memmove.c \
	ft_mem/ft_memset.c \
	ft_mem/ft_memdel.c \
	ft_put/ft_putchar_fd.c \
	ft_put/ft_putendl_fd.c \
	ft_put/ft_putnbr_fd.c \
	ft_put/ft_putstr_fd.c \
	ft_put/ft_puttab_fd.c \
	ft_str/ft_strchr.c \
	ft_str/ft_strcmp.c \
	ft_str/ft_strdup.c \
	ft_str/ft_striteri.c \
	ft_str/ft_strjoin.c \
	ft_str/ft_strlcat.c \
	ft_str/ft_strlcpy.c \
	ft_str/ft_strlen.c \
	ft_str/ft_strmapi.c \
	ft_str/ft_strncmp.c \
	ft_str/ft_strnstr.c \
	ft_str/ft_strrchr.c \
	ft_str/ft_strsep.c \
	ft_str/ft_strtrim.c \
	ft_str/ft_substr.c \
	ft_str/ft_strndup.c \
	ft_str/ft_strnext.c \
	ft_to/ft_tolower.c \
	ft_to/ft_toupper.c \
	free/ft_free_arr.c \
	array/ft_arrdup.c \
	array/ft_arrlen.c \
	get_next_line/get_next_line.c \
	other/ft_split.c \
	other/ft_atoi.c \
	other/ft_calloc.c \
	other/ft_realloc.c \
	other/ft_itoa.c \
	other/ft_bzero.c \

# Object files
OBJ = $(SRC:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
