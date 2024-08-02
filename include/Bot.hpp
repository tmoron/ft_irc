/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 00:51:45 by tomoron           #+#    #+#             */
/*   Updated: 2024/08/02 22:28:57 by tomoron          ###   ########.fr       */
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
		std::string 							_name;
		int 									_connFd;
		struct pollfd 							_pollfd;
		std::string 							_buffer;
		bool									_stop;
		std::map<std::string, GPTHistory *> 	_histories;
	public:
		Bot(std::string ip, std::string port);
		~Bot();
		void	genName();
		int 	init_connection(const char *ip, uint16_t port);
		void	send(std::string str);
		void 	listen();
		void	login(std::string pass);

		void 	handleBuffer();
		void	exec(std::string buffer);
		void	addHistory(std::string name, std::string msg, const std::string role);
		
};

#endif

