/*
	Resource list library
	Copyright (c) 2022-present cam900 and contributors
	see https://gitlab.com/cam900/resource_list/-/blob/main/LICENSE for details

	Example usage of library
*/

#include "resource_list.hpp"
#include <iostream>

int main(int arg_num, char** arg_val)
{
	resource_list<int> something;
    // init
	std::cout << "list size is " << something.size() << std::endl;
	resource_id a = something.insert(30);
	resource_id b = something.insert(72);
	resource_id c = something.insert(17);
    // get size
	std::cout << "list size is " << something.size() << std::endl;
	for (auto it = something.cbegin(); it != something.cend(); it++)
	{
		std::cout << "id " << it->first << ": " << it->second << std::endl;
	}
    // remove something and get current status
	something.erase(b);
	std::cout << "list size is " << something.size() << std::endl;
	for (auto it = something.cbegin(); it != something.cend(); it++)
	{
		std::cout << "id " << it->first << ": " << it->second << std::endl;
	}
	something.erase(a);
    // add another thing
	resource_id d = something.emplace(30);
	resource_id e = something.emplace(11);
	resource_id f = something.emplace(21);
	std::cout << "list size is " << something.size() << std::endl;
	for (auto it = something.cbegin(); it != something.cend(); it++)
	{
		std::cout << "id " << it->first << ": " << it->second << std::endl;
	}
	return 0;
}
