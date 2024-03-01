# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrauer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/01 14:00:52 by kbrauer           #+#    #+#              #
#    Updated: 2024/03/01 14:00:55 by yourLogin        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -lreadline -g#-Wall -Wextra -Werror 

SRCS_DIR = .
LIBFT_DIR = ./libft_bonus
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = $(SRCS_DIR)/main.c
	
OBJS = $(SRCS:.c=.o)

.c.o:
	cc $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
		cc  $(FLAGS) -o $@ $(OBJS) -L. ./libft_bonus/libft.a

$(LIBFT):
		make -C $(LIBFT_DIR) all

all: $(NAME)

clean:
	rm -f $(OBJS) $(LIBFT_DIR)/*.o

fclean: clean
	rm -f $(NAME) ./libft_bonus/libft.a

re: fclean all

.PHONY: all, clean, fclean, re
