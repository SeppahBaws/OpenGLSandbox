#include "pch.h"
// ReSharper Disable Once CppUnusedIncludeDirective
#include <vld.h>

#include "src/Core/Application.h"

int main()
{
	Application* pApplication = new Application();
	pApplication->Run();
	
	delete pApplication;
}
