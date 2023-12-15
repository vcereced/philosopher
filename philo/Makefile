# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 19:41:54 by vcereced          #+#    #+#              #
#    Updated: 2023/06/21 16:52:42 by vcereced         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = $(wildcard ./*c)

OBJT = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread -g


all: $(NAME)

$(NAME): $(OBJT)
	$(CC) $(CFLAGS) $(OBJT) -o $(NAME)

clean:
	rm -f $(OBJT)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	@./philo 2 603 300 100 3
	
	

debug: all
	$(CC) -g  $(SRC) -o debug
	lldb ./debug 4 0 10000000000 1000

.PHONY: all clean fclean re runm