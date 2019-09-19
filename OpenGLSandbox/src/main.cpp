#include <iostream>

#include "Application.h"

int main()
{
	Application* pApplication = new Application();
	pApplication->Run();
	
	delete pApplication;
}
