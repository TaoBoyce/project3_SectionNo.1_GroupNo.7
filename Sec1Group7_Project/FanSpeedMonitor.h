#pragma once
#include "Monitor.h"

class FanSpeedMonitor :Monitor<int> {
private:
	int speedRPM;
public:
	FanSpeedMonitor();
	int getRPM();
	bool setRPM(int rpm);
	int getFluctuatingRPM();
};