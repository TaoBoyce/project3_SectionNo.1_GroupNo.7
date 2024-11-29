#include "FanSpeedMonitor.h"
#include <string.h>
#include <iostream>

class Test {
public:
	virtual std::string getTestName() = 0;
	virtual void doTest() = 0;
	void announceResult(bool success) {
		std::cout << "Test " << getTestName();
		if (success) {
			std::cout << ": Success" << std::endl;
		}
		else {
			std::cout << ": FAIL FAIL FAIL FAIL FAIL" << std::endl;
		}
	}
};

class TEST_001_FanConstructor_REQ_002 :Test {
	std::string getTestName() override {
		return "TEST_001_FanConstructor_REQ_002";
	}
public:
	void doTest() override {
		//Arrange
		FanSpeedMonitor monitor = FanSpeedMonitor();
		int expected = 0;
		int actual = 0;

		//Act
		actual = monitor.getRPM();

		//Assert
		bool success;
		if (expected == actual) {
			success = true;
		}
		else {
			success = false;
		}
		announceResult(success);
	}
};

class TEST_002_SetFanSpeed_True_REQ_004:Test {
	std::string getTestName() override {
		return "TEST_002_SetFanSpeed_True_REQ_004";
	}
public:
	void doTest() override {
		//Arrange
		FanSpeedMonitor monitor = FanSpeedMonitor();
		int expected = 1000;
		int actual = 0;

		//Act
		monitor.setRPM(1000);
		actual = monitor.getRPM();

		//Assert
		bool success;
		if (expected == actual) {
			success = true;
		}
		else {
			success = false;
		}
		announceResult(success);
	}
};

class TEST_003_SetFanSpeed_False1_REQ_005:Test {
	std::string getTestName() override {
		return "TEST_003_SetFanSpeed_False1_REQ_005";
	}
public:
	void doTest() override {
		//Arrange
		FanSpeedMonitor monitor = FanSpeedMonitor();
		int expected = 0;
		int actual = 0;

		//Act
		monitor.setRPM(-200);
		actual = monitor.getRPM();

		//Assert
		bool success;
		if (expected == actual) {
			success = true;
		}
		else {
			success = false;
		}
		announceResult(success);
	}
};

class TEST_004_SetFanSpeed_False2_REQ_005:Test {
	std::string getTestName() override {
		return "TEST_004_SetFanSpeed_False2_REQ_005";
	}
public:
	void doTest() override {
		//Arrange
		FanSpeedMonitor monitor = FanSpeedMonitor();
		int expected = 0;
		int actual = 0;

		//Act
		monitor.setRPM(5000);
		actual = monitor.getRPM();

		//Assert
		bool success;
		if (expected == actual) {
			success = true;
		}
		else {
			success = false;
		}
		announceResult(success);
	}
};

class TEST_110_GetFluctuatingFanSpeed :Test {
	std::string getTestName() override {
		return "TEST_110_GetFluctuatingFanSpeed";
	}
public:
	void doTest() override {
		//Arrange
		FanSpeedMonitor monitor = FanSpeedMonitor("test_success.txt");
		int expected1 = 1001;
		int expected2 = 1002;
		int expected3 = 1003;
		int actual = 0;

		//Act
		monitor.setRPM(1000);
		actual = monitor.getFluctuatingRPM();

		//Assert
		bool success;
		switch (actual) {
		case 1001:
		case 1002:
			//purposeful fallthrough
		case 1003:
			success = true;
			break;
		default:
			success = false;
			break;
		}
		announceResult(success);
	}
};


int main() {
	TEST_001_FanConstructor_REQ_002 test1 = TEST_001_FanConstructor_REQ_002();
	TEST_002_SetFanSpeed_True_REQ_004 test2 = TEST_002_SetFanSpeed_True_REQ_004();
	TEST_003_SetFanSpeed_False1_REQ_005 test3 = TEST_003_SetFanSpeed_False1_REQ_005();
	TEST_004_SetFanSpeed_False2_REQ_005 test4 = TEST_004_SetFanSpeed_False2_REQ_005();
	TEST_110_GetFluctuatingFanSpeed test5 = TEST_110_GetFluctuatingFanSpeed();

	test1.doTest();
	test2.doTest();
	test3.doTest();
	test4.doTest();
	test5.doTest();
}