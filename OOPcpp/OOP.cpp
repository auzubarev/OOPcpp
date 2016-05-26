#pragma once
#include <iostream>	
#include "Factory.h"
#include <time.h>
int main() {
	srand((unsigned int)time(NULL));
	Shapes::resetCount();
	Container<Shapes *> figures;
	try {
		for (int i = 0; i < 20; i++)
			figures.pushBack(Factory::getRandShape());
		std::cout << Shapes::getCount();
		std::cout << "\n";
		for (int i = 0; i < 20; i++)
			std::cout << figures.get(i)->print();
		for (int i = 0; i < 20; i++)
			delete figures.get(i);
		figures.clear();
		std::cout << "\n";
		std::cout << Shapes::getCount() << "\n";
	}
	catch (const std::string & e) {
		std::cout << "ERROR! " + e;
	}
	system("pause");
	return 0;
}
