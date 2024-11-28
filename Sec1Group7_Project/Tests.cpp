#include "Monitor.h"
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

class TEST_101_MonitorConstructor_REQ_101:Test {
	std::string getTestName() override {
		return "TEST_101_MonitorConstructor_REQ_101";
	}
public:
	void doTest() override {
		//Arrange
		Monitor<int> monitor = Monitor<int>();
		int expected = 0;
		int actual = 0;

		//Act
		actual = monitor.getFlux();

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

class TEST_102_ReadFromFile_Success_REQ_102:Test {
	std::string getTestName() override {
		return "TEST_102_ReadFromFile_Success_REQ_102";
	}
public:
	void doTest() override {

		//Arrange
		Monitor<int> monitor = Monitor<int>();
		std::vector<int> expected = { 1,2,3 };
		std::vector<int> actual;

		//Act
		actual = monitor.readFromFile("test_success.txt");

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

class TEST_103_ReadFromFile_NoFile_REQ_104:Test {
	std::string getTestName() override {
		return "TEST_103_ReadFromFile_NoFile_REQ_104";
	}
public:
	void doTest() override {

		//Arrange
		Monitor<int> monitor = Monitor<int>();
		std::vector<int> expected;
		std::vector<int> actual;

		//Act
		actual = monitor.readFromFile("test_nofile.txt");

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

class TEST_104_ReadFromFile_EmptyFile_REQ_104:Test {
	std::string getTestName() override {
		return "TEST_104_ReadFromFile_EmptyFile_REQ_104";
	}
public:
	void doTest() override {

		//Arrange
		Monitor<int> monitor = Monitor<int>();
        std::vector<int> expected;
		std::vector<int> actual;

		//Act
		actual = monitor.readFromFile("test_empty.txt");

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

class TEST_105_ReadFromFile_NoParse_REQ_104:Test {
	std::string getTestName() override {
		return "TEST_105_ReadFromFile_NoParse_REQ_104";
	}
public:
	void doTest() override {

		//Arrange
		Monitor<int> monitor = Monitor<int>();
		std::vector<int> expected;
		std::vector<int> actual;

		//Act
		actual = monitor.readFromFile("test_noparse.txt");

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

class TEST_106_ParseData_Success_REQ_105:Test {
	std::string getTestName() override {
		return "";
	}
public:
	void doTest() override {

		//Arrange
		Monitor<int> monitor = Monitor<int>();
		int expected = 123;
		int actual;

		//Act
		actual = monitor.parseData("123");

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

class TEST_107_ParseData_Fail_REQ_105:Test {
	std::string getTestName() override {
		return "TEST_107_ParseData_Fail_REQ_105";
	}
public:
	void doTest() override {

		//Arrange
		Monitor<int> monitor = Monitor<int>();
		int expected = 0;
		int actual;

		//Act
		try {
			actual = monitor.parseData("notNumbers");
		}
		catch(std::exception e){
			actual = 0;
		}

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

class TEST_108_GetFlux_Success_REQ_107:Test {
	std::string getTestName() override {
		return "TEST_108_GetFlux_Success_REQ_107";
	}
public:
	void doTest() override {

		//Arrange
		Monitor<int> monitor = Monitor<int>();
		int expected1 = 1;
		int expected2 = 2;
		int expected3 = 3;
		int actual;

		//Act
		monitor.readFromFile("test_success.txt");
		actual = monitor.getFlux();

		//Assert
		bool success;
		switch (actual) {
		case 1:
		case 2:
			//purposeful fallthrough
		case 3:
			success = true;
			break;
		default:
			success = false;
			break;
		}
		announceResult(success);
	}
};

class TEST_109_GetFlux_Empty_REQ_107:Test {
	std::string getTestName() override {
		return "TEST_109_GetFlux_Empty_REQ_107 ";
	}
public:
	void doTest() override {

		//Arrange
		Monitor<int> monitor = Monitor<int>();
		int expected = 0;
		int actual = 0;

		//Act
		actual = monitor.getFlux();

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


int main() {
	TEST_101_MonitorConstructor_REQ_101 test1 = TEST_101_MonitorConstructor_REQ_101();
	TEST_102_ReadFromFile_Success_REQ_102 test2 = TEST_102_ReadFromFile_Success_REQ_102();
	TEST_103_ReadFromFile_NoFile_REQ_104 test3 = TEST_103_ReadFromFile_NoFile_REQ_104();
	TEST_104_ReadFromFile_EmptyFile_REQ_104 test4 = TEST_104_ReadFromFile_EmptyFile_REQ_104();
	TEST_105_ReadFromFile_NoParse_REQ_104 test5 = TEST_105_ReadFromFile_NoParse_REQ_104();
	TEST_106_ParseData_Success_REQ_105 test6 = TEST_106_ParseData_Success_REQ_105();
	TEST_107_ParseData_Fail_REQ_105 test7 = TEST_107_ParseData_Fail_REQ_105();
	TEST_108_GetFlux_Success_REQ_107 test8 = TEST_108_GetFlux_Success_REQ_107();
	TEST_109_GetFlux_Empty_REQ_107 test9 = TEST_109_GetFlux_Empty_REQ_107();

	test1.doTest();
	test2.doTest();
	test3.doTest();
	test4.doTest();
	test5.doTest();
	test6.doTest();
	test7.doTest();
	test8.doTest();
	test9.doTest();

}