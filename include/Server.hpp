/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:55:07 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/29 21:12:17 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVER_HPP
# define SERVER_HPP

#include "include.hpp"
#include "Client.hpp"
#include "CommandManager.hpp"
#include "Channel.hpp"

class Client;
class CommandManager;

class Server {
	private:
		int						_servSocketFd;
		std::string				_password;
		std::vector<Client*>	_clients;
		struct pollfd			*_pollfds;
		CommandManager			_commandManager;
		std::vector<Channel*>	_channels;

		int		init_socket(uint16_t port);
		void	update_pollfds();

	public:
		Server(std::string port, std::string password); // Default constructor
		~Server(void);

		void					setServSocketFd(int servSocketFd);
		void					setPassword(std::string password);

		void					sendStr(std::string message);
		int						getServSocketFd();
		std::string				getPassword();
		std::vector<Client*>	&getClients();
		Client					*getClient(std::string nick);
		std::vector<Channel*>	getChannels();

		void		addClient(int a);
		Channel		*getChannel(std::string &name, int create);
		void		delClient(Client *client);

		void		delChannel(std::string name);
		void		listen(void);
		void		receiveData(void);
		void		exec(std::string full_cmd, Client &client);
		Server		&addCommand(std::string cmdName, void (*funct)(const std::string &, Client &, Server &), bool requiireRegister);

};

#endif
