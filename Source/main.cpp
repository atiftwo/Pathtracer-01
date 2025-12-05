#include <iostream>

#ifndef BUILD_TYPE
	#define BUILD_TYPE "Unconfigured"
#endif

int main()
{
	std::cout << "Hello, World!\nCurrent build configuration: " << BUILD_TYPE << std::endl;
	return 0;
}