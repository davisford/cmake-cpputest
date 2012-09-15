#include "CppUTest/TestHarness.h"

extern "C"
{
  #include "LedDriver.h"
}

static uint16_t virtualLeds;

TEST_GROUP(LedDriver)
{
  void setup()
  {
    virtualLeds = 0;
    LedDriver_Create(&virtualLeds);
  }

  void teardown() 
  {
    LedDriver_Destroy();
  }
};

TEST(LedDriver, FirstTest)
{
  FAIL("Start here");
}