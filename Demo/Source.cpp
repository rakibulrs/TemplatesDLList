#include <iostream>
#include "../TemplatesDLList/DLList.h"

int main()
{
	DLList<int> a{ 1,2,3,4,5,6,7 };
	DLList<int> b{ 1,2,3,4,5,6 };
	a = b;
	std::cout << a.to_string() << std::endl;
	std::cout << b.to_string() << std::endl;
	return 0;
}