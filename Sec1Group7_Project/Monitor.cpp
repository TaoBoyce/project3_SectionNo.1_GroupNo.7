#include "Monitor.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

template<typename T>
Monitor<T>::Monitor()
{
	data.clear();
}

template<typename T>
T Monitor<T>::parseData(std::string line)
{
	//Non-supported type goes here
	return T();
}

template<>
int Monitor<int>::parseData(std::string line)
{
	//specification for integer type
	int num = 0;
	num = std::stoi(line);//try to convert to int
	return num;
}

template<>
float Monitor<float>::parseData(std::string line)
{
	//specification for float type
	float num = 0.0f;
	num = std::stof(line);//try to convert to float
	return num;
}

template<typename T>
T Monitor<T>::getFlux()
{
	if (data.empty()) {
		return T(); //returns empty if data is empty
	}
	int entryNum = rand() % data.size();
	return data[entryNum];
}

template<typename T>
std::vector<T> Monitor<T>::readFromFile(std::string filename)
{
	std::ifstream fin;
	fin.open(filename);

	if (!fin.is_open) {
		return data;
	}

	//clear data for new data
	data.clear();

	//read file until end, filling data with parsed data
	std::string line;
	while (std::getline(fin, line)) {
		try {//error handling
			data.push_back(parseData(line));
		}
		catch (std::exception e) {//catch unconvertable input
			return data;
		}
	}

	return data;
}
