#include "pch.h"
// ReSharper Disable Once CppUnusedIncludeDirective
#include <vld.h>

#include "Application.h"

int main()
{
	Application* pApplication = new Application();
	pApplication->Run();
	
	delete pApplication;
}
