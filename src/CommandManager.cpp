/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:02:43 by copilot           #+#    #+#             */
/*   Updated: 2024/07/25 18:44:06 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandManager.hpp"

/*------------------------------- Constructors -------------------------------*/
CommandManager::CommandManager()
{
}

CommandManager::~CommandManager()
{
}

/*--------------------------------- Methods ----------------------------------*/
CommandManager &CommandManager::addCommand(std::string cmdName, void (*funct)(const std::string &, Client &, Server &))
{
	this->_cmdNames.push_back(cmdName);
	this->_cmdFuncts.push_back(funct);
	return (*this);
}

void CommandManager::execCommand(std::string cmdName, const std::string &arg, Client &client, Server &server)
{
	for (size_t i = 0; i < this->_cmdNames.size(); i++)
	{
		if (this->_cmdNames[i] == cmdName)
		{
			this->_cmdFuncts[i](arg, client, server);
			return ;
		}
	}
	writeError(client, 0, 421, cmdName + std::string(" :Unknown command"));
}

void	commandPass(const std::string &pass, Client &clt, Server &srv)
{
	if(pass.length() == 0)
	{
		writeError(clt, 0, 461, "PASS :Not enough parameters");
		return ;
	}
	if(clt.isRegistered())
	{
		writeError(clt, 0, 462, ":You may not reregister");
		return ;
	}
	if (srv.getPassword().compare(pass))
	{
		clt.setLoggedIn(true);
		std::cout << "Client " << clt.getNick() << " as a valid password" << std::endl;
	}
	else
	{
		std::cout << "Client " << clt.getNick() << " as a wrong password" << std::endl;
		writeError(clt, 0, 464, ":Password incorect" );
	}
}

void	commandKick(const std::string &arg, Client &client, Server &server)
{
	// server;
	// unsigned int	i;
	// for (i = 0; i < chnlClt.size() - 1; i++)
	// {
	// 	if (chnlClt.at(i) == &clt)
	// 	{
	// 		chnlClt.erase(chnlClt.begin() + i);
	// 		// KICK &Melbourne Matthew                 ;    Kick Matthew from &Melbourne
	// 		// KICK #Finnish John :Speaking English    ;    Kick John from #Finnish using "Speaking English" as the reason (comment).
	// 		// :WiZ KICK #Finnish John                 ;    KICK message from WiZ to remove John from channel #Finnish          // ce le suprime peut etre pas ca
	// 		std::cout << "Kick " << clt.getNick() << " from " << chnl.getName(); // c'est peut etre pas des std::cout mais au moins c'est la
	// 		if (msg.length() != 0)
	// 			std::cout << " using '" << msg << "' as the reason (comment).";
	// 		return ;
	// 	}
	// }
	// if (i == chnlClt.size())
	// 	writeError(clt, 0, 442, "<channel> :You're not on that channel");
	// 	// ERR_NOTONCHANNEL tom erreur ?
}


bool	alreadyUse(std::vector<Client*> &clients, Client *current, std::string nick)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i]->getNick() == nick && clients[i] != current)
			return true;
	}
	return false;
}

void	commandInvite(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string> arg_split = ft_split(arg, ' ');
	if (arg_split.size() < 3)
	{
		writeError(client, 0, 461, "INVITE :Not enough parameters");
		return ;
	}
	if (alreadyUse(server.getClients(), &client, arg_split[1]))
	{
		writeError(client, 0, 401, arg_split[1] + " :No such nick/channel");
		return ;
	}
	if (server.getChannel(arg_split[2], 0, 0) == 0)
	{
		writeError(client, 0, 403, arg_split[2] + " :No such channel");
		return ;
	}
	Channel *chnl = server.getChannel(arg_split[2], 0, 0);
	chnl->inviteInChannel(client, *server.getClient(arg_split[1]), *chnl);
}

void	commandTopic(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string> arg_split = ft_split(arg, ' ');
	if (arg_split.size() < 2)
	{
		writeError(client, 0, 461, "TOPIC :Not enough parameters");
		return ;
	}
	if (arg_split.size() == 2 && server.getChannel(arg_split[1], 0, 0))
	{
		Channel *chnl = server.getChannel(arg_split[1], 0, 0);
		// writeMessage(client, 0, 332, chnl->getName() + " :" + chnl->getTopic());
	}
	else if (arg_split.size() >= 3 && server.getChannel(arg_split[1], 0, 0))
	{
		Channel *chnl = server.getChannel(arg_split[1], 0, 0);
		chnl->setTopic(arg_split[2]);
	}
	else
		writeError(client, 0, 403, arg_split[1] + " :No such channel");
}

void	commandNick(const std::string &arg, Client &client, Server &server)
{
	if(!arg.length())
	{
		writeError(client, 0, 431, ":No nickname given");
		return ;
	}
	if(!client.getLoggedIn())
		return;
	std::cout << "nick command" << std::endl;
	if (!alreadyUse(server.getClients(), &client, arg))
		client.setNick(arg);
	else
		writeError(client, 0, 433, arg + " :Nickname is already in use");

}

void	commandUser(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string> arg_split;

	std::cout << "user command" << std::endl;
	if(client.isRegistered())
	{
		writeError(client, 0, 462, ":You may not reregister");
		return ;
	}
	arg_split = ft_split(arg, ' ');
	std::cout << "number of args : " << arg_split.size() << std::endl;
	if(arg_split.size() != 4)
		writeError(client, 0 ,461, "USER :Not enough parameters");
	client.setUser(arg);
}

void	sendMsgAllClientChannel(std::string msg, std::vector<Client*> cltChnl, Channel &chnl)
{
	for (unsigned int i = 0; i < cltChnl.size(); i++)
	{
		// transmettre le msg au client;
		// cltChnl.at(i);
	}
}

void	commandPrivMsg(const std::string &arg, Client &client, Server &server)
{
	//flemme (si quelqu'un d'autre vois ça , il y a la methode "sendMessage" pour envoyer un message, j'ai pas testé, j'ai la flemme aussi) // a bas bravo
}

void commandJoin(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string>	arg_split;
	std::string channel_name;
	Channel *channel;

	arg_split = ft_split(arg, ' ');
	if(arg_split.size() == 0)
		writeError(client, 0, 461, "JOIN :Not enough parameters");	
	channel_name = arg_split[1];
	channel = server.getChannel(channel_name, &client, 1);
	channel->addClient(&client);
}
