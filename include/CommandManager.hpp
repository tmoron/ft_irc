/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:19:22 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/24 16:35:53 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include "Chanel.hpp"

#ifndef COMMANDMANAGER_HPP
# define COMMANDMANAGER_HPP

# include "include.hpp"

class Server;
class Client;
class Chanel;

class CommandManager
{
	private:
		std::vector <std::string>	_cmdNames;
		std::vector <void (*)(const std::string &, Client &, Server &)>	_cmdFuncts;

	public:
		CommandManager();
		~CommandManager();

		CommandManager	&addCommand(std::string cmdName, void (*funct)(const std::string &, Client &, Server &));
		void			execCommand(std::string cmdName, const std::string &arg, Client &client, Server &server);
		void			commandPass(std::string pass, Client &clt, Server &srv);
		void			sendMsgAllClientChannel(std::string msg, std::vector<Client*> cltChnl, Chanel &chnl);
};

void	commandPass(const std::string &pass, Client &clt, Server &srv);
void	commandNick(const std::string &arg, Client &client, Server &server);
void	commandUser(const std::string &arg, Client &client, Server &server);

#endif
