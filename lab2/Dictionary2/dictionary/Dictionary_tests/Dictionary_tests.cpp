#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../dictionary/DictionaryProcessor.h"

TEST_CASE("Load word to dictionary")
{
	Dictionary dictionary = {};
	std::string line = "cat кот, кошка";

	LoadWordWithTranslationToDictionary(dictionary, line);
	REQUIRE(dictionary.find("cat") != dictionary.end());
	REQUIRE(dictionary["cat"] == "кот, кошка");

}

TEST_CASE("String to lower")
{
	SECTION("string")
	{
		std::string line = "CaT";

		line = StringToLower(line);
		REQUIRE(line == "cat");
	}
}