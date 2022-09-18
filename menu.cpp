#include "menu.h"
#include <iostream>

int menu(std::vector<std::string> options)
{
	bool cont = true;
	int choice;
	while (cont == true)
	{
		int current = 1;
		std::cout << "----------------------------------------------" << std::endl;
		for (auto &option : options)
		{
			std::cout << current << ". " << option << std::endl;
			current++;
		}
		std::cout << ">>> ";
		std::cin >> choice;
		std::cin.get();
		if (choice > 0 && choice <= current)
		{
			cont = false;
			return choice;
		}
		else
		{
			std::cout << "----------------------------------------------" << std::endl
					  << "Please provide a valid option" << std::endl;
		}
	}
}

int menu(std::vector<std::string> options, std::string title)
{
	bool cont = true;
	int choice;
	while (cont == true)
	{
		int current = 1;
		std::cout << "----------------------------------------------" << std::endl
				  << title << std::endl;
		for (auto &option : options)
		{
			std::cout << current << ". " << option << std::endl;
			current++;
		}
		std::cout << ">>> ";
		std::cin >> choice;
		std::cin.get();
		if (choice > 0 && choice <= current)
		{
			cont = false;
			return choice;
		}
		else
		{
			std::cout << "----------------------------------------------" << std::endl
					  << "Please provide a valid option" << std::endl;
		}
	}
}