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
		virtual void simplify() {}
		virtual ~Number() {}
	private:
		NumberKind number_type;
	};
	// common bin operator such as + ,- ,* ,/ 
	NumObj bin_op(const NumObj& lhs, const NumObj& rhs, OpKind op);
	bool compare_op(const NumObj& lhs, const NumObj& rhs, OpKind op);
	class Integer :public Number
	{
	public:
		static NumObj from(long long v);
		Integer(long long v) :value(v), Number(NumberKind::INTEGER) {}
		std::string to_string() override;
		NumObj common_factor(const NumObj& c)override;
		NumObj convert(NumberKind kind)override;
		long long get_value()const { return value; }
	private:
		long long value;
	};
}