#pragma once
#include "core.hpp"
#include "error.hpp"
#include <string>
namespace mcalcu
{
	enum NumberKind
	{
		Integer,Fraction,Irrational,Compound_Number
	};
	// The Basic Class that represents a concrate value such as integer ,fraction ,irational
	// 1, 1/2, 2^(1/2) + 3^(1/3)
	class Number
	{
	public:
		Number(NumberKind num_type) :number_type(num_type) {}
		NumberKind get_number_kind()const { return number_type; }
		virtual std::string to_string() {
			throw Error("method to_string() haven't been overrided");
		}
		virtual Number common_factor(Number c) {
			throw Error("method common_factor() haven't been overrided");
		}
		virtual Number convert(NumberKind kind)
		{

		}
		virtual ~Number() {}
	private:
		NumberKind number_type;
	};
	// 
	class Integer :public Number
	{
	public:
		Integer(long long v) :value(v), Number(NumberKind::Integer) {}

	private:
		long long value;
	};
}