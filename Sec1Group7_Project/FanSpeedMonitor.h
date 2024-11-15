#pragma once
#include "Monitor.h"
#define MAX_FAN_RPM 2000
#define FAN_FILE "FanSpeedData.txt"

class FanSpeedMonitor:Monitor<int> {
private:
	int speedRPM;
public:
	FanSpeedMonitor();
	FanSpeedMonitor(std::string filename);
	int getRPM();
	bool setRPM(int rpm);
	int getFluctuatingRPM();
};