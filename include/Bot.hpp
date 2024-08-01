/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 00:51:45 by tomoron           #+#    #+#             */
/*   Updated: 2024/08/01 17:45:54 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.hpp"
#include "GPTHistory.hpp"

#ifndef BOT_HPP
# define BOT_HPP

class GPTHistory;

class Bot
{
	private:
		int 								_connFd;
		struct pollfd 						_pollfd;
		std::string 						_buffer;
		bool								_stop;
		std::map<std::string, GPTHistory *> 	_histories;
	public:
		Bot(std::string ip, std::string port);
		~Bot();
		int 	init_connection(const char *ip, uint16_t port);
		void	send(std::string str);
		void 	listen();
		void	login(std::string pass);

		void 	handleBuffer();
		void	exec(unsigned long len);
		void	addHistory(std::string name, std::string msg);
};

#endif

