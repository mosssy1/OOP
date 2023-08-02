#include "HtmlDecodeProcessor.h"
#include <map>


const std::map<std::string, char> htmlDicrionary = {
	{ "&quot;", '"' },
	{ "&apos;", '\'' },
	{ "&lt;", '<' },
	{ "&gt;", '>' },
	{ "&amp;", '&' }
};


void CheckSubstring(std::string const& html, unsigned& pos, char& tmpCh)
{
	for (auto& infoEntity : htmlDicrionary)
	{
		if (html.substr(pos, infoEntity.first.length()) == infoEntity.first)
		{
			tmpCh = infoEntity.second;
			pos += infoEntity.first.length() - 1;
			break;
		}
	}
};

std::string HtmlDecode(std::string const& html)
{
	std::string decodedStr;

	for (unsigned i = 0; i < html.length(); i++)
	{
		if (html[i] == '&')
		{
			char tmpCh = '&';
			CheckSubstring(html, i, tmpCh);
			decodedStr += tmpCh;
		}
		else
		{
			decodedStr += html[i];
		}
	}

	return decodedStr;
};