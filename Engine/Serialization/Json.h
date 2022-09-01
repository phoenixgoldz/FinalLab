#pragma once 
#include "rapidjson/document.h" 
#include <string> 

namespace phoenix
{
	namespace json
	{
		bool Load(const std::string& filename, rapidjson::Document& document);

		bool Get(const rapidjson::Value& value, const std::string& name, int& data);
	};
}