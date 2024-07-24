/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:19:22 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/24 15:43:39 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDMANAGER_HPP
# define COMMANDMANAGER_HPP

#include "include.hpp"
#include <string>
#include <vector>
#include "Server.hpp"
#include "Client.hpp"

class Client;
class Server;

class CommandManager
{
        private:
        std::vector <std::string> _cmdNames;
        std::vector <void (*)(const std::string &, Client &, Server &)> _cmdFuncts;

    public:
        CommandManager();
        ~CommandManager();

        CommandManager &addCommand(std::string cmdName, void (*funct)(const std::string &, Client &, Server &));
        void            execCommand(std::string cmdName, const std::string &arg, Client &client, Server &server);
};

void	commandPass(std::string pass, Client &clt, Server &srv);
void	commandNick(const std::string &arg, Client &client, Server &server);
void	commandUser(const std::string &arg, Client &client, Server &server);
#endif
