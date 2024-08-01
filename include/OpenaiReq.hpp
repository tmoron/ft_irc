/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenaiReq.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:35:44 by tomoron           #+#    #+#             */
/*   Updated: 2024/08/02 00:36:46 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.hpp"

#ifndef OPENAIREQ_HPP
# define OPENAIREQ_HPP

class OpenaiReq
{
	private:
		std::string _address;
		std::string _path;

		std::string _reqBuffer;
		std::string _resBuffer;

		std::string			getInitialBody(const std::string &body);
		int					create_socket();
		struct addrinfo		*resolve_address();
		std::string			parse_response();
		std::string			getChunk(std::stringstream &body);
	public:
		OpenaiReq(std::string body);	
		~OpenaiReq();
		
		std::string send();
};

#endif
