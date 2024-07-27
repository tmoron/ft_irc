/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:56:17 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/27 15:19:27 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
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
		srv->addCommand("PASS",commandPass)
			.addCommand("NICK", commandNick)
			.addCommand("USER", commandUser)
			.addCommand("JOIN", commandJoin)
			.addCommand("TOPIC", commandTopic)
			.addCommand("WHO", commandWho)
			.addCommand("PING", commandPing)
			.addCommand("PRIVMSG",commandPrivMsg)
			.addCommand("KICK", commandKick);
		srv->listen();
		
		delete srv;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}
