/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:33:54 by zqadiri           #+#    #+#             */
/*   Updated: 2022/04/01 14:40:15 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASPELL_HPP
#define ASPELL_HPP

#include <iostream>
#include <string>

class ASpell
{
	private:
		std::string name;
		std::string effects;
	public:
		ASpell();
		~ASpell();
		ASpell(const ASpell&);
		ASpell(const std::string&, const std::string&);
		std::string getName(void) const;
		std::string getEffects(void) const;  

		virtual ASpell *clone(void) const = 0;		
};

#endif
