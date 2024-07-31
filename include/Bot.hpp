/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 00:51:45 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/31 17:56:54 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

#include <string>
#include <stdint.h>
#include <poll.h>


class Bot
{
	private:
		int _connFd;
		struct pollfd _pollfd;
		std::string _buffer;
		bool	_stop;
	public:
		Bot(std::string ip, std::string port);
		~Bot();
		int init_connection(const char *ip, uint16_t port);
		void	send(std::string str);
		void listen();
};

#endif

