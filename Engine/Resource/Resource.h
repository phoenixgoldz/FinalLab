#pragma once
#include <string>


namespace phoenix
{
	class Resource
	{
	public:
		virtual bool Create(const std::string filename, ...) = 0;
	};
}



