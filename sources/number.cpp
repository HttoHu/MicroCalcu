#include "../includes/number.hpp"
#include "../includes/core.hpp"
namespace mcalcu
{
	namespace op
	{
		NumObj integer_add(const NumObj& lhs, const NumObj& rhs)
		{
		}
	}
	NumObj bin_op(const NumObj& lhs, const NumObj& rhs, OpKind op)
	{
		return NumObj();
	}

	NumObj Integer::from(long long v)
	{
		return std::make_shared<Integer>(v);
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
		switch (get_number_kind())
		{
		case INTEGER:
			return Integer::from(value);
		default:
			throw Error("failed to convert");
		}
	}

}