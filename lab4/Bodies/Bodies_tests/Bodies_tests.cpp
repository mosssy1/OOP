#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Bodies/CBody.h"
#include "../Bodies/CBodyController.h"
#include "../Bodies/CCompound.h"
#include "../Bodies/CCone.h"
#include "../Bodies/CCylinder.h"
#include "../Bodies/CParallelepiped.h"
#include "../Bodies/CSolidBody.h"
#include "../Bodies/CSphere.h"
#include "../Bodies/Result.h"
#include <sstream>

const std::string STRING_SPHERE = "Сфера:\n\tПлонтность = 20\n\tОбъём = 113.0973355\n\tМасса = 2261.946711\n\tradius = 3\n";
const std::string STRING_PARALLELEPIPED = "Параллелепипед:\n\tПлонтность = 20\n\tОбъём = 60000\n\tМасса = 1200000\n\tДлина параллелепипеда : 30\n\tШирина парллелепипеда : 40\n\tГлубина параллелепипеда : 50\n";
const std::string STRING_CONE = "Конус:\n\tПлонтность = 40\n\tОбъём = 12566.37061\n\tМасса = 502654.8246\n\tБазовый радиус конуса : 20\n\tВысота конуса : 30\n";
const std::string STRING_CYLINDER = "Цилиндр:\n\tПлонтность = 40\n\tОбъём = 37699.11184\n\tМасса = 1507964.474\n\tБазовый радиус цилиндра : 20\n\tВысота цилиндра : 30\n";

TEST_CASE("CheckSphere")
{
	CSphere sphere(20, 3);
	SECTION("Check Sphere")
	{
		REQUIRE(sphere.GetType() == "Сфера");
		REQUIRE(sphere.GetRadius() == 3);
		REQUIRE(sphere.GetDensity() == 20);
		REQUIRE(round(sphere.GetVolume() * 1000) / 1000 == 113.097);
		REQUIRE(round(sphere.GetMass() * 1000) / 1000 == 2261.947);
		std::ostringstream output;
		REQUIRE(sphere.ToString(output) == STRING_SPHERE);
	}
	CParallelepiped parallelepiped(20, 30, 40, 50);
	SECTION("Check Parallelepiped")
	{
		REQUIRE(parallelepiped.GetDensity() == 20);
		REQUIRE(parallelepiped.GetHeight() == 30);
		REQUIRE(parallelepiped.GetWidth() == 40);
		REQUIRE(parallelepiped.GetDepth() == 50);
		REQUIRE(parallelepiped.GetVolume() == 60000);
		REQUIRE(parallelepiped.GetMass() == 1200000);
		REQUIRE(parallelepiped.GetType() == "Параллелепипед");
		std::ostringstream output;
		REQUIRE(parallelepiped.ToString(output) == STRING_PARALLELEPIPED);
	}
	CCone cone(20, 30, 40);
	SECTION("Check cone")
	{
		REQUIRE(cone.GetBaseRadius() == 20);
		REQUIRE(cone.GetHeight() == 30);
		REQUIRE(round(cone.GetVolume() * 1000) / 1000 == 12566.371);
		REQUIRE(round(cone.GetMass() * 1000) / 1000 == 502654.825);
		REQUIRE(cone.GetType() == "Конус");
		std::ostringstream output;
		REQUIRE(cone.ToString(output) == STRING_CONE);
	}
	CCylinder cylinder(20, 30, 40);
	SECTION("Check cylinder")
	{
		REQUIRE(cylinder.GetType() == "Цилиндр");
		REQUIRE(cylinder.GetBaseRadius() == 20);
		REQUIRE(cylinder.GetHeight() == 30);
		REQUIRE(round(cylinder.GetVolume() * 1000) / 1000 == 37699.112);
		REQUIRE(round(cylinder.GetMass() * 1000) / 1000 == 1507964.474);
		std::ostringstream output;
		REQUIRE(cylinder.ToString(output) == STRING_CYLINDER);
	}
	
}

TEST_CASE("Add Body")
{
	std::ostringstream output;
	SECTION("Add Sphere")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("1\n1\n20 3");
		CBodyController cbody(input, output, bodies);
		REQUIRE(cbody.Interpret().status == Status::OK);
		REQUIRE(bodies.size() == 1);
	}
	SECTION("Add Parallelepiped")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("1\n2\n20 30 40 50");
		CBodyController cbody(input, output, bodies);
		REQUIRE(cbody.Interpret().status == Status::OK);
		REQUIRE(bodies.size() == 1);
	}
	SECTION("Add Cone")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("1\n3\n20 30 40");
		CBodyController cbody(input, output, bodies);
		REQUIRE(cbody.Interpret().status == Status::OK);
		REQUIRE(bodies.size() == 1);
	}
	SECTION("Add Cylinder")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("1\n4\n20 30 40");
		CBodyController cbody(input, output, bodies);
		REQUIRE(cbody.Interpret().status == Status::OK);
		REQUIRE(bodies.size() == 1);
	}
	SECTION("Add Compound Body")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("1\n5\n3\n20 30 40\n1\n20 40");
		CBodyController cbody(input, output, bodies);
		while (input)
		{
			cbody.Interpret();
		}
		REQUIRE(bodies.size() == 1);
	}
}
TEST_CASE("Enter add body and exit")
{
	std::ostringstream output;
	SECTION("Simple Body")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("1\n5");
		CBodyController cbody(input, output, bodies);
		while (!input.eof())
		{
			REQUIRE(cbody.Interpret().status != Status::ERROR_);
		}
		REQUIRE(bodies.size() == 0);
	}
	SECTION("Compound Body")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("5\n5");
		CBodyController cbody(input, output, bodies);
		while (!input.eof())
		{
			REQUIRE(cbody.Interpret().status != Status::ERROR_);
		}
		REQUIRE(bodies.size() == 0);
	}
}

TEST_CASE("Not exist command")
{
	std::ostringstream output;
	SECTION("Empty command")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("");
		CBodyController cbody(input, output, bodies);
		REQUIRE(cbody.Interpret().status == Status::ERROR_);
		REQUIRE(bodies.size() == 0);
	}
	SECTION("Not exist command")
	{
		std::vector<std::shared_ptr<CBody>> bodies;
		std::istringstream input("jsasj");
		CBodyController cbody(input, output, bodies);
		REQUIRE(cbody.Interpret().status == Status::ERROR_);
		REQUIRE(output.str() == "Команды:\n1 - Добавить тело\n2 - Найти тело с наибольшей массой\n3 - Найти тело которое будет легче всего весить в воде\n4 - Вывести информацию обо всех телах\n5 - Выйти из программы\n");
		REQUIRE(bodies.size() == 0);
	}
}

TEST_CASE("Cyclic body insertion")
{
	auto b1 = std::make_shared<CCompound>();
	auto b2 = std::make_shared<CCompound>();
	auto b3 = std::make_shared<CCompound>();
	b1->AddChild(b2);
	b2->AddChild(b3);
	REQUIRE(!b3->AddChild(b1));
	REQUIRE(!b2->AddChild(b2));

}
