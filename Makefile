# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomoron <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 16:47:55 by tomoron           #+#    #+#              #
#    Updated: 2024/07/22 18:00:20 by tomoron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CC = c++

SRCS =	src/main.cpp\
		src/Server.cpp

OBJS = $(SRCS:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -std=c++98 -Iinclude

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

.cpp.o:
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean
