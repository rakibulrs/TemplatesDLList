#include <iostream>
#include "../TemplatesDLList/DLList.h"

int main()
{
	try
	{
		DLList<int> a{ 1,2,3,4,5,6,7 };
		DLList<int> b{ 1,2,3,4,5,6 };
		std::cout << a.get(6);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
	
}