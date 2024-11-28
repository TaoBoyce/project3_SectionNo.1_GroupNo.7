#pragma once
#include <vector>
#include <string>

template <typename T>
class Monitor {
private:
	std::vector<T> data;
	T parseData(std::string line);
protected:
	T getFlux();
	std::vector<T> readFromFile(std::string filename);
public:
	Monitor();
};

template <>
int Monitor<int>::parseData(std::string line);
template <>
float Monitor<float>::parseData(std::string line);
