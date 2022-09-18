#include "assignment.h"
#include "menu.h"
#include <string>
#include <iostream>
#include <vector>

assignment::assignment(std::string &name, float pointsEarned, float pointsPossible)
{
	m_name = name;
	m_pointsEarned = pointsEarned;
	m_pointsPossible = pointsPossible;
}

const float assignment::getPointsEarned()
{
	return m_pointsEarned;
}

const float assignment::getPointsPossible()
{
	return m_pointsPossible;
}

const std::string assignment::getName()
{
	return m_name;
}

const float assignment::getGrade()
{
	return m_gradeEarned;
}

void assignment::modifyAssignment()
{
	std::vector<std::string> options = {"Change name", "Change point values"};
	switch (menu(options, "Which field would you like to change?"))
	{
	case 1:
		changeName();
		break;
	case 2:
		changePointValues();
		break;
	}
}

void assignment::changeName()
{
	std::cout << "----------------------------------------------" << std::endl
			  << "What would you like to change the name to?" << std::endl
			  << ">>> ";
	std::cin.get();
	std::getline(std::cin, m_name);
	std::cout << "----------------------------------------------" << std::endl
			  << "Assignment name successfully changed" << std::endl;
}

void assignment::changePointValues()
{
	std::vector<std::string> choices = {"Points earned", "Possible points"};
	bool cont = true;
	char another[4];
	while (cont == true)
	{
		switch (menu(choices, "Which point value would you like to change?"))
		{
		case 1:
			std::cout << "How many points did you earn on this assignment?" << std::endl
					  << ">>> ";
			std::cin >> m_pointsEarned;
			calculateGrade();
			break;
		case 2:
			std::cout << "How many points were possible on this assignment?" << std::endl
					  << ">>> ";
			std::cin >> m_pointsPossible;
			calculateGrade();
			break;
		}
		std::cout << "----------------------------------------------" << std::endl
				  << "Would you like to modify another value? (Y/N)" << std::endl
				  << ">>> ";
		std::cin >> another;
		if ((toupper(another[0])) != 'Y')
		{
			cont = false;
		}
	}
}

void assignment::calculateGrade()
{
	m_gradeEarned = (m_pointsEarned / m_pointsPossible) * 100.0f;
}