#pragma once
// TempMonitor.h

#ifndef TEMPMONITOR_H
#define TEMPMONITOR_H

#include "Monitor.h"
#include <string>
#include <vector>

class TempMonitor : public Monitor<float> {
private:
	float maxTemperatureThreshold;  // Maximum allowable temperature

public:
	// Constructor
	TempMonitor();

	// Setters and getters for max temperature threshold
	void setMaxTemperatureThreshold(float threshold);
	float getMaxTemperatureThreshold() const;

	// Method to load temperature data from a file
	std::vector<float> loadTemperatureData(const std::string& filename);

	// Getter for the data vector (read-only access to temperature data)
	std::vector<float> getTemperatureData() const;

	// Getter for the latest recorded temperature
	float getLatestTemperature() const;

	// Method to calculate average temperature
	float getAverageTemperature() const;

	//if we want to have a max temp thersh hold
	// Check if the latest temperature exceeds the threshold
   // bool isTemperatureExceedingThreshold() const;
};

#endif // TEMPMONITOR_H
