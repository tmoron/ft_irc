/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:53:55 by pageblanche       #+#    #+#             */
/*   Updated: 2024/07/24 15:42:07 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "include.hpp"
# include <string>

class Server;
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
		std::string getBuffer();
		int			getFd();
		bool		getLoggedIn();

		int			updateBuffer();
};




#endif
