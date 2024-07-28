/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:31:51 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/29 00:42:21 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "Client.hpp"
#include "Server.hpp"
#include "Channel.hpp"

void	commandPass(const std::string &pass, Client &clt, Server &srv);
void	commandNick(const std::string &arg, Client &client, Server &server);
void	commandUser(const std::string &arg, Client &client, Server &server);
void	commandPrivMsg(const std::string &arg, Client &client, Server &server);
void	commandJoin(const std::string &arg, Client &client, Server &server);
void	commandKick(const std::string &arg, Client &client, Server &server);
void	commandTopic(const std::string &arg, Client &client, Server &server);
void	commandMode(const std::string &arg, Client &client, Server &server);
void	commandModeI(const std::string &arg, Client &client, Server &server);
void	commandModeT(const std::string &arg, Client &client, Server &server);
void	commandModeK(const std::string &arg, Client &client, Server &server);
void	commandModeO(const std::string &arg, Client &client, Server &server);
void	commandModeL(const std::string &arg, Client &client, Server &server);
void	commandWho(const std::string &arg, Client &client, Server &server);
void	commandPing(const std::string &arg, Client &client, Server &server);

#endif
