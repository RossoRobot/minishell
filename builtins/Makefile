# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 14:40:06 by mvolgger          #+#    #+#              #
#    Updated: 2024/04/13 15:31:41 by mvolgger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# makefile

NAME = builtinstester

SRCS = cd.c pwd.c export.c libft_helpers.c main.c env_dup.c list_init.c itoa.c \
		list_to_arr.c

CFLAGS = -g #-Wall -Wextra -Werror 

CC = cc

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c  builtins.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) builtins.h 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean 
	$(MAKE) all

.PHONY: all clean fclean re
	
