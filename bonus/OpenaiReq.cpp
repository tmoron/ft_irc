/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenaiReq.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:33:31 by tomoron           #+#    #+#             */
/*   Updated: 2024/08/02 01:13:18 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenaiReq.hpp"
#include <netdb.h>

OpenaiReq::OpenaiReq(std::string body)
{
	this->_address = "openai.tmoron.fr";
	this->_path = "/";

	this->_reqBuffer = getInitialBody(body);
}
OpenaiReq::~OpenaiReq()
{
	
}

std::string OpenaiReq::getInitialBody(const std::string &body)
{
	std::stringstream res;

	res << "POST " << this->_path << " HTTP/1.1\r\n";
	res << "Host: " << this->_address << "\r\n";
	res << "User-Agent: ircbot/1.0\r\n";
	res << "Accept: */*\r\n";
	res << "Connection: close\r\n";
	res << "Content-Length: " << body.length() << "\r\n";
	res << "\r\n";
	res << body;
	return(res.str());
}

struct addrinfo *OpenaiReq::resolve_address()
{
	struct addrinfo hints;
	struct addrinfo *res;

	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	if(getaddrinfo(this->_address.c_str(), "80", &hints, &res) != 0)
		return(0);
	return(res);
}

int OpenaiReq::create_socket()
{		
	struct addrinfo *addrs = resolve_address();
	int socket_fd;

	if(!addrs)
		return(-1);
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
		freeaddrinfo(addrs);
		return(-1);
	}
	if(connect(socket_fd, addrs->ai_addr, addrs->ai_addrlen) != 0)
	{
		perror("connect");
		close(socket_fd);
		freeaddrinfo(addrs);
		return(-1);
	}
	freeaddrinfo(addrs);
	return(socket_fd);
}

std::string OpenaiReq::getChunk(std::stringstream &body)
{
	std::string res;
	char buffer[1024];
	int expected_len;
	int lst_read_len;

	body >> std::hex >> expected_len;
	body.readsome(buffer, 2);
	if(!expected_len)
		return ("");
	while(expected_len != 0 && !body.eof())
	{
		lst_read_len = body.readsome(buffer,
			(expected_len > 1024) ? 1024 : expected_len);
		expected_len -= lst_read_len;
		res += std::string(buffer, lst_read_len); 
	}
	body.readsome(buffer,2);
	return (res);
}

std::string OpenaiReq::parse_response()
{
	std::string &buffer = this->_resBuffer;
	std::string sep = "\r\n\r\n";
	std::stringstream body;
	std::stringstream final_buffer;
	
	if(buffer.find(sep, 0) == std::string::npos)
		return("invalid response");
	body << buffer.substr(buffer.find(sep, 0) + sep.length());
	while(!body.eof())
		final_buffer << getChunk(body);
	return(final_buffer.str());
}


std::string OpenaiReq::send()
{
	int socket = this->create_socket();
	char buffer[1024];
	unsigned long len = -1;
	
	if(socket == -1)
		return("could not establish connection to " + this->_address);
	write(socket, this->_reqBuffer.c_str(), this->_reqBuffer.length());
	while(len != 0)
	{
		len = read(socket,buffer, 1024);
		if(len)
			this->_resBuffer += std::string(buffer,len);
	}
	return(parse_response());
}
