/*
Author:		Bruce Wheeler
Class:		CST 276
Task:		Lab 1 - Singleton Pattern
file:		Config.h
Date:		1/23/23
*/
#pragma once

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

// Will generate one copy of the original instance each and every time that it is called
// allowing for multiple copies of the original to exist on screen (for this application),
// does NOT create new instance each time.
class Config {

public:
	unsigned int width{100};				// needed variables for display information
	unsigned int height{100};
	float radius{10};

	friend std::istream& operator>>(std::istream& in, Config& a) {
		std::string line;
		std::getline(in, line);
		std::istringstream inn(line);
		inn >> a.width;
		inn >> a.height;
		inn >> a.radius;
		return in;
	}

	static Config& getInstance(std::string& a){		
		static Config instance;
		std::ifstream input_file(a);
		input_file >> instance;
		return instance;
	}
  
private:
	Config()= default;
	~Config()= default;
	Config(const Config&)= delete;
	Config& operator=(const Config&)= delete;

};
