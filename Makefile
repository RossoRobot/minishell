# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrauer <kbrauer@student.42vienna.com >    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/01 14:00:52 by kbrauer           #+#    #+#              #
#    Updated: 2024/03/09 17:50:35 by kbrauer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -lreadline -g #-Wall -Wextra -Werror 

SRCS_DIR = .
LIBFT_DIR = ./libft_bonus
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = $(SRCS_DIR)/main.c $(SRCS_DIR)/utils.c $(SRCS_DIR)/free.c
	
OBJS = $(SRCS:.c=.o)

.c.o:
	cc $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
		cc  $(FLAGS) -o $@ $(OBJS) -L. $(LIBFT) 

$(LIBFT):
		make -C $(LIBFT_DIR) all

all: $(NAME)

clean:
	rm -f $(OBJS) $(LIBFT_DIR)/*.o

fclean: clean
	rm -f $(NAME) ./libft_bonus/libft.a

re: fclean all

.PHONY: all, clean, fclean, re
