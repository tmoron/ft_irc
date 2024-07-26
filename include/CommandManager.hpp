/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:19:22 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/26 14:52:08 by hubourge         ###   ########.fr       */
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

	public:
		CommandManager();
		~CommandManager();

		CommandManager	&addCommand(std::string cmdName, void (*funct)(const std::string &, Client &, Server &));
		void			execCommand(std::string cmdName, const std::string &arg, Client &client, Server &server);
};

void	sendMsgAllClientChannel(std::string msg, std::vector<Client*> cltChnl, Channel &chnl);
void	commandPass(const std::string &pass, Client &clt, Server &srv);
void	commandNick(const std::string &arg, Client &client, Server &server);
void	commandUser(const std::string &arg, Client &client, Server &server);
void	commandPrivMsg(const std::string &arg, Client &client, Server &server);
void	commandJoin(const std::string &arg, Client &client, Server &server);
void	commandKick(const std::string &arg, Client &client, Server &server);
void	commandTopic(const std::string &arg, Client &client, Server &server);
void	commandMode(const std::string &arg, Client &client, Server &server);
void	commandInvite();
void	commandAddChannel();
void	commandDelChannel();


#endif
