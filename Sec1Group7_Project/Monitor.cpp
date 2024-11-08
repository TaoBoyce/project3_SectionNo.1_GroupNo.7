#include "Monitor.h"

template<typename T>
Monitor<T>::Monitor()
{
	//data vector by default is initialized as empty
}

template<typename T>
T Monitor<T>::parseData(std::string line)
{
	return T();
}

template<typename T>
T Monitor<T>::getFlux()
{
	return T();
}

template<typename T>
std::vector<T> Monitor<T>::readFromFile(std::string filename)
{
	return std::vector<T>();
}

template<>
int Monitor<int>::parseData(std::string filename)
{
	return 0;
}

template<>
float Monitor<float>::parseData(std::string filename)
{
	return 0.0f;
}

