#pragma once

#include "../CppProperties/CppProperties.h"
#include <string>

class X
{
public:
	Property<std::string> name;
	Property<std::string> category;
	Property<std::string> data;
	Property<std::string> description;
	Property<double> pi;


};