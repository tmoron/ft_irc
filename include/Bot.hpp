/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 00:51:45 by tomoron           #+#    #+#             */
/*   Updated: 2024/08/01 14:59:37 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GPTHistory.hpp"
#include "include.hpp"

#ifndef BOT_HPP
# define BOT_HPP

class Bot
{
	private:
		int 						_connFd;
		struct pollfd 				_pollfd;
		std::string 				_buffer;
		bool						_stop;
		std::vector<GPTHistory>		_history;

	public:
		Bot(std::string ip, std::string port);
		~Bot();
		int 	init_connection(const char *ip, uint16_t port);
		void	send(std::string str);
		void 	listen();
		void	login(std::string pass);
};

#endif

