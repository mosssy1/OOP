#include <string>
#include <map>

using namespace std;

const map<string, char> htmlDicrionary = {
	{ "&quot;", '"' },
	{ "&apos;", '\'' },
	{ "&lt;", '<' },
	{ "&gt;", '>' },
	{ "&amp;", '&' }
};

string HtmlDecode(string const& html)
{
	string result;
	result.reserve(html.size());

	size_t pos = 0;
	while (pos < html.size())
	{
		size_t subStrStartPos = html.find("&", pos);

		if (subStrStartPos == string::npos) 
		{
			result.append(html.substr(pos));
			break;
		}

		size_t subStrEndPos = html.find(";", subStrStartPos);

		if (subStrEndPos == string::npos) 
		{
			result.append(html.substr(pos));
			break;
		}

		result.append(html.substr(pos, subStrStartPos - pos));
		string entity = html.substr(subStrStartPos, subStrEndPos - subStrStartPos + 1);
		auto it = htmlDicrionary.find(entity);

		if (it != htmlDicrionary.end())
		{
			result.push_back(it->second);
		}
		else
		{
			result.append(entity);
		}

		pos = subStrEndPos + 1;
	}

	return result;
}