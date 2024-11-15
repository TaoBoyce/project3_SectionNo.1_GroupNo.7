#pragma once
// CPUMonitor.h

#ifndef CPUMONITOR_H
#define CPUMONITOR_H

#include "Monitor.h"
#include <string>
#include <vector>

class CPUMonitor : public Monitor<float> {
private:
	float cpuClockSpeed;  // Clock speed in GHz or MHz, depending on your use case

public:
	// Constructor
	CPUMonitor();

	// Setters and getters for CPU clock speed
	void setCPUClockSpeed(float speed);
	float getCPUClockSpeed() const;

	// Method to load CPU usage data from a file
	std::vector<float> loadCPUData(const std::string& filename);

	// Getter for the data vector (read-only access to CPU usage data)
	std::vector<float> getCPUData() const;

	// Getter for the last recorded CPU usage (latest flux)
	float getLatestCPUUsage() const;

	// Method to calculate average CPU usage
	float getAverageUsage() const;


};

#endif // CPUMONITOR_H

