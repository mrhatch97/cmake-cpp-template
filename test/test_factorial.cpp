#include <foo/foo.h>
#include <test/util.h>

int main()
{
	using namespace foo::test;

	int result = foo::factorial(5);

	test_equal(120, result);
}
