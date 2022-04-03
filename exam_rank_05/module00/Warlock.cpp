
#include "Warlock.hpp"

Warlock::Warlock()
{
}

Warlock::~Warlock(){
    std::cout << this->getName() << ": My job here is done!" << std::endl;
}

Warlock::Warlock(const Warlock &)
{

}

Warlock::Warlock(std::string n, std::string t)
{
    this->name = n;
    std::cout << this->getName() << ": This looks like another boring day." << std::endl;
    this->setTitle(t);
}

Warlock &Warlock::operator=(const Warlock&){
    
    return *this;
}

const std::string &Warlock::getName(void) const{
    return this->name;
}

const std::string &Warlock::getTitle(void) const{
    return this->title;
}

void 	Warlock::setTitle(const std::string &obj){
    this->title = obj;
}

void Warlock::introduce() const
{
    std::cout << this->getName() << ": I am " << this->getName() 
        << ", " << this->getTitle() << " !" << std::endl;
}
