#include "assignment.h"
#include "assignmentCategory.h"
#include "subject.h"

int main()
{
	std::string name = "Calc I";
	subject test(name);
	test.addCategory();
	test.addAssignment();
	test.printSubjectReport();

	return 0;
}