/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:29:50 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/27 00:21:52 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include "include.hpp"

std::string					trim(char c, std::string str);
std::vector<std::string>	ft_split(std::string str, char c);
void Handler(int signum);
long unsigned int	stdStringToLongUnsignedInt(std::string str);
std::string removeChar(const std::string &input, char c);
std::vector<std::string> ft_split_irc(std::string str);

#endif
