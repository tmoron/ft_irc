/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandKick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:25:58 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/29 00:41:27 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include.hpp"
#include "commands.hpp"

// KICK <channel> <user> [<comment>]
// KICK &Melbourne Matthew                 ;    Kick Matthew from &Melbourne
// KICK #Finnish John :Speaking English    ;    Kick John from #Finnish using "Speaking English" as the reason (comment).
// :WiZ KICK #Finnish John ; KICK message from WiZ to remove John from channel #Finnish          // ce le suprime peut etre pas ca
void	commandKick(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string>	argSplit;

	argSplit = ft_split(arg, ' ');
	if(argSplit.size() < 3)
		client.sendInfo(0, 461, "KICK :Not enough parameters");
	if (argSplit[0].find(':')) // jsp il faut se referer a la doc
		return ;

	std::vector<Channel*>		channels = server.getChannels();
	std::vector<std::string>	chnlName = ft_split(argSplit[1], ',');
	std::vector<std::string>	kickName = ft_split(argSplit[2], ',');
	std::string					reasonMsg;

	if (argSplit.size() >= 4)
		reasonMsg = argSplit[3];
	for (unsigned int i = 0; i < channels.size() - 1; i++) // channels available
	{
		for (unsigned int j = 0; j < chnlName.size() - 1; j++) // channel to kick
		{
			if (channels[i]->getName() == chnlName[j]) // channel found
			{
				for (unsigned int k = 0; k < kickName.size() - 1; k++) // people to kick
				{
					if (!channels[i]->isOperator(&client)) // is not operator
					{
						client.sendInfo(0, 482, "KICK :More privileges needed");
						continue ;
					}
					channels[i]->delClient(kickName[k]);
					std::cout << "Kick " << kickName[k] << " from " << channels[i]->getName();
					if (!reasonMsg.empty())
						std::cout << " using " << reasonMsg << std::endl;
				}
			}
		}
	}
}
