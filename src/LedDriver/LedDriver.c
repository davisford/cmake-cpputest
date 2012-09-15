#include "LedDriver.h"
#include "RuntimeError.h"
#include <stdbool.h>

static uint16_t * ledsAddress;
static uint16_t ledsImage; 

enum { ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON };

///
/// Initialize Led Driver with the hardware address
/// @param address the hardware address for the LEDs
void LedDriver_Create(uint16_t * address) 
{
  ledsAddress = address;
  ledsImage = ALL_LEDS_OFF;
  *ledsAddress = ledsImage; 
}

///
/// Destroy the driver
void LedDriver_Destroy(void) 
{

}

static uint16_t convertLedNumberToBit(int number) 
{
  return 1 << (number - 1);
}

enum { FIRST_LED = 1, LAST_LED = 16 };

static bool IsLedOutOfBounds(int ledNumber)
{
  if ((ledNumber < FIRST_LED) || (ledNumber > LAST_LED))
  {
    //RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
    return true;
  }
  return false;
}

static void updateHardware(void)
{
  *ledsAddress = ledsImage;
}

///
/// Turn an individual LED on
/// @param ledNumber the LED number
void LedDriver_TurnOn(int ledNumber)
{
  if (IsLedOutOfBounds(ledNumber))
    return;

  ledsImage |= convertLedNumberToBit(ledNumber);
  updateHardware();
}

///
/// Turn an individual LED off
/// @param ledNumber the LED number
void LedDriver_TurnOff(int ledNumber) 
{
  if (IsLedOutOfBounds(ledNumber))
    return;

  ledsImage &= ~(convertLedNumberToBit(ledNumber));
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
    return false;
  return ledsImage & (convertLedNumberToBit(ledNumber));
}

//
// Returns true if the LED for ledNumber is off
BOOL LedDriver_IsOff(int ledNumber)
{
  if (IsLedOutOfBounds(ledNumber))
    return false;
  return ledsImage | (convertLedNumberToBit(ledNumber));
}