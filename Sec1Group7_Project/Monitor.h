#pragma once
#include <vector>
#include <string>

template <typename T>
class Monitor {
private:
	std::vector<T> data;
public:
	T parseData(std::string line);
	T getFlux();
	std::vector<T> readFromFile(std::string filename);
	Monitor();
};

template <>
int Monitor<int>::parseData(std::string line);
template <>
float Monitor<float>::parseData(std::string line);