#pragma once
#include "core.hpp"
#include "error.hpp"
#include <string>
#include <memory>
#include <map>
namespace mcalcu
{
	class Number;
	using NumObj = std::shared_ptr<Number>;
	enum NumberKind
	{
		INTEGER, FRACTION, IRRATIONAL, COMPOUND,REAL,
	};
	enum OpKind
	{
		ADD, SUB, MUL, DIV, POW
	};
	std::string to_string(NumberKind nk);
	std::string to_string(OpKind ok);
	struct NumberType
	{
		NumberType() = default;
		NumberType(int _level, std::string _name) :level(_level), name(_name) {}
		// high level reveals the complexity of the type. Usually, the low level object can convert to the high level object.
		int level;
		bool need_to_convert(const NumberType& nt);
		std::string name;
	};
	extern std::map<NumberKind, NumberType> number_type_table;


	enum CompareOp
	{
		GT, LT, GE, LE, EQ, NE
	};
	// The Basic Class that represents a concrate value such as integer ,fraction ,irational
	// 1, 1/2, 2^(1/2) + 3^(1/3)
	class Number
	{
	public:
		NumberKind get_number_kind()const { return number_type; }
		Number(NumberKind nk) :number_type(nk) {}
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
		virtual long double calcu() const{
			throw Error("method calcu() haven't been overrided");
		}
		// to query wheter the object is a single number or made up with many number like (3+2^(-1/2)+4^(3/4))
		virtual bool single_number() { return false; }
		virtual NumObj clone() {
			return nullptr;
		}
		virtual ~Number() {}
	private:
		NumberKind number_type;
	};
	bool operator==(const NumObj& a, const NumObj& b);
	// common bin operator such as + ,- ,* ,/

	NumObj bin_op(const NumObj& lhs, const NumObj& rhs, OpKind op);
	// compare operation such as < > <= >= 
	bool compare_op(const NumObj& lhs, const NumObj& rhs, OpKind op);
	NumObj pow(const NumObj& num, int times);
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
		bool single_number()override { return true; }
		NumObj clone()override;
		long double calcu()const override;


	private:
		long long value;
	};
	class Real : public Number {
	public:
		static NumObj from(long double v);

		Real(long double _v) :Number(REAL),value(_v) {}
		std::string to_string()override;
		NumObj clone()override;
		NumObj simplify()override { return clone(); }
		long double calcu()const override { return value; }
		bool single_number()override { return true; }
	private:
		long double value;
	};

	class Fraction :public Number
	{
	public:
		static NumObj from(const NumObj& _numerator, const NumObj& _denominator);
		static NumObj reciprocal(const NumObj& frac);

		Fraction(const NumObj& _numerator, const NumObj& _denominator) :Number(NumberKind::FRACTION), numerator(_numerator->clone()), denominator(_denominator) {}
		std::string to_string() override;
		NumObj common_factor(const NumObj& c)override;
		NumObj convert(NumberKind kind)override;
		NumObj simplify()override;
		bool single_number()override;
		NumObj clone()override;
		long double calcu()const override;


		NumObj numerator;
		NumObj denominator;
	};

	class Irrational : public Number
	{
	public:
		static NumObj from(NumObj _base, NumObj _expo, NumObj _o = Integer::from(1));
		Irrational(NumObj _base, NumObj _expo,NumObj _o= Integer::from(1)) :Number(IRRATIONAL), base(_base), expo(_expo),
			outer(_o) {}
		NumObj convert(NumberKind kind)override;
		NumObj simplify()override;
		std::string to_string()override;
		bool single_number()override;
		NumObj clone()override;
		long double calcu()const override;

		NumObj base;
		NumObj expo;
		NumObj outer;
	};

	class Compound : public Number {
	public:
	private:

	};
}