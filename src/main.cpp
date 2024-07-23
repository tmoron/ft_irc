/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:56:17 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/23 10:36:56 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"
#include "Client.hpp"

void	test_client(void)
{
	Client *clt = new Client();

	clt->setBuffer("/KICK example");
	
	delete clt;
}	

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		std::cerr << "Error : Wrong number of arguments" << std::endl;
		std::cerr << "	Usage: " << argv[0] << " <port> <password>" << std::endl;
		return(1);
	}
	Server *srv = new Server(std::string(argv[1]), std::string(argv[2]));

	// srv->listen();
	test_client();
	
	delete srv;
	return(0);
}
