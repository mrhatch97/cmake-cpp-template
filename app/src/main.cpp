#include <foo/foo.h>

#include <iostream>
#include <string>

int main(int argc, char **  argv)
{
	int num = std::stoi(argv[1]);	

	std::cout << foo::factorial(num) << std::endl;
}
