#include "pch.h"
#include "CppUnitTest.h"

#include "../Sec1Group7_Project/Monitor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestsExample
{
	TEST_CLASS(TestsExample)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Monitor<int> m = Monitor<int>();
		}
	};
}
