/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:19:22 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/24 15:01:38 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CommandManager_HPP
#define CommandManager_HPP

#include<string>
#include<vector>
#include "Client.hpp"
#include "Server.hpp"

class Server;
class Client;

class CommandManager
{
    private:
        std::vector <std::string> _cmdNames;
        std::vector <void (*)(const std::string &, Client &, Server &)> _cmdFuncts;

    public:
        CommandManager();

		CommandManager &addCommand(std::string cmdName, void (*funct)(const std::string &, Client &, Server &));
		void 			execCommand(std::string cmdName, const std::string &arg, Client &client, Server &server);

        ~CommandManager();
};

#endif
