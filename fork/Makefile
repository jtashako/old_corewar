#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smonroe <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/22 13:16:37 by smonroe           #+#    #+#              #
#    Updated: 2019/02/22 13:16:40 by smonroe          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = reg

SRC = test.c

CC = gcc -Wall -Werror -Wextra -I ../libft/ -L ../libft/ -lft

all: $(NAME)

$(NAME):
	$(CC) -o $(NAME) $(SRC)

clean:
	/bin/rm -rf *~ \#*\# a.out* *.swp *.gch

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

fsan:
	$(CC) $(SRC) -o $(NAME) -g -fsanitize=address

