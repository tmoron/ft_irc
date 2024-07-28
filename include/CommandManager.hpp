/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:19:22 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/29 00:47:38 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include "Channel.hpp"

#ifndef COMMANDMANAGER_HPP
# define COMMANDMANAGER_HPP

# include "include.hpp"

class Server;
class Client;
class Channel;

class CommandManager
{
	private:
		std::vector <std::string>	_cmdNames;
		std::vector <void (*)(const std::string &, Client &, Server &)>	_cmdFuncts;
		std::vector<bool> _cmdRequireRegister;

	public:
		CommandManager();
		~CommandManager();

		CommandManager	&addCommand(std::string cmdName, void (*funct)(const std::string &, Client &, Server &), bool requireRegister);
		void			execCommand(std::string cmdName, const std::string &arg, Client &client, Server &server);

};

#endif
