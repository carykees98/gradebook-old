#include "assignmentCategory.h"
#include "menu.h"
#include "findMax.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>

assignmentCategory::assignmentCategory(std::string &name, float pWeight)
{
	m_name = name;
	m_pWeight = pWeight;
}

void assignmentCategory::readAssignmentsFromFile()
{
	int entryCount;
	std::ifstream infile("assignments.dat");
	if (infile.fail())
	{
		std::ofstream fileCreator("assignments.dat");
		fileCreator << "0" << std::endl;
		fileCreator.close();
		infile.open("assignments.dat");
	}
	infile >> entryCount;
	infile.get();
	std::string assignmentName;
	float pointsEarned, pointsPossible;
	for (int i = 0; i < entryCount; i++)
	{
		infile >> pointsEarned >> pointsPossible;
		infile.get();
		std::getline(infile, assignmentName);
		m_assignments.emplace_back(assignmentName, pointsEarned, pointsPossible);
	}
	calculateAverage();
}

const void assignmentCategory::exportAssignmentsToFile()
{
	std::ofstream outfile("assignments.dat");
	outfile << m_assignments.size() << std::endl;
	for (int i = 0; i < m_assignments.size(); i++)
	{
		outfile << m_assignments[i].getPointsEarned() << " " << m_assignments[i].getPointsPossible() << " " << m_assignments[i].getName() << std::endl;
	}
}

void assignmentCategory::addAssignment()
{
	std::string assignmentName;
	float earned, max;
	char newlineTest;
	std::cout << "----------------------------------------------" << std::endl
			  << "What is the name of the assignment you would like to add?" << std::endl
			  << ">>> ";
	std::cin.get(newlineTest);
	if (newlineTest != '\n')
	{
		std::cin.putback(newlineTest);
	}
	std::getline(std::cin, assignmentName);
	std::cout << "How many points did you earn on this assignment?" << std::endl
			  << ">>> ";
	std::cin >> earned;
	std::cout << "How many points were possible on this assignment?" << std::endl
			  << ">>> ";
	std::cin >> max;
	m_assignments.emplace_back(assignmentName, earned, max);
	calculateAverage();
}

void assignmentCategory::modifyAssignment()
{
	bool cont = true;
	int answer;
	char another[4];
	while (cont == true)
	{
		std::cout << "----------------------------------------------" << std::endl
				  << "Which assignment would you like to modify?" << std::endl;
		for (int i = 0; i < m_assignments.size(); i++)
		{
			std::cout << i + 1 << ". " << m_assignments[i].getName() << " " << std::right << std::setw(3) << m_assignments[i].getPointsEarned() << " / " << std::setw(3) << m_assignments[i].getPointsPossible() << std::endl;
		}
		std::cout << ">>> ";
		std::cin >> answer;
		answer = answer - 1;
		m_assignments[answer].modifyAssignment();
		std::cout << "----------------------------------------------" << std::endl
				  << "Would you like to modify another assignment? (Y/N)" << std::endl
				  << ">>> ";
		std::cin >> another;
		if ((toupper(another[0])) != 'Y')
		{
			cont = false;
		}
	}
}

void assignmentCategory::modifyCategory()
{
	std::vector<std::string> choices = {"Category name", "Percent Weight"};
	bool cont = true;
	char another[4];
	while (cont == true)
	{
		switch (menu(choices, "Which field would you like to modify"))
		{
		case 1:
			changeName();
			break;
		case 2:
			changeWeight();
			calculateAverage();
			break;
		}
		std::cout << "----------------------------------------------" << std::endl
				  << "Would you like to modify another field? (Y/N)" << std::endl
				  << ">>> ";
		std::cin >> another;
		if ((toupper(another[0])) != 'Y')
		{
			cont = false;
		}
	}
}

void assignmentCategory::changeName()
{
	std::cout << "What would you like to change the name of this category to?" << std::endl
			  << ">>> ";
	std::cin >> m_name;
}

void assignmentCategory::changeWeight()
{
	std::cout << "What would you like to change the percent weight of this category to?" << std::endl
			  << ">>> ";
	std::cin >> m_pWeight;
}

void assignmentCategory::calculateAverage()

{
	float cumEarned = 0.0f;
	float cumPossible = 0.0f;
	for (auto &currentAssignment : m_assignments)
	{
		currentAssignment.calculateGrade();
		cumEarned = cumEarned + currentAssignment.getPointsEarned();
		cumPossible = cumPossible + currentAssignment.getPointsPossible();
	}
	m_categoryAverage = (cumEarned / cumPossible) * 100.0f;
}

const void assignmentCategory::printReport()
{
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "----------------------------------------------" << std::endl
			  << "Category: " << m_name << std::endl
			  << "Percent Weight: " << m_pWeight << "%" << std::endl;
	if (m_assignments.size() == 0)
	{
		std::cout << std::endl
			      << "There are no assignments to list" << std::endl
				  << std::endl;
	}
	else
	{
		std::cout << "Category Average: " << m_categoryAverage << "%" << std::endl
				  << "Contribution to Class Total: " << m_categoryAverage * m_pWeight / 100.0f << "%" << std::endl
				  << std::endl;
		int nameWidth;
		if ((findMax(m_assignments) + 3) < 16)
		{
			nameWidth = 16;
		}
		else
		{
			nameWidth = findMax(m_assignments) + 3;
		}
		std::cout << std::setw(nameWidth) << "Assignment Name:" << std::setw(15) << "Pts. Earned:" << std::setw(17) << "Pts. Possible:" << std::setw(17) << "Percent Grade:" << std::endl;
		for (int i = 0; i < m_assignments.size(); i++)
		{
			std::cout << std::left << std::setw(nameWidth) << m_assignments[i].getName() << std::right << std::setw(15) << m_assignments[i].getPointsEarned() << std::setw(17) << m_assignments[i].getPointsPossible() << std::setw(16) << m_assignments[i].getGrade() << "%" << std::endl;
		}
		std::cout << std::endl;
	}
}

void assignmentCategory::deleteAssignment()
{
	if (m_assignments.size() == 0)
	{
		std::cout << "----------------------------------------------" << std::endl
			<< "There are no assignments to delete" << std::endl;
	}
	else
	{
		int answer;
		char another[4];
		bool cont = true;
		while (cont == true)
		{
			std::cout << "----------------------------------------------" << std::endl
				<< "Which assignment would you like to delete?" << std::endl;
			for (int i = 0; i < m_assignments.size(); i++)
			{
				std::cout << i + 1 << ". " << m_assignments[i].getName() << std::endl;
			}
			std::cout << ">>> ";
			std::cin >> answer;
			if ((answer < 1) || (answer > (m_assignments.size() + 1)))
			{
				std::cout << "----------------------------------------------" << std::endl
					<< "Please enter a valid option" << std::endl;
				continue;
			}
			answer = answer - 1;
			m_assignments.erase(m_assignments.begin() + answer);
			std::cout << "----------------------------------------------" << std::endl
				<< "Assignment successfully deleted" << std::endl;
			if (m_assignments.size() > 0)
			{
				std::cout << "----------------------------------------------" << std::endl
					<< "Would you like to delete another assignment? (Y/N)" << std::endl
					<< ">>> ";
				std::cin >> another;
				if ((toupper(another[0])) != 'Y')
				{
					cont = false;
				}
			}
			else
			{
				cont = false;
			}
		}
	}
}

const std::string assignmentCategory::getName()
{
	return m_name;
}

const float assignmentCategory::getAverage()
{
	return m_categoryAverage;
}

const float assignmentCategory::getDWeight()
{
	return m_dWeight;
}
