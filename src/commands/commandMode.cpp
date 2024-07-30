/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandMode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:36:14 by hubourge          #+#    #+#             */
/*   Updated: 2024/07/30 17:15:38 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

int	pushInQueue(std::vector<std::string> &argSplit, std::queue<std::string> &modeQueue, Client &client);

// MODE <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]
// — i : Définir/supprimer le canal sur invitation uniquement
// — t : Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
// — k : Définir/supprimer la clé du canal (mot de passe)
// — o : Donner/retirer le privilège de l’opérateur de canal
// — l : Définir/supprimer la limite d’utilisateurs pour le canal
void	commandMode(const std::string &arg, Client &client, Server &server)
{
	std::vector<void (*)(const std::string &, Client &, Server &, Channel &, std::string &, std::string &)>	functmode;
	std::vector<std::string>																				argSplit;
	std::queue<std::string>																					modeQueue;
	std::string																								allowedOption = "itkol";

	argSplit = ft_split(arg, ' ');
	if(argSplit.size() < 1)
	{
		client.sendInfo(0, 461, "MODE :Not enough parameters");
		return ;
	}
	if (server.getChannel(argSplit[0], 0) == 0)
	{
		client.sendInfo(0, 403, argSplit[0] + " :No such channel");
		return ;
	}
	Channel *channel = server.getChannel(argSplit[0], 0);
	if (!channel->isOnChannel(&client))
	{
		client.sendInfo(0, 442, argSplit[0] + " :You're not on that channel");
		return ;
	}
	if (argSplit.size() == 1)
	{
		client.sendInfo(channel, 324, channel->getMode());
		return ;
	}
	if (pushInQueue(argSplit, modeQueue, client))
		return ;
	functmode.push_back(commandModeI);
	functmode.push_back(commandModeT);
	functmode.push_back(commandModeK);
	functmode.push_back(commandModeO);
	functmode.push_back(commandModeL);
	while (!modeQueue.empty())
	{
		std::string optionc = modeQueue.front();
		std::string arg = "";
		modeQueue.pop();
		for (size_t i = 0; i < optionc.length(); i++)
		{
			if (optionc[i] == '+' || optionc[i] == '-')
				continue ;
			if (allowedOption.find(optionc[i]) == std::string::npos)
			{
				client.sendInfo(0, 472, optionc + " :is unknown mode char to me for " + argSplit[0]);
				return ;
			}
			if (!modeQueue.empty() && arg.empty())
			{
				arg = modeQueue.front();
				modeQueue.pop();
			}
			functmode[allowedOption.find(optionc[i])](arg, client, server, *channel, optionc, arg);
		}
	}

}

/*--------------------------------- Options ----------------------------------*/
void	commandModeI(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt, std::string &cmdArg)
{
	(void) cmdArg;
	if (!chnl.isOperator(&client))
	{
		client.sendInfo(&chnl, 482, " :More privileges needed");
		return ;
	}
	if (cmdOpt[0] == '+')
		chnl.setInviteOnly(true, &client);
	else if (cmdOpt[0] == '-')
		chnl.setInviteOnly(false, &client);
}

void	commandModeT(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt, std::string &cmdArg)
{
	(void) cmdArg;
	if (!chnl.isOperator(&client))
	{
		client.sendInfo(&chnl, 482, ":More privileges needed");
		return ;
	}
	if (cmdOpt[0] == '+')
		chnl.setTopicOperatorOnly(true, &client);
	else if (cmdOpt[0] == '-')
		chnl.setTopicOperatorOnly(false, &client);
}

void	commandModeK(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt, std::string &cmdArg)
{
	if (!chnl.isOperator(&client))
	{
		client.sendInfo(&chnl, 482, ":More privileges needed");
		return ;
	}
	if (cmdOpt[0] == '-')
		chnl.setPassword("");
	else if (chnl.getPassword() != "")
		return ;
	else if (cmdOpt[0] == '+')
	{
		if (cmdArg.empty())
		{
			client.sendInfo(&chnl, 461, "Mode: Not enough parameters"); // c'est bon ce message tom ?
			return ;
		}
		chnl.setPassword(cmdArg);
		cmdArg.clear();
	}
}

void	commandModeO(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt, std::string &cmdArg)
{
	(void) cmdArg;
	if (!chnl.isOperator(&client))
	{
		client.sendInfo(&chnl, 482, ":More privileges needed");
		return ;
	}
	if (cmdOpt[0] == '+')
		chnl.setTopicOperatorOnly(true, &client);
	else if (cmdOpt[0] == '-')
		chnl.setTopicOperatorOnly(false, &client);
}

void	commandModeL(const std::string &arg, Client &client, Server &server, Channel &chnl, std::string &cmdOpt, std::string &cmdArg)
{
	if (!chnl.isOperator(&client))
	{
		client.sendInfo(&chnl, 482, ":More privileges needed");
		return ;
	}
	if (cmdOpt[0] == '+')
	{
		if (cmdArg.empty())
		{
			client.sendInfo(&chnl, 461, "MODE :Not enough parameters");
			return ;
		}
		if (stdStringToLongUnsignedInt(cmdArg) > MAX_CHANNEL_USER)
			chnl.setUserLimit(MAX_CHANNEL_USER, &client);
		else
			chnl.setUserLimit(stdStringToLongUnsignedInt(cmdArg), &client);
		cmdArg.clear();
	}
	else if (cmdOpt[0] == '-')
		chnl.setUserLimit(MAX_CHANNEL_USER);
}

/*---------------------------------- Utils -----------------------------------*/
bool verifOption(std::string option)
{
	std::string		allowedOption = "+-itkol";
	for (size_t i = 0; i < option.length(); i++)
	{
		if (allowedOption.find(option[i]) == std::string::npos)
			return false;
	}
	return true;
}

int	pushInQueue(std::vector<std::string> &argSplit, std::queue<std::string> &modeQueue, Client &client)
{
	for (unsigned int i = 1; i < argSplit.size(); i++)
	{
		if (argSplit[i][0] == '+' || argSplit[i][0] == '-')
		{
			if (verifOption(argSplit[i]))
				modeQueue.push(argSplit[i]);
			else
			{
				client.sendInfo(0, 472, argSplit[i] + " :is unknown mode char to me for " + argSplit[0]);
				return 1;
			}
		}
		else
			modeQueue.push(argSplit[i]);
	}
	return 0;
}
