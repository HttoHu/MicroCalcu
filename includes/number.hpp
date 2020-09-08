#pragma once
#include "core.hpp"
#include "error.hpp"
#include <string>
#include <memory>
namespace mcalcu
{
	class Number;
	using NumObj = std::shared_ptr<Number>;
	enum NumberKind
	{
		INTEGER,FRACTION,IRRATIONAL,COMPOUND
	};
	enum OpKind
	{
		ADD,SUB,MUL,DIV,POW
	};
	std::string to_string(NumberKind nk);
	std::string to_string(OpKind ok);


	enum CompareOp
	{
		GT,LT,GE,LE,EQ,NE
	};
	// The Basic Class that represents a concrate value such as integer ,fraction ,irational
	// 1, 1/2, 2^(1/2) + 3^(1/3)
	class Number
	{
	public:
		Number(NumberKind num_type) :number_type(num_type) {}
		NumberKind get_number_kind()const { return number_type; }
		// to print the number
		virtual std::string to_string() {
			throw Error("method to_string() haven't been overrided");
		}
		virtual NumObj common_factor(const NumObj& c) {
			throw Error("method common_factor() haven't been overrided");
		}
		virtual NumObj convert(NumberKind kind) {
			throw Error("method convert() haven't been overrided");
		}
		virtual NumObj simplify() {
			throw Error("method simplify() haven't been overrided");
		}
		virtual long double calcu() {
			throw Error("method calcu() haven't been overrided");
		}
		virtual NumObj clone() {
			return nullptr;
		}
		virtual ~Number() {}
	private:
		NumberKind number_type;
	};

	// common bin operator such as + ,- ,* ,/

	NumObj bin_op(const NumObj& lhs, const NumObj& rhs, OpKind op);
	// compare operation such as < > <= >= 
	bool compare_op(const NumObj& lhs, const NumObj& rhs, OpKind op);

	NumObj operator+(const NumObj& lhs, const NumObj& rhs);
	NumObj operator-(const NumObj& lhs, const NumObj& rhs);
	NumObj operator*(const NumObj& lhs, const NumObj& rhs);
	NumObj operator/(const NumObj& lhs, const NumObj& rhs);

	class Integer :public Number
	{
	public:
		static NumObj from(long long v);
		static long long get_value(const NumObj& obj);

		Integer(long long v) :value(v), Number(NumberKind::INTEGER) {}
		std::string to_string() override;
		NumObj common_factor(const NumObj& c)override;
		NumObj convert(NumberKind kind)override;
		NumObj simplify()override;
		NumObj clone()override;
		long double calcu()override;


	private:
		long long value;
	};

	class Fraction :public Number
	{
	public:
		static NumObj from(const NumObj& _numerator, const NumObj& _denominator);
		static NumObj reciprocal(const NumObj& frac);

		Fraction(const NumObj& _numerator, const NumObj& _denominator) :Number(NumberKind::FRACTION),numerator(_numerator), denominator(_denominator) {}
		std::string to_string() override;
		NumObj common_factor(const NumObj& c)override;
		NumObj convert(NumberKind kind)override;
		NumObj simplify()override;
		NumObj clone()override;
		long double calcu()override;


		NumObj numerator;
		NumObj denominator;
	};
}