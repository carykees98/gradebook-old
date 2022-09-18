#include "findMax.h"
#include "assignment.h"

int findMax(std::vector<assignment> collection) {
	int max = 0;
	for (assignment item : collection)
	{
		if (item.getName().length() > max) {
			max = item.getName().length();
		}
	}
	return max;
}