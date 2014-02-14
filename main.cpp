#include <iostream>
#include <boost/lexical_cast.hpp>
#include "combination.h"

int main(int argc, char const* argv[]){
	combination combo(
			boost::lexical_cast<int>(argv[1]),
			boost::lexical_cast<int>(argv[2]));

	int c = combo.combinations();
	std::cout << "combinations: " << c << std::endl;

	for(; !combo.is_end(); ++combo){
		std::cout << "(";
		for (int val: *combo) {
			std::cout << val <<" ";
		}
		std::cout << ")" <<std::endl;
	}

	return 0;
}
