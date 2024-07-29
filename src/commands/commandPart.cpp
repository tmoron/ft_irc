/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandPart.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:43:58 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/29 21:25:39 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"
#include "include.hpp"

void commandPart(const std::string &arg, Client &client, Server &server)
{
	std::vector<std::string>	arg_list = ft_split_irc(arg);
	std::vector<std::string>	channel_list;
	Channel						*channel;

	if(arg_list.size() == 0)
	{
		client.sendInfo(0, 461, "PART :Not enough parameters");
		return;
	}
	channel_list = ft_split(arg_list[0],',');
	for(unsigned int i = 0; i < channel_list.size(); i++)
	{
		channel = server.getChannel(channel_list[i], 0);
		if(!channel)
			client.sendInfo(channel, 403,":No such channel");
		else if(!channel->isOnChannel(&client))
			client.sendInfo(channel, 442, ":You're not on that channel");
		else if(arg_list.size() >= 2)
			channel->delClient(&client, arg_list[1]);
		else
			channel->delClient(&client, "");
	}

}
