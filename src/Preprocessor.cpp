#include "Preprocessor.h"

namespace com {

	std::string Preprocessor::process(const std::vector<std::string>& file)
	{
		std::string res = "";
		for (std::string line : file)
		{
			char last = '\0';
			for (char c : line)
			{
				if (c == '/' && last == '/')
				{
					last = '\0';
					break;
				}
				else if (c == ' ' && last == ' ')
				{
					last = '\0';
				}
				else if (c == '\n' || c == '\r')
				{
					c = '\0';
				}
				else if (c == '\t')
				{
					c = ' ';
				}

				if (last != '\0')
					res += last;
				last = c;
			}
			if (last != '\0')
				res += last;
		}
		return res;
	}

}
