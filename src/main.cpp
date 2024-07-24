/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:56:17 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/24 15:27:40 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include <iostream>
#include <string>
#include <sstream>





// void	test_client(Server *srv)
// {
// 	std::string user;

// 	for (int i = 0; i < 100; i++)
// 	{
// 		std::stringstream ss;
// 		ss << "tom_" << i;
// 		user = ss.str();
// 		try {
// 			srv->setClient(Client(i, user, "tomorom"));
// 		}
// 		catch (std::exception &e) {std::cerr << e.what() << std::endl;}
// 	}
// 	std::cout << " ================= Show client =================" << std::endl;
// 	srv->showClient();
// }

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		std::cerr << "Error : Wrong number of arguments" << std::endl;
		std::cerr << "	Usage: " << argv[0] << " <port> <password>" << std::endl;
		return(1);
	}
	Server *srv = new Server(std::string(argv[1]), std::string(argv[2]));

	srv->listen();
	// test_client(srv);

	delete srv;
	return(0);
}
