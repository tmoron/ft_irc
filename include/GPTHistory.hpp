/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GPTHistory.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:38:40 by pageblanche       #+#    #+#             */
/*   Updated: 2024/08/02 13:44:27 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.hpp"

#ifndef GPT_HISTORY_HPP
# define GPT_HISTORY_HPP

typedef struct s_history
{
    std::string role;
    std::string message;
}               t_history;

class GPTHistory
{
    private:
        const std::string       _name;
        std::vector<t_history>  _history;
    public:
        GPTHistory(std::string name);

        void addHistory(std::string role, std::string message);
        
        std::string             getName() const;
        std::vector<t_history>  getHistory() const;
		std::string				getHistoryJson() const;

        GPTHistory &operator=(const GPTHistory &other);
        ~GPTHistory();
};

#endif
