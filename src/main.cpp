/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:56:17 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/29 17:40:19 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "commands.hpp"
#include "include.hpp"

int	g_sig = 0;

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		std::cerr << "Error : Wrong number of arguments" << std::endl;
		std::cerr << "	Usage: " << argv[0] << " <port> <password>" << std::endl;
		return(1);
	}
	
	try
	{
		signal(SIGINT, Handler);
		Server *srv = new Server(std::string(argv[1]), std::string(argv[2]));
		srv->addCommand("PASS",commandPass, 0)
			.addCommand("NICK", commandNick, 0)
			.addCommand("USER", commandUser, 0)
			.addCommand("JOIN", commandJoin, 1)
			.addCommand("TOPIC", commandTopic, 1)
			.addCommand("WHO", commandWho, 1)
			.addCommand("PING", commandPing, 1)
			.addCommand("PRIVMSG",commandPrivMsg, 1)
			.addCommand("KICK", commandKick, 1)
			.addCommand("MODE", commandMode, 1)
			.addCommand("INVITE",commandInvite,1);
		srv->listen();
		
		delete srv;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}
