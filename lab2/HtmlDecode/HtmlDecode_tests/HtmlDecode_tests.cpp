#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HtmlDecode/HtmlDecodeProcessor.h"

#include <iostream>
#include <vector>

TEST_CASE("encoded string")
{
	SECTION("empty string results")
	{
		std::string input;
		const std::string decode = HtmlDecode(input);

		REQUIRE(decode.empty());
	}

	SECTION("string without html characters")
	{
		std::string input("A simple example with some text");
		const std::string decode = HtmlDecode(input);

		REQUIRE(decode == input);
	}

	SECTION("simple example")
	{
		std::string input("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
		const std::string decode = HtmlDecode(input);
		const std::string answer = "Cat <says> \"Meow\". M&M's";

		REQUIRE(decode == answer);
	}

	SECTION("collision of two html characters")
	{
		const std::string input = "&amp;lt;";
		auto const decode = HtmlDecode(input);
		const std::string answer = "&lt;";

		REQUIRE(decode == answer);
	}
}
