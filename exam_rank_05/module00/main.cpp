
#include "Warlock.hpp"

int main()
{
// 		Warlock bob;
// 		Warlock bob("Bob", "the magnificent");
// 		Warlock jim("Jim", "the nauseating"); 
// 		bob = jim;
		// Warlock jack(jim);

		//	!!

		Warlock const richard("Richard", "Mistress of Magma");
		richard.introduce();
		std::cout << richard.getName() << " - " << richard.getTitle() << std::endl;

		Warlock* jack = new Warlock("Jack", "the Long");
		jack->introduce();
		jack->setTitle("the Mighty");
		jack->introduce();

		delete jack;

		return (0);
}