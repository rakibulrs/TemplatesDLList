#include <iostream>
#include "../TemplatesDLList/DLList.h"

int main()
{
	try
	{
		DLList<int> a{ 1,2,3};
		DLList<int> b{ 2,2,2 };
		b = std::move(a);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
	return 0;
}