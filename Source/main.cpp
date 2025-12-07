#include <iostream>

#ifdef Debug
	#define BUILD_TYPE "DEBUG"
#elif defined(Release)
	#define BUILD_TYPE "RELEASE"
#else
	#define BUILD_TYPE "UNCONFIGURED"
#endif

int main()
{
	std::cout << "Hello, World!\nCurrent build configuration is " << BUILD_TYPE << std::endl;
	return 0;
}