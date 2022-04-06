#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab12_3.3\main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int day = 13;
			int month = 10;
			Assert::AreEqual((int)ZodiacSigns::Balance, (int)getSign(day, month));
		}
	};
}
