/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:31:20 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/26 18:10:31 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::string	trim(char c, std::string str)
{
	int	i;

	i = 0;
	while(str[i] == c)
		i++;
	str.erase(0, i);
	if(!str.length())
		return(str);
	i = str.length() - 1;
	while(str[i] == c)
		i--;
	str.erase(i + 1);
	return(str);
}

std::vector<std::string> ft_split(std::string str, char sep)
{
	std::vector <std::string>	res;
	std::string					part;
	std::stringstream			ss;

	ss << str;
	while(!ss.eof())
	{
		getline(ss, part, sep);
		if(part.length() != 0)
			res.push_back(part);
	}
	return(res);
}

void Handler(int signum)
{
	std::cout << "Server shutting down" << std::endl;
	g_sig = 1;
}

long unsigned int	stdStringToLongUnsignedInt(std::string str)
{
	long unsigned int	res;
	std::stringstream	ss;

	ss << str;
	ss >> res;
	return(res);
}
