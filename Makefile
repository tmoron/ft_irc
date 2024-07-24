# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 16:47:55 by tomoron           #+#    #+#              #
#    Updated: 2024/07/24 16:51:35 by hubourge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CC = c++

SRCS =	src/main.cpp\
		src/Server.cpp\
		src/Client.cpp\
		src/CommandManager.cpp\
		src/Channel.cpp\

OBJS = $(SRCS:.cpp=.o)

FLAGS = -g -Wall -std=c++98 -Iinclude #-Wextra -Werror

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
