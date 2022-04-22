/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:48:14 by zqadiri           #+#    #+#             */
/*   Updated: 2022/04/22 00:10:26 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include "ASpell.hpp"
# include <vector>

class Warlock
{
    private:
        std::string         name;    
        std::string         title;
        std::vector<ASpell *> spells;
        
        Warlock();
        Warlock(const Warlock &);
        Warlock& operator= (const Warlock &);
    
    public:
        Warlock(const std::string &, const std::string &);
        ~Warlock();

        const std::string&  getName() const;
        const std::string&  getTitle() const;
        void                setTitle(const std::string &);
        void                introduce() const;

        void                learnSpell(ASpell *);
        void                forgetSpell(const std::string &);
        void                launchSpell(const std::string &, const ATarget &);
};

#endif
