#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "assignmentCategory.h"

class subject
{
public:
	void modifySubject();
	void addCategory();
	void addAssignment();
	void modifyCategory();
	void printSubjectReport();

public:
	subject() = delete;
	subject(std::string &);

private:
	std::string m_name;
	int m_alphanumericGradeKey;
	float m_average;
	std::vector<int> m_lowerGradeBounds;
	std::vector<assignmentCategory> m_assignmentTypes;
	static std::unordered_map<int, std::string> m_alphanumericGrades;

private:
	void determineLetterGrade();
	void printCurrentSettings();
	void changeName();
	void changeGradeBounds();
	void calculateAverage();
};