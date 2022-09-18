#pragma once

#include <string>
#include <vector>
#include "assignment.h"

class assignmentCategory
{
public:
	void modifyCategory();
	void addAssignment();
	void modifyAssignment();
	const void printReport();
	void deleteAssignment();

public:
	const std::string getName();
	const float getAverage();
	const float getDWeight();

public:
	assignmentCategory() = delete;
	assignmentCategory(std::string &, float);

public:
	void readAssignmentsFromFile();
	const void exportAssignmentsToFile();

private:
	float m_pWeight;
	float m_dWeight;
	float m_categoryAverage;
	std::string m_name;
	std::vector<assignment> m_assignments;

private:
	void changeName();
	void changeWeight();
	void calculateAverage();
};
