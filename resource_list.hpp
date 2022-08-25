/*
	Resource list library
	Copyright (c) 2022-present cam900 and contributors
	see https://gitlab.com/cam900/resource_list/-/blob/main/LICENSE for details

	usage:

	top of source:
	#include "location/of/resource_list.hpp"

	construct:
	resource_list<class> something;

	destruct:
	~something();

	insert something to list:
	resource_id a = something.insert(anything);
	or
	resource_id a = something.emplace(anything);

	erase something from list:
	something.erase(a);

	get data from list:
	class b = something.get(a);

	check error string:
	get_error_string();

	details are below
*/

#ifndef _RESOURCE_LIST
#define _RESOURCE_LIST

#pragma once

#include <functional>
#include <unordered_map>
#include <queue>
#include <string>

typedef std::size_t resource_id;

template<class _Ty>
class resource_list
{
public:
	// constructor
	resource_list()
		: error_string("")
		, stored_list()
		, deleted_list()
	{}

	// destructor
	~resource_list()
	{
		if (!stored_list.empty())
		{
			stored_list.clear();
		}
		while (!deleted_list.empty())
		{
			deleted_list.pop();
		}
	}

	// add resource to list
	resource_id insert(_Ty source)
	{
		no_error();
		resource_id id = stored_list.size();
		if (!deleted_list.empty())
		{
			id = deleted_list.top();
			deleted_list.pop();
		}
		stored_list.insert(std::make_pair(id, source));
		return id;
	}

	resource_id emplace(_Ty source)
	{
		no_error();
		resource_id id = stored_list.size();
		if (!deleted_list.empty())
		{
			id = deleted_list.top();
			deleted_list.pop();
		}
		stored_list.emplace(id, source);
		return id;
	}

	// remove resource from list
	void erase(resource_id id)
	{
		no_error();
		if (!stored_list.empty())
		{
			deleted_list.push(id);
			stored_list.erase(id);
		}
		else
		{
			error_string = "Trying to remove resource from empty list!";
			return;
		}
	}

	// get resource from list
	_Ty get(resource_id id)
	{
		no_error();
		if (!exists(id))
		{
			error_string = "Trying to accessing empty list!";
			return _Ty(0);
		}
		return stored_list.at(id);
	}

	// check resource exists in id
	bool exists(resource_id id)
	{
		no_error();
		return ((!empty()) && (stored_list.count(id) > 0));
	}

	// check if list is empty
	bool empty()
	{
		no_error();
		return stored_list.empty();
	}

	// check list size
	std::size_t size()
	{
		no_error();
		return stored_list.size();
	}

	// get list
	std::unordered_map<resource_id, _Ty> list()
	{
		no_error();
		return stored_list;
	}

	// get list begin
	typename std::unordered_map<resource_id, _Ty>::iterator begin() noexcept
	{
		return stored_list.begin();
	}

	typename std::unordered_map<resource_id, _Ty>::const_iterator cbegin() const noexcept
	{
		return stored_list.cbegin();
	}

	// get list end
	typename std::unordered_map<resource_id, _Ty>::iterator end() noexcept
	{
		return stored_list.end();
	}

	typename std::unordered_map<resource_id, _Ty>::const_iterator cend() const noexcept
	{
		return stored_list.cend();
	}

	// operator override
	_Ty operator[](resource_id id) const
	{
		no_error();
		if (!exists(id))
		{
			error_string = "Trying to accessing empty list!";
			return _Ty(0);
		}
		return stored_list[id];
	}

	// get error string
	std::string get_error_string()
	{
		return error_string;
	}

private:
	// error string
	std::string error_string;
	// containers
	std::unordered_map<resource_id, _Ty> stored_list;
	std::priority_queue<resource_id, std::vector<resource_id>, std::greater<resource_id>> deleted_list;

	// internal functions
	void no_error()
	{
		error_string = "No error.";
	}
};

#endif