#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

class PowerUsage {
private:
	std::vector<int>powerData;
	//powerUsageData;
	std::map<std::string, int> appUsage;
	std::mutex dataMutex;



public:
	//constructor
	PowerUsage() {

	}

	//destructor
	~PowerUsage() {

	}

	//initialize with data file
	void initialize(const std::string& filename) {
		loadData(filename);
	}
	//read data from file
	void  loadData(const std::string& filename) {
		std::ifstream file(filename);
		int value;
		while (file >> value) {
			powerData.push_back(value);
		}
	}
	int getPowerUsage() {
		std::lock_guard<std::mutex> lock(dataMutex);
	}

	std::vector <int> getPowerFluctuations() {
		std::lock_guard<std::mutex> lock(dataMutex);
		return powerData;
	}

	void addApplication(const std::string& appName, int initialUsage) {
		std::lock_guard<std::mutex>lock(dataMutex);
		appUsage[appName] = initialUsage;
	}
	void passToHMI() {
		std::lock_guard<std::mutex> lock(dataMutex);
		std::cout << "Passing to HMI/SCADA...\n";
		for (const auto& app : appUsage) {
			std::cout << app.first << ": " << app.second << "W\n";
		}
	}
	void displayTabularView() {
		std::lock_guard<std::mutex> lock(dataMutex);
		std::cout << "\nTabular View of Power Data:\n";
		std::cout << std::setw(10) << "Time" << std::setw(15) << "Usage (W)" << "\n";
		for (size_t i = 0; i < powerData.size(); ++i) {
			std::cout << std::setw(10) << i << std::setw(15) << powerData[i] << "\n";
		}
	}
};