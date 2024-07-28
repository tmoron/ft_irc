/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandPrivMsg.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:27:31 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/29 00:41:27 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include.hpp"
#include "commands.hpp"

void	commandPrivMsg(const std::string &arg, Client &client, Server &server)
{	
	std::vector<std::string> arg_split;
	Channel *channel;
	Client *client_dest;

	arg_split = ft_split_irc(arg);
	if(arg_split.size() == 0)
	{
		client.sendInfo(0, 411, ":No recipient given PRIVMSG");
		return;
	}
	if(arg_split.size() == 1)
	{
		client.sendInfo(0, 412, ":No text to send");
		return;
	}
	if(arg_split[0][0] == '#')
	{
		channel = server.getChannel(arg_split[0], 0 ,0);
		if(!channel)
		{
			client.sendInfo(0, 404, arg_split[0] + " :Cannot send to channel");
			return;
		}
		channel->sendMsg(client, arg_split[1]);
	}
	else
	{
		client_dest = server.getClient(arg_split[0]);
		if(!client_dest)
		{
			client.sendInfo(0, 401, arg_split[0] + " :No such nick/channel");
			return ;
		}
		client_dest->sendMsg(client, arg_split[0], arg_split[1]);
	}
}
