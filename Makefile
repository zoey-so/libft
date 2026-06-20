CC = cc
CFLAGS += -Wall -Wextra -Werror -I .
SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c  \
		ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c  \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c  \
		ft_strrchr.c ft_tolower.c ft_toupper.c ft_ctype_data.c ft_lstadd_front.c \
		ft_lstadd_back.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
		ft_lstmap.c ft_lstsize.c ft_lstnew.c
BON = ft_substr_bonus.c ft_strtrim_bonus.c ft_strmapi_bonus.c ft_strjoin_bonus.c \
		ft_striteri_bonus.c ft_putchar_fd_bonus.c ft_putendl_fd_bonus.c \
		ft_putnbr_fd_bonus.c ft_putstr_fd_bonus.c ft_split_bonus.c ft_itoa_bonus.c
OBJECTS = $(SOURCES:.c=.o)
BON_OBJ = $(BON:.c=.o)
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJECTS) $(BON_OBJ) libft_bonus.h
	ar rcs $(NAME) $(OBJECTS) $(BON_OBJ)

clean:
	rm -f $(OBJECTS) $(BON_OBJ)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
