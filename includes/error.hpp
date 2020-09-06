#pragma once
#include <iostream>
#include <string>
namespace mcalcu
{
	class Error
	{
	public:
		Error(const std::string &str):content(str){}
		std::string what()const
		{
			return content;
		}
	private:
		std::string content;
	};
}