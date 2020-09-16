#include "../includes/core.hpp"
#include <map>
#include <algorithm>
namespace mcalcu
{
	long long gcd(long long a, long long b)
	{
		if (b == 0)return a;
		return gcd(b, a % b);
	}

	long long factor_iter(long long res)
	{
		for(long long i=2;i*i<=res;i++)
			if(!(res%i))
				return i;
		return 0;
	}
	void factor(long long a, std::vector<long long>& vec)
	{
		while (true)
		{
			long long ans = factor_iter(a);
			if (!ans)
			{
				vec.push_back(a);
				break;
			}
			vec.push_back(ans);
			a /= ans;
		}
	}
	std::vector<IntegerFrequency> count_frency(const std::vector<long long>& vec)
	{
		std::map<long long, int> table;
		for (auto a : vec)
			table[a]++;
		std::vector<IntegerFrequency> res;
		for (auto& a : table) {
			res.push_back({ a.first,a.second });
		}
		std::sort(res.begin(), res.end(), [](const IntegerFrequency& a, const IntegerFrequency& b)
			{
				return a.second < b.second;
			});
		return res;
	}
#ifdef TEST_UNIT
	void test_factor()
	{
		long long a = 2*2*3*4*233*7681;
		std::vector<long long> ans;
		factor(a, ans);
		for (auto a : ans)
			std::cout << a << " ";
	}
#endif
}