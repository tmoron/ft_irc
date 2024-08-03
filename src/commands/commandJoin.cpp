/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:24:15 by tomoron           #+#    #+#             */
/*   Updated: 2024/08/03 15:00:30 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

void commandJoin(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string>	arg_split;

	arg_split = ft_split_irc(arg);
	if(arg_split.size() == 0)
		client.sendInfo(0, 461, "JOIN :Not enough parameters");

	Channel						*channel;
	std::vector<std::string>	channel_names = ft_split(arg_split[0], ',');
	std::vector<std::string>	keys;

	if (arg_split.size() > 1)
		keys = ft_split(arg_split[1], ',');

	for (unsigned int i = 0; i < channel_names.size(); i++)
	{
		channel = server.getChannel(channel_names[i], 1);
		if (!channel)
			continue ;
		if(channel->addClient(&client, keys.size() > i ? keys[i] : ""))
		{
			channel->sendStr(":" + client.getIdentifier() + " JOIN " + channel_names[i]);
			if(channel->getTopic().length())
				client.sendInfo(channel, 332, channel->getTopic());
			else
				client.sendInfo(channel, 332, ":No topic is set");
			client.sendInfo(0, 353, "= " + channel_names[i] + " :" + channel->getNames());
			client.sendInfo(0, 366, channel_names[i] + " :End of /NAMES list");
		}
	}
}
