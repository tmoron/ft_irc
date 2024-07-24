/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:55:07 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/24 15:44:12 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Client.hpp"
#include "include.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <vector>
# include <iostream>
# include <sstream>
# include <poll.h>
#include "CommandManager.hpp"

class Client;
class CommandManager;

class Server {
	private:
		int						_servSocketFd;
		std::string				_password;
		std::vector<Client*>	_clients;
		struct pollfd			*_pollfds;
		CommandManager			_commandManager;

		int	init_socket(uint16_t port);
		void update_pollfds();

	public:
		Server(std::string port, std::string password); // Default constructor
		~Server(void);

		void		setServSocketFd(int servSocketFd);
		void		setPassword(std::string password);
		// void		setClient(Client client);

		int						getServSocketFd();
		std::string				getPassword();
		std::vector<Client*>	&getClients();

		void		showClient(void);
		void		listen(void);
		void		addClient(int a);
		void		receiveData(void);
		void		exec(const std::string &full_cmd, Client &client);

		class OutOfRangeClientExeption : public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Index out of range";
				}
		};
};

#endif
