#include "FanSpeedMonitor.h"

FanSpeedMonitor::FanSpeedMonitor()
{
	readFromFile(FAN_FILE);
	setRPM(0);
}

int FanSpeedMonitor::getRPM()
{
	return speedRPM;
}

bool FanSpeedMonitor::setRPM(int rpm)
{
	if (rpm < 0 || rpm > MAX_FAN_RPM) {
		//rpm is out of range
		return false;
	}
	speedRPM = rpm;
	return true;
}

int FanSpeedMonitor::getFluctuatingRPM()
{
	return speedRPM + getFlux();
}
