#include "Preprocessor.h"

namespace com {

	std::string Preprocessor::process(const std::vector<std::string>& file)
	{
		std::string res = "";
		char last = '\0';
		bool inComment = false;
		for (std::string line : file)
		{
			for (char c : line)
			{
				if (inComment)
				{
					if (last == '*' && c == '/')
					{
						inComment = false;
						last = '\0';
						continue;
					}
				}
				else
				{
					if (last == '/' && c == '*')
					{
						inComment = true;
						last = '\0';
						continue;
					}
					else if (last == '/' && c == '/')
					{
						last = '\0';
						break;
					}
					else if (std::string("\t\n\r ").find(c) != std::string::npos)
					{
						continue;
					}

					if (last != '\0')
						res += last;
				}

				last = c;
			}
		}
		if (last != '\0')
			res += last;
		return res;
	}

}
