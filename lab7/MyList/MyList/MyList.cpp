﻿#include <iostream>
#include "CMyList.hpp"

int main()
{
	CMyList<int> lst;

	for (int i = 0; i < 100000; i++)
	{
		lst.PushBack(1);
	}
	return 0;
}

