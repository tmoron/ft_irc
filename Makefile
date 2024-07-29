# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 16:47:55 by tomoron           #+#    #+#              #
#    Updated: 2024/07/29 23:39:39 by tomoron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CC = c++

SRCS =	src/main.cpp\
		src/Channel.cpp\
		src/utils.cpp\
		src/Client.cpp\
		src/CommandManager.cpp\
		src/Server.cpp\
		src/commands/commandWho.cpp\
		src/commands/commandKick.cpp\
		src/commands/commandInvite.cpp\
		src/commands/commandMode.cpp\
		src/commands/commandNick.cpp\
		src/commands/commandPing.cpp\
		src/commands/commandPass.cpp\
		src/commands/commandJoin.cpp\
		src/commands/commandUser.cpp\
		src/commands/commandPrivMsg.cpp\
		src/commands/commandTopic.cpp\
		src/commands/commandPart.cpp\
		src/commands/commandQuit.cpp\

OBJS = $(SRCS:.cpp=.o)

FLAGS = -g -Wall -std=c++98 -Iinclude #-Wextra -Werror

all:
	@make --no-print-directory -j16 $(NAME)

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
