/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandKick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:25:58 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/31 16:03:56 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

// KICK <channel> <user> [<comment>]
// KICK &Melbourne Matthew                 ;    Kick Matthew from &Melbourne
// KICK #Finnish John :Speaking English    ;    Kick John from #Finnish using "Speaking English" as the reason (comment).
// :WiZ KICK #Finnish John ; KICK message from WiZ to remove John from channel #Finnish          // ce le suprime peut etre pas ca
void	commandKick(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string>	argSplit;

	argSplit = ft_split(arg, ' ');
	if(argSplit.size() < 2)
		client.sendInfo(0, 461, "KICK :Not enough parameters");

	std::vector<Channel*>		channels = server.getChannels();
	std::vector<std::string>	chnlName = ft_split(argSplit[0], ',');
	std::vector<std::string>	kickName = ft_split(argSplit[1], ',');
	std::string					reasonMsg;

	for (unsigned int i = 0; i < argSplit.size() - 2; i++)
	{
		reasonMsg += argSplit[i + 2];
		if (i < argSplit.size() - 3)
			reasonMsg += " ";
	}
	for (unsigned int i = 0; i < channels.size(); i++) // channels available
	{
		for (unsigned int j = 0; j < chnlName.size(); j++) // channel to kick
		{
			if (channels[i]->getName() == chnlName[j]) // channel found
			{
				for (unsigned int k = 0; k < kickName.size(); k++) // people to kick
				{
					if (!channels[i]->isOperator(&client)) // is not operator
					{
						client.sendInfo(channels[i], 482, ":More privileges needed");
						continue ;
					}
					std::stringstream ss;
					ss << ":" << client.getNick() << " ";
					ss << "KICK " << kickName[k] << " from " << channels[i]->getName();
					if (!reasonMsg.empty())
					 	ss << " :" << reasonMsg;
					channels[i]->sendStr(ss.str());
					channels[i]->delClient(kickName[k]);
				}
			}
		}
	}
}
