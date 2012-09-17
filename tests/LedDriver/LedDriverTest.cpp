/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/

#include "CppUTest/TestHarness.h"

extern "C"
{
  #include "LedDriver.h"
  #include "RuntimeErrorStub.h"
}

TEST_GROUP(LedDriver)
{

  uint16_t virtualLeds;
 
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

TEST(LedDriver, LedsAreOffAfterCreate)
{
  virtualLeds = 0xffff;
  LedDriver_Create(&virtualLeds);
  LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
  LedDriver_TurnOn(1);
  LONGS_EQUAL(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
  LedDriver_TurnOn(1);
  LedDriver_TurnOff(1);
  LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds)
{
  LedDriver_TurnOn(9);
  LedDriver_TurnOn(8);
  LONGS_EQUAL(0x180, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(8);
  LONGS_EQUAL(0xff7f, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable)
{
  virtualLeds = 0xffff;
  LedDriver_TurnOn(8);
  LONGS_EQUAL(0x80, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds)
{
  LedDriver_TurnOn(1);
  LedDriver_TurnOn(16);
  LONGS_EQUAL(0x8001, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm)
{
  LedDriver_TurnOn(-1);
  LedDriver_TurnOn(0);
  LedDriver_TurnOn(17);
  LedDriver_TurnOn(3141);
  LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
  LedDriver_TurnAllOn();

  LedDriver_TurnOff(-1);
  LedDriver_TurnOff(0);
  LedDriver_TurnOff(17);
  LedDriver_TurnOff(3141);
  LONGS_EQUAL(0xffff, virtualLeds);
}

IGNORE_TEST(LedDriver, OutOfBoundsToDo)
{
  // demo shows how to IGNORE a test
}

TEST(LedDriver, OutOfBoundsProducesRuntimeError)
{
  LedDriver_TurnOn(-1);
  STRCMP_EQUAL("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
}

TEST(LedDriver, IsOn)
{
  CHECK_EQUAL(FALSE, LedDriver_IsOn(1));
  LedDriver_TurnOn(1);
  CHECK_EQUAL(TRUE, LedDriver_IsOn(1)); 
}

TEST(LedDriver, IsOff)
{
  CHECK_EQUAL(TRUE, LedDriver_IsOff(12));
  LedDriver_TurnOn(12);
  CHECK_EQUAL(FALSE, LedDriver_IsOff(12));
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff) 
{
  CHECK_EQUAL(TRUE, LedDriver_IsOff(0));
  CHECK_EQUAL(TRUE, LedDriver_IsOff(17));
  CHECK_EQUAL(FALSE, LedDriver_IsOn(0));
  CHECK_EQUAL(FALSE, LedDriver_IsOn(17));
}

TEST(LedDriver, AllOn)
{
  LedDriver_TurnAllOn();
  LONGS_EQUAL(0xffff, virtualLeds);
}

TEST(LedDriver, AllOff)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnAllOff();
  LONGS_EQUAL(0, virtualLeds);
}

