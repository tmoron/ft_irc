/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:53:55 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/26 14:29:49 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.hpp"

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "include.hpp"

class Server;
class Channel;

class Client
{
	private:
		int			_fd;
		std::string	_user;
		std::string	_nick;
		std::string	_buffer;
		bool		_loggedIn;
		Server		&_server;

		void handleBuffer();

	public:
		Client(int fd, Server &srv);
		~Client(void);

		void		setUser(std::string user);
		void		setNick(std::string nick);
		void		setLoggedIn(bool b);

		std::string	getUser();
		std::string	getNick();
		std::string	getBuffer();
		int			getFd();
		int			getLoggedIn();

		int			isRegistered();
		int			updateBuffer();
		int			sendMessage(Client &from,const std::string &to,const std::string &message);
		void		sendStr(std::string msg);
		std::string	getIdentifier();
		void		sendInfo(Channel *channel, int code, std::string description);
};

# include "Channel.hpp"

#endif
