#pragma once
#include<string>
#include "Vector.h"

class Company {

public:
	std::string company_name;
	Vector<std::string> services;
	std::string adress;
};

class Customer {

public:
	std::string name;
	std::string service;
	std::string company_name;
	uint16_t volume;
};