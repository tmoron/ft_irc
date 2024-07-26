/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:29:50 by tomoron           #+#    #+#             */
/*   Updated: 2024/07/26 18:11:16 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include "include.hpp"

std::string					trim(char c, std::string str);
std::vector<std::string>	ft_split(std::string str, char c);
void Handler(int signum);
long unsigned int	stdStringToLongUnsignedInt(std::string str);

#endif
