/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:48:14 by zqadiri           #+#    #+#             */
/*   Updated: 2022/04/01 14:33:03 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>
#include <string>

class Warlock
{
	private:
		std::string name;
		std::string title;

		Warlock();
		Warlock(const Warlock &);
		Warlock &operator=(const Warlock&);
	public:
		~Warlock();
		Warlock(std:: string, std::string);

		const std::string &getName(void) const;
		const std::string &getTitle(void) const;

		void 	setTitle(const std::string &);
		void 	introduce() const;
		
};

#endif