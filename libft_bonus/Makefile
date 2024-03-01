NAME = libft.a

FLAGS = -Wall -Wextra -Werror -g

SRCS = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_tolower.c ft_toupper.c ft_atoi.c ft_memcmp.c ft_strncmp.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memcpy.c ft_memchr.c ft_calloc.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_putnbr_fd.c ft_striteri.c ft_strlen.c ft_strlcat.c ft_strlcpy.c

SRCS_BONUS = ft_lstsize.c ft_lstadd_back.c ft_lstadd_front.c ft_lstiter.c ft_lstdelone.c ft_lstclear.c ft_lstlast.c ft_lstnew.c ft_lstmap.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

.c.o:
	cc $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	ar cr $(NAME) $(OBJS)

all: $(NAME)

bonus: $(OBJS_BONUS)
	ar cr $(NAME) $(OBJS_BONUS)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all
