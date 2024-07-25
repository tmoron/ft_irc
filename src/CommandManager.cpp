/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:02:43 by copilot           #+#    #+#             */
/*   Updated: 2024/07/25 10:40:03 by hubourge         ###   ########.fr       */
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
	if (srv.getPassword() == pass)
	{
		clt.setLoggedIn(true);
		std::cout << "Client " << clt.getNick() << " as a valid password" << std::endl;
	}
	else // peut etre throw une exeption //non //d'accord
	{
		std::cout << "Client " << clt.getNick() << " as a wrong password" << std::endl;
		writeError(clt, 0, 464, ":Password incorect" );
	}
}

void	commandKick(Channel &chnl, Client &clt, std::string msg)
{
	//cette fonction ne prends pas le bons parametres et channel ne peut pas être null, c'est une reference
	//if (!chnl)
	 //	writeError(clt,0, 403, "#AAAAAAAAAAAAAAAAAA :No such channel");
	std::vector<Client*> chnlClt = chnl.getClients();
	unsigned int i;
	for (i = 0; i < chnlClt.size() - 1; i++)
	{
		if (chnlClt.at(i) == &clt)
		{
			chnlClt.erase(chnlClt.begin() + i);
			if (msg.length() != 0)
				std::cout << msg << std::endl;
			return ;
		}
	}
	if (i == chnlClt.size())
		writeError(clt, 0, 442, "<channel> :You're not on that channel");
		// ERR_NOTONCHANNEL tom erreur ?
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
