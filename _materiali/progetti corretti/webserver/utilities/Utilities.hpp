#pragma once

#include <string>
#include <vector>

class Utilities
{
	public:
		Utilities(){};
		~Utilities(){};
		static std::string join(std::vector<std::string> v, std::string delims);
		static std::string to_lower(std::string str);
		static std::vector<std::string> split(std::string req, std::string delims, bool skip_empty);
		static std::string trim(std::string str);
};