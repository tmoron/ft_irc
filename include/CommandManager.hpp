/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:19:22 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/23 17:19:57 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CommandManager_HPP
#define CommandManager_HPP

#include<string>
#include<vector>

class CommandManager
{
    private:
        std::vector <std::string> _cmdNames;
        std::vector <void (*)()> _cmdFuncts;

    public:
        CommandManager();

		CommandManager &addCommand(std::string cmdName, void (*funct)());
		void 			execCommand(std::string cmdName);

        ~CommandManager();
};

#endif
