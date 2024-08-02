/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:31:20 by tomoron           #+#    #+#             */
/*   Updated: 2024/08/02 15:13:15 by pageblanche      ###   ########.fr       */
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

std::vector<std::string> ft_split_irc(std::string str)
{
	std::vector <std::string>	res;
	unsigned long				len;

	if (str[0] == ':')
		str.erase(0, 1);
	while (str.length())
	{
		if(str[0] == ':')
			len = std::string::npos;
		else
			len = str.find(' ', 0);
		if(len)
			res.push_back(str.substr(0, len));
		if(len != std::string::npos)
			str.erase(0, len + 1);
		else
			str.erase(0, std::string::npos);
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

std::string removeChar(const std::string &input, char c)
{
	unsigned long pos;
	std::string str;

	str = input;
	pos = str.find(c, 0);
	while(pos != std::string::npos)
	{
		str.erase(pos, 1);
		pos = str.find(c, 0);
	}
	return(str);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned long int	i;
	char				*ptr;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

