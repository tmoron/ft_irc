/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:53:55 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/02 16:20:38 by tomoron          ###   ########.fr       */
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
		std::string	_nick;
		std::string	_buffer;
		bool		_loggedIn;
		Server		&_server;

		std::string	_user;
		std::string _hostname;
		std::string _servername;
		std::string _realname;

		int			_quit;

		void handleBuffer();

	public:
		Client(int fd, Server &srv);
		~Client(void);

		void		welcome();
		void		setUser(std::string user);
		void		setNick(std::string nick);
		void		setLoggedIn(bool b);
		void		setHostname(std::string hostname);
		void		setServername(std::string servername);
		void		setRealname(std::string realname);

		std::string	getUser();
		std::string	getNick();
		std::string	getBuffer();
		int			getFd();
		int			getLoggedIn();
		std::string	getHostname();
		std::string getServername();
		std::string getRealname();

		int			isRegistered();
		int			updateBuffer();
		int			sendMsg(Client &from,const std::string &to,const std::string &message);
		void		quit();
		void		sendStr(std::string msg);
		std::string	getIdentifier();
		void		sendInfo(Channel *channel, int code, std::string description);
		std::string getWho(Channel *channel);
};

# include "Channel.hpp"

#endif
