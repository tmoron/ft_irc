/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandNick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:24:49 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/29 00:50:03 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include.hpp"
#include "commands.hpp"

void	commandNick(const std::string &arg, Client &client, Server &server)
{
	if(!arg.length())
	{
		client.sendInfo(0, 431, ":No nickname given");
		return ;
	}
	if (!server.getClient(arg))
		client.setNick(arg);
	else
		client.sendInfo(0, 433, arg + " :Nickname is already in use");

}
