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

#include "LedDriver.h"
#include "RuntimeError.h"

static uint16_t * ledsAddress;
static uint16_t ledsImage; 

enum { 
  ALL_LEDS_ON = ~0, 
  ALL_LEDS_OFF = 0
};

///
/// Initialize Led Driver with the hardware address
/// @param address the hardware address for the LEDs
///
void LedDriver_Create(uint16_t * address) 
{
  ledsAddress = address;
  ledsImage = ALL_LEDS_OFF;
  *ledsAddress = ledsImage; 
}

///
/// Destroy the driver
///
void LedDriver_Destroy(void) { }


enum { 
  FIRST_LED = 1, 
  LAST_LED = 16 
};

///
/// Test if an LED number is out of bounds
/// @param ledNumber the number to test for
/// @return TRUE if out of bounds
static BOOL IsLedOutOfBounds(int ledNumber)
{
  if ((ledNumber < FIRST_LED) || (ledNumber > LAST_LED))
  {
    RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
    return TRUE;
  }
  return FALSE;
}

///
/// Write to the LED memory
///
static void updateHardware(void)
{
  *ledsAddress = ledsImage;
}

///
/// Helper function to convert led number to bit
static uint16_t convertLedNumberToBit(int number) 
{
  return 1 << (number - 1);
}

/// 
/// Toggles the bit of the led number on
/// @param the led number to toggle
static void setLedImageBit(int ledNumber)
{
  ledsImage |= convertLedNumberToBit(ledNumber);
}

/// 
/// Toggles the bit of the led number off
/// @param the led number to toggle
static void clearLedImageBit(int ledNumber)
{
  ledsImage &= ~convertLedNumberToBit(ledNumber);
}

///
/// Turn an individual LED on
/// @param ledNumber the LED number
///
void LedDriver_TurnOn(int ledNumber)
{
  if (IsLedOutOfBounds(ledNumber)) 
    return;

  setLedImageBit(ledNumber);
  updateHardware();
}

///
/// Turn an individual LED off
/// @param ledNumber the LED number
void LedDriver_TurnOff(int ledNumber) 
{
  if (IsLedOutOfBounds(ledNumber))
    return;

  clearLedImageBit(ledNumber);
  updateHardware();
}

///
/// Turn all the LEDs on
void LedDriver_TurnAllOn(void)
{
  ledsImage = ALL_LEDS_ON;
  updateHardware();
}

///
/// Turn all the LEDs off
void LedDriver_TurnAllOff(void) 
{
  ledsImage = ALL_LEDS_OFF;
  updateHardware();
}

/// 
/// Returns true if the LED for ledNumber is on
BOOL LedDriver_IsOn(int ledNumber) 
{
  if (IsLedOutOfBounds(ledNumber))
    return FALSE;
  return 0 != (ledsImage & convertLedNumberToBit(ledNumber));
}

//
// Returns true if the LED for ledNumber is off
BOOL LedDriver_IsOff(int ledNumber)
{
  return !LedDriver_IsOn(ledNumber);
}
