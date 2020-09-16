#include "../includes/number.hpp"
#include "../includes/core.hpp"
#include <map>
namespace mcalcu
{

	std::map<NumberKind, NumberType> number_type_table
	{
		{INTEGER,NumberType(1,"int")},{FRACTION,NumberType(2,"frac")}
	};
	namespace op
	{


		NumObj integer_add(const NumObj& lhs, const NumObj& rhs)
		{
			return Integer::from(Integer::get_value(lhs) + Integer::get_value(rhs));
		}
		NumObj integer_mul(const NumObj& lhs, const NumObj& rhs)
		{
			return Integer::from(Integer::get_value(lhs) * Integer::get_value(rhs));
		}
		NumObj integer_sub(const NumObj& lhs, const NumObj& rhs)
		{
			return Integer::from(Integer::get_value(lhs) - Integer::get_value(rhs));
		}
		NumObj integer_div(const NumObj& lhs, const NumObj& rhs)
		{
			long long a = Integer::get_value(lhs), b = Integer::get_value(rhs);
			if (a % b == 0)
				return Integer::from(a / b);
			return Fraction::from(lhs, rhs);
		}
		NumObj fraction_add(const NumObj& lhs, const NumObj& rhs)
		{
			auto lhs_num = std::static_pointer_cast<Fraction> (lhs)->numerator;
			auto rhs_num = std::static_pointer_cast<Fraction> (rhs)->numerator;
			auto demo = lhs_num * rhs_num;
			auto lhs_deno = std::static_pointer_cast<Fraction> (lhs)->denominator;
			auto rhs_deno = std::static_pointer_cast<Fraction> (rhs)->denominator;
			auto num = lhs_num * rhs_deno + rhs_num * lhs_deno;
			return Fraction::from(num, demo)->simplify();
		}
		NumObj fraction_sub(const NumObj& lhs, const NumObj& rhs)
		{
			auto lhs_num = std::static_pointer_cast<Fraction> (lhs)->numerator;
			auto rhs_num = std::static_pointer_cast<Fraction> (rhs)->numerator;
			auto demo = lhs_num * rhs_num;
			auto lhs_deno = std::static_pointer_cast<Fraction> (lhs)->denominator;
			auto rhs_deno = std::static_pointer_cast<Fraction> (rhs)->denominator;
			auto num = lhs_num * rhs_deno - rhs_num * lhs_deno;
			return Fraction::from(num, demo)->simplify();
		}
		NumObj fraction_mul(const NumObj& lhs, const NumObj& rhs)
		{
			auto lhs_num = std::static_pointer_cast<Fraction> (lhs)->numerator;
			auto rhs_num = std::static_pointer_cast<Fraction> (rhs)->numerator;
			auto lhs_deno = std::static_pointer_cast<Fraction> (lhs)->denominator;
			auto rhs_deno = std::static_pointer_cast<Fraction> (rhs)->denominator;
			return Fraction::from(lhs_num * rhs_num, rhs_deno * lhs_deno)->simplify();
		}
		NumObj fraction_div(const NumObj& lhs, const NumObj& rhs)
		{
			return fraction_mul(lhs, Fraction::reciprocal(rhs));
		}

		NumObj real_add(const NumObj& lhs, const NumObj& rhs) {
			return Real::from(lhs->calcu() + rhs->calcu());
		}

		NumObj real_mul(const NumObj& lhs, const NumObj& rhs) {
			return Real::from(lhs->calcu() * rhs->calcu());
		}

		NumObj real_div(const NumObj& lhs, const NumObj& rhs) {
			return Real::from(lhs->calcu() / rhs->calcu());
		}
		NumObj real_sub(const NumObj& lhs, const NumObj& rhs) {
			return Real::from(lhs->calcu() - rhs->calcu());
		}
		NumObj irrational_mul(const NumObj& lhs, const NumObj& rhs)
		{
			auto left = std::static_pointer_cast<Irrational> (lhs), right = std::static_pointer_cast<Irrational>(rhs);
			if (left->expo == right->expo)
			{
				auto new_base = left->base * right->base;
				auto new_outer = left->outer * right->outer;
				auto ret = Irrational::from(new_base,left->expo->clone(),new_outer);
				return ret->simplify();
			}
			else if (left->base == right->base && left->outer == right->outer) {
				auto new_expo = left->expo + right->expo;
				return Irrational::from(left->base->clone(), new_expo, left->outer->clone()->simplify());
			}
			return Real::from(left->calcu() * right->calcu());
		}
		NumObj irrational_div(const NumObj& lhs, const NumObj& rhs)
		{
			auto left = std::static_pointer_cast<Irrational> (lhs), right = std::static_pointer_cast<Irrational>(rhs);
			if (left->expo == right->expo)
			{
				auto new_base = left->base / right->base;
				auto new_outer = left->outer / right->outer;
				auto ret = Irrational::from(new_base, left->expo->clone(), new_outer);
				return ret->simplify();
			}
			else if (left->base == right->base && left->outer == right->outer) {
				auto new_expo = left->expo - right->expo;
				return Irrational::from(left->base->clone(), new_expo, left->outer->clone()->simplify());
			}
			return Real::from(left->calcu() / right->calcu());
		}
		using BinOpFuncType = decltype(&integer_add);

		std::map<std::pair<NumberKind, OpKind>, BinOpFuncType> bin_op_map
		{
			{{INTEGER,ADD},integer_add},{{INTEGER,SUB},integer_sub},{{INTEGER,MUL},integer_mul},{{INTEGER,DIV},integer_div},
			{{FRACTION,ADD},fraction_add},{{FRACTION,SUB},fraction_sub},{{FRACTION,MUL},fraction_mul},{{FRACTION,DIV},fraction_div},
			{{REAL,ADD},real_add},{{REAL,SUB},real_sub,} ,{{ REAL,MUL }, real_mul},{{ REAL,DIV }, real_div},
			{{IRRATIONAL,MUL},irrational_mul},{{IRRATIONAL,DIV},irrational_div},
		};
	}

	std::string to_string(NumberKind nk)
	{
		std::map<NumberKind, std::string> table
		{
			{INTEGER,"int"},{FRACTION,"frac"},{IRRATIONAL,"irrational"},{COMPOUND,"compound"}
		};
		return table[nk];
	}
	std::string to_string(OpKind ok)
	{
		std::map<OpKind, std::string> table
		{
			{ADD,"add"},{SUB,"sub"},{MUL,"mul"},{DIV,"div"}
		};
		return table[ok];
	}

	bool operator==(const NumObj& a, const NumObj& b)
	{
		return std::abs(a->calcu() - b->calcu()) < 0.0001;
	}

	NumObj bin_op(const NumObj& lhs, const NumObj& rhs, OpKind op)
	{
		if (lhs->get_number_kind() == rhs->get_number_kind())
		{// Remeber to do something to convert
			auto result = op::bin_op_map.find({ lhs->get_number_kind(),op });
			if (result == op::bin_op_map.end())
				throw Error("{type:" + to_string(lhs->get_number_kind()) + ",op:" + to_string(op) + "} operation is not compatible.");
			return result->second(lhs, rhs);
		}
		else
		{
			NumObj nobj;
			auto lhs_type = number_type_table[lhs->get_number_kind()], rhs_type = number_type_table[rhs->get_number_kind()];
			if (lhs_type.need_to_convert(rhs_type))
			{
				nobj = lhs->convert(rhs->get_number_kind());
				return bin_op(nobj, rhs, op);
			}
			else
			{
				nobj = rhs->convert(lhs->get_number_kind());
				return bin_op(lhs, nobj, op);
			}
			throw Error("NumObj bin_op(const NumObj& lhs, const NumObj& rhs, OpKind op) not finished yet ");
		}
	}

	NumObj pow(const NumObj& num, int times)
	{
		if (times < 0)
			return Fraction::from(Integer::from(1), pow(num, -times));
		else if (times == 1)
			return num;
		auto result = pow(num, times / 2);
		if (times & 1)
			return result * result * num;
		return result * result;
	}

	NumObj operator+(const NumObj& lhs, const NumObj& rhs)
	{
		return bin_op(lhs, rhs, ADD);
	}

	NumObj operator-(const NumObj& lhs, const NumObj& rhs)
	{
		return bin_op(lhs, rhs, SUB);
	}

	NumObj operator*(const NumObj& lhs, const NumObj& rhs)
	{
		return bin_op(lhs, rhs, MUL);
	}

	NumObj operator/(const NumObj& lhs, const NumObj& rhs)
	{
		return bin_op(lhs, rhs, DIV);
	}

	NumObj Integer::from(long long v)
	{
		return std::make_shared<Integer>(v);
	}

	long long Integer::get_value(const NumObj& obj)
	{
		if (obj->get_number_kind() != INTEGER)
		{
			throw Error("Integer::get_value(const NumObj& obj) Only accept Integer object!");
		}
		return std::static_pointer_cast<Integer>(obj)->value;
	}
	std::string Integer::to_string()
	{
		return "< Integer: " + std::to_string(value) + " >";
	}
	NumObj Integer::common_factor(const NumObj& c)
	{
		if (c->get_number_kind() == INTEGER)
		{
			return Integer::from(gcd(value, std::static_pointer_cast<Integer>(c)->value));
		}
		return Integer::from(1);
	}
	NumObj Integer::convert(NumberKind kind)
	{
		switch (kind)
		{
		case INTEGER:
			return Integer::from(value);
		case FRACTION:
			return Fraction::from(clone(), Integer::from(1));
		case REAL:
			return Real::from((long double)value);
		default:
			throw Error("failed to convert");
		}
	}

	NumObj Integer::simplify()
	{
		return Integer::from(value);
	}

	NumObj Integer::clone()
	{
		return Integer::from(value);
	}

	long double Integer::calcu()const
	{
		return (long double)value;
	}

	NumObj Fraction::from(const NumObj& _numerator, const NumObj& _denominator)
	{
		return std::make_shared<Fraction>(_numerator, _denominator);
	}

	NumObj Fraction::reciprocal(const NumObj& frac)
	{
		auto fracc = std::static_pointer_cast<Fraction> (frac);
		return Fraction::from(fracc->denominator, fracc->numerator);
	}

	std::string Fraction::to_string()
	{
		return "<Fraction:{" + numerator->to_string() + "},{" + denominator->to_string() + "}>";
	}

	NumObj Fraction::common_factor(const NumObj& c)
	{
		return NumObj();
	}

	NumObj Fraction::convert(NumberKind kind)
	{
		switch (kind)
		{
			// Warning, accuracy may be lost
		case mcalcu::INTEGER:
			return Integer::from(calcu());
		case mcalcu::FRACTION:
			return clone();
		case REAL:
			return Real::from(calcu());
		}
		throw Error("invalid convert");
	}

	NumObj Fraction::simplify()
	{
		numerator = numerator->simplify();
		denominator = denominator->simplify();
		auto factor = numerator->common_factor(denominator);
		numerator = numerator / factor;
		denominator = denominator / factor;
		if (numerator->get_number_kind() == INTEGER && denominator->get_number_kind() == INTEGER)
		{
			long long num = Integer::get_value(numerator), deno = Integer::get_value(denominator);
			if (num % deno == 0)
				return Integer::from(num / deno);
		}
		return clone();
	}

	bool Fraction::single_number()
	{
		return denominator->single_number() && numerator->single_number();
	}

	NumObj Fraction::clone()
	{
		return Fraction::from(numerator->clone(), denominator->clone());
	}

	long double Fraction::calcu()const
	{
		return numerator->calcu() / denominator->calcu();
	}

	bool NumberType::need_to_convert(const NumberType& nk)
	{
		return level < nk.level;
	}

	NumObj Irrational::from(NumObj _base, NumObj _expo, NumObj _o)
	{
		return std::make_shared<Irrational>(_base, _expo);
	}

	NumObj Irrational::convert(NumberKind kind)
	{
		switch (kind)
		{
		case REAL:
			return Real::from(calcu());
		case FRACTION:
			return Fraction::from(clone(), Integer::from(1));
		}
	}

	NumObj Irrational::simplify()
	{
		expo->simplify();
		base->simplify();
		outer->simplify();
		// to complex to calculate
		if (!single_number())
			return convert(REAL);


		auto one = Integer::from(1);
		// speical cases
		if (base == one)
			return outer;
		else if (expo == one)
			return base * outer;
		else if (expo == Integer::from(0))
			return outer;
		else if (expo->get_number_kind() == INTEGER)
			return pow(clone(), Integer::get_value(expo));
		// if the expo is a fraction, like 2^(1/2)
		else if (expo->get_number_kind() == FRACTION)
		{
			auto expo_frac = std::static_pointer_cast<Fraction>(expo);
			if (expo_frac->numerator->get_number_kind() != INTEGER || expo_frac->denominator->get_number_kind() != INTEGER)
				return convert(REAL);
			if (expo_frac->numerator != one)
			{
				long long times = Integer::get_value(expo_frac->numerator);
				base = pow(base, times);
				expo_frac->numerator = one->clone();
			}
			std::vector<long long> vec;
			if (base->get_number_kind() == INTEGER && expo_frac->denominator->get_number_kind() == INTEGER)
			{
				long long times = Integer::get_value(expo_frac->denominator);
				factor(Integer::get_value(base), vec);
				std::vector<IntegerFrequency> freq = count_frency(vec);
				// filter the elements whose frenquency is less than the times. 
				freq = filter<IntegerFrequency>(freq.begin(), freq.end(), [=](const IntegerFrequency& a)
					{
						return a.second >= times;
					});
				for (auto& a : freq)
				{
					outer = outer * Integer::from(std::pow(a.first, a.second / times));
					base = base / Integer::from(std::pow(a.first, (a.second / times) * times));
				}
				if (base == one)
					return base->clone();
			}
			return clone();
		}
		return clone();
	}

	std::string Irrational::to_string()
	{
		return "<Irrational: {"+outer->to_string()+"},{" + base->to_string() + "},{" + expo->to_string() + "}>";
	}

	bool Irrational::single_number()
	{
		return base->single_number();
	}

	NumObj Irrational::clone()
	{
		auto res = from(base->clone(), expo->clone(), outer->clone());
		return res;
	}

	long double Irrational::calcu()const
	{
		return outer->calcu() * std::pow<long double>(base->calcu(), expo->calcu());
	}

	NumObj Real::from(long double v)
	{
		return std::make_shared<Real>(v);
	}

	std::string Real::to_string()
	{
		return "<Real:" + std::to_string(value) + ">";
	}

	NumObj Real::clone()
	{
		return Real::from(value);
	}

}