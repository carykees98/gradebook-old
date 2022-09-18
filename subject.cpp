#include "subject.h"

#include <unordered_map>
#include <string>
#include <iostream>
#include <iomanip>
#include "menu.h"

std::unordered_map<int, std::string> subject::m_alphanumericGrades = {
    {0, "A+"},
    {1, "A"},
    {2, "A-"},
    {3, "B+"},
    {4, "B"},
    {5, "B-"},
    {6, "C+"},
    {7, "C"},
    {8, "C-"},
    {9, "D"}};

void subject::modifySubject()
{
    std::vector<std::string> options = { "Subject Name", "Letter Grade Bounds", "Assignment Category" };
    switch (menu(options, "What would you like to modify?")) {
    case 1:
        changeName();
        break;
    case 2:
        changeGradeBounds();
        determineLetterGrade();
        break;
    case 3:
        modifyCategory();
        calculateAverage();
        break;
    }
}

void subject::addCategory()
{
    bool cont = true;
    char contResponse[4];
    while (cont == true) {
        std::string name;
        std::cout << "What is the name of the category you would like to add?" << std::endl
            << ">>> ";
        std::cin >> name;
        float pWeight;
        std::cout << "What is the percent weight for this category?" << std::endl
            << ">>> ";
        std::cin >> pWeight;
        m_assignmentTypes.emplace_back(name, pWeight);
        std::cout << "Would you like to add another category? (Y/N)" << std::endl
            << ">>> ";
        std::cin >> contResponse;
        if (toupper(contResponse[0]) != 'Y') {
            cont = false;
        }
    }
    calculateAverage();
}

void subject::addAssignment() // add ability to add multiple assignments without returning to menu
{
    int menuAnswer;
    char contResponse[4] = { 'Yes\0' };
    while (toupper(contResponse[0]) == 'Y') {
        std::cout << "Which category would you like to add the assignment to?" << std::endl;
        for (int i = 0; i < m_assignmentTypes.size(); i++) {
            std::cout << i + 1 << ". " << m_assignmentTypes[i].getName() << std::endl;
        }
        std::cout << ">>> ";
        std::cin >> menuAnswer;
        menuAnswer -= 1;
        m_assignmentTypes[menuAnswer].addAssignment();
        std::cout << "Would you like to add another Assignment? (Y/N)" << std::endl
            << ">>> ";
        std::cin >> contResponse;
    }
    calculateAverage();
}

void subject::modifyCategory()
{
    int menuAnswer;
    char contResponse[4] = { 'Yes\0' };
    while (toupper(contResponse[0]) == 'Y') {
        std::cout << "----------------------------------------------" << std::endl
            << "Which category would you like to modify?" << std::endl;
        for (int i = 0; i < m_assignmentTypes.size(); i++) {
            std::cout << i + 1 << ". " << m_assignmentTypes[i].getName() << std::endl;
        }
        std::cout << ">>> ";
        std::cin >> menuAnswer;
        menuAnswer -= 1;
        m_assignmentTypes[menuAnswer].modifyCategory();
        std::cout << "Would you lIke to modify another category?" << std::endl
            << ">>> ";
        std::cin >> contResponse;
    }
    calculateAverage();
}

void subject::printSubjectReport()
{
    std::cout << "Class Name: " << m_name << std::endl
        << std::fixed << std::setprecision(2) << "Current Average: " << m_average << std::endl;
    for (auto &type : m_assignmentTypes) {
        type.printReport();
    }
}

subject::subject(std::string &name)
{
    m_name = name;
}

void subject::determineLetterGrade()
{

}

void subject::printCurrentSettings()
{
}

void subject::changeName()
{
    std::cout << "----------------------------------------------" << std::endl
        << "This subjects name is currently: " << m_name << std::endl
        << "What would you like the new name to be?" << std::endl
        << ">>> ";
    std::cin >> m_name;
}

void subject::changeGradeBounds()
{
    int menuAnswer;
    std::cout << "----------------------------------------------" << std::endl
        << "Which bound would you like to change?" << std::endl;
    for (int i = 0; i < m_alphanumericGrades.size(); i++) {
        std::cout << i + 1 << ". " << m_alphanumericGrades[i] << std::endl;
    }
    std::cin >> menuAnswer;
    menuAnswer -= 1;
    std::cout << "What would you like the new lower bound for " << m_alphanumericGrades[menuAnswer] << "to be?" << std::endl
        << ">>> ";
    std::cin >> m_lowerGradeBounds[menuAnswer];
}

void subject::calculateAverage()
{
    float totalPoints = 0;
    for (auto& type : m_assignmentTypes) {
        totalPoints += (type.getAverage() * type.getDWeight());
    }
    m_average = totalPoints / m_assignmentTypes.size();
}
