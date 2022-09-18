#pragma once
#include <string>

class assignment
{
public:
	void modifyAssignment();
	void calculateGrade();

public:
	assignment() = delete;
	assignment(std::string &, float, float);

public:
	const float getPointsEarned();
	const float getPointsPossible();
	const std::string getName();
	const float getGrade();

private:
	std::string m_name;
	float m_pointsEarned;
	float m_pointsPossible;
	float m_gradeEarned;

private:
	void changeName();
	void changePointValues();
};
