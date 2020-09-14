#pragma once
#include <exception>
#include <iostream>
#include <vector>
#include <functional>
#include <type_traits>
#define TEST_UNIT
namespace mcalcu
{
	long long gcd(long long a, long long b);
	void factor(long long a, std::vector<long long> & vec);
	using IntegerFrequency = std::pair<long long, int>;
	std::vector<IntegerFrequency> count_frency(std::vector<long long>& vec);


	template<typename EleType, typename It, typename FuncType>
	auto filter(It from, It end, FuncType func)
	{

		std::vector<EleType> res;
		while (from != end)
		{
			if (func(*from))
				res.push_back(*from);
			++from;
		}
		return res;
	}

#ifdef TEST_UNIT
	void test_factor();
#endif
}