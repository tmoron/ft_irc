# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 16:47:55 by tomoron           #+#    #+#              #
#    Updated: 2024/08/01 15:05:10 by pageblanche      ###   ########.fr        #
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

SRCS_BONUS =	bonus/main.cpp\
				bonus/Bot.cpp\
				bonus/utils.cpp\
				bonus/GPTHistory.cpp

OBJS = $(SRCS:.cpp=.o)

OBJS_BONUS = $(SRCS_BONUS:.cpp=.o)

FLAGS = -g -Wall -std=c++98 -Iinclude #-Wextra -Werror

all:
	@make --no-print-directory -j16 $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

bonus: bot

bot: $(OBJS_BONUS)
	$(CC) $(FLAGS) $(OBJS_BONUS) -o bot

.cpp.o:
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) bot

re: fclean all

.PHONY: clean all re fclean bonus
