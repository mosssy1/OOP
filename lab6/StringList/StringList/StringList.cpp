#include <iostream>
#include "CStringList.h"

int main()
{
	CStringList tmp;
	tmp.PushBack("Hello");
	tmp.PushBack("World");
	auto tmp1 = tmp.rbegin();
}
