#pragma once

#include <sstream>

namespace foo { namespace test
{
	template<typename E, typename A>
	void test_equal(const E & expected, const A & actual)
	{
		if (expected != actual)
		{
			std::ostringstream stream;
			stream << "Expected: " << expected << ", but got: " << actual;
			throw std::runtime_error(stream.str());
		}
	}

}  }
