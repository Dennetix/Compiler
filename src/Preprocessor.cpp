#include "Preprocessor.h"

namespace com {

	std::string Preprocessor::process(const std::vector<std::string>& file)
	{
		std::string res = "";
		for (std::string line : file)
		{
			bool inString = false;
			char last = '\0';
			for (char c : line)
			{
				if (c == '"')
				{
					inString = !inString;
				}
				else if (!inString && c == '/' && last == '/')
				{
					last = '\0';
					break;
				}
				else if (!inString && c == ' ' && last == ' ')
				{
					last = '\0';
				}
				else if (!inString && (c == '\n' || c == '\r'))
				{
					c = '\0';
				}
				else if (!inString && c == '\t')
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
