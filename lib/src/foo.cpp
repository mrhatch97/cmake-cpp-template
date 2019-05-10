#include "foo/foo.h"

#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

namespace foo 
{
	int factorial(int n) 
	{
		std::vector<int> vec(n);

		std::iota(vec.begin(), vec.end(), 1);
		return std::accumulate(vec.begin(), vec.end(), 1, 
				std::multiplies<int>());
	}
}
