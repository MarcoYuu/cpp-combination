#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/timer/timer.hpp>

#include "combination.h"

int main(int argc, char const* argv[]){
	combination combo(
			boost::lexical_cast<int>(argv[1]),
			boost::lexical_cast<int>(argv[2]));

	int c = combo.combinations();
	std::cout << "combinations: " << c << std::endl;

	//boost::timer::cpu_timer timer;
	//for(int i=0; i < c; ++i){
	//	timer.resume();
	//	const std::vector<int> &r = combo.next();
	//	timer.stop();

	//	std::cout << "(";
	//	for (int val: r) {
	//		std::cout << val <<" ";
	//	}
	//	std::cout << ")" <<std::endl;
	//}

	boost::timer::cpu_timer timer;
	for(; !combo.is_end(); ++combo){
		timer.stop();

		std::cout << "(";
		for (int val: *combo) {
			std::cout << val <<" ";
		}
		std::cout << ")" <<std::endl;

		timer.resume();
	}

	std::cout << "wall[sec],\t user[sec],\t system[sec],\t CPU%" << std::endl;
	std::cout << timer.format(10, "%w,\t %u,\t %s,\t %p") << std::endl;

	return 0;
}
