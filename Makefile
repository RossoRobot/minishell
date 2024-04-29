# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/01 14:00:52 by kbrauer           #+#    #+#              #
#    Updated: 2024/04/29 10:36:46 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -g  #-Wall -Wextra -Werror 

MAIN_DIR = ./main

BI_DIR =./builtins

EXEC_DIR = ./execute

SRCS = $(MAIN_DIR)/main.c $(MAIN_DIR)/utils.c $(MAIN_DIR)/utils2.c \
	$(MAIN_DIR)/free.c $(MAIN_DIR)/define_type.c $(BI_DIR)/cd.c \
	$(BI_DIR)/env_dup.c $(BI_DIR)/export.c $(BI_DIR)/itoa.c \
	$(BI_DIR)/libft_helpers.c $(BI_DIR)/list_init.c \
	$(BI_DIR)/list_to_arr.c $(BI_DIR)/pwd.c $(MAIN_DIR)/parse.c \
	$(EXEC_DIR)/execute.c $(BI_DIR)/execute_builtins.c \
	
	
OBJS = $(SRCS:.c=.o)

.c.o:
	cc -g -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
		cc $(FLAGS) -o $@ $(OBJS) -lreadline

$(LIBFT):
		make -C all

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all, clean, fclean, re
