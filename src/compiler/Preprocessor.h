#pragma once

#include <string>
#include <vector>

namespace com {

	class Preprocessor
	{
	public:
		std::string process(const std::vector<std::string>& file);
	};

}
