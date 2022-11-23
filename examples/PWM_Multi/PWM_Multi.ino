/****************************************************************************************************************************
  PWM_Multi.ino

  For Arduino AVR ATtiny-based boards (ATtiny3217, etc.) using megaTinyCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/ATtiny_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

#define _PWM_LOGLEVEL_       4

// Select false to use PWM
#define USING_TIMER       false   //true

#include "ATtiny_PWM.h"

/*
  const uint8_t digital_pin_to_timer[] = {
  // Left side, top to bottom
  TIMERA0,         // 0  PA4 WO4 WOA
  TIMERA0,         // 1  PA5 WO5 WOB
  #if defined(DAC0)
  DACOUT,           // 2  PA6
  #else
  NOT_ON_TIMER,     // 2  PA6
  #endif
  NOT_ON_TIMER,     // 3  PA7
  NOT_ON_TIMER,     // 4  PB7
  NOT_ON_TIMER,     // 5  PB6
  NOT_ON_TIMER,     // 6  PB5 WO2 Alt
  NOT_ON_TIMER,     // 7  PB4 WO1 Alt
  NOT_ON_TIMER,     // 8  PB3 WO0 Alt
  TIMERA0,          // 9  PB2 WO2
  TIMERA0,          // 10 PB1 WO1
  // Right side, bottom to top
  TIMERA0,          // 11 PB0 WO0
  #if (defined(TCD0) && defined(USE_TIMERD0_PWM))
  TIMERD0,          // 12 PC0 WOC
  TIMERD0,          // 13 PC1 WOD
  #else
  NOT_ON_TIMER,     // 12 PC0
  NOT_ON_TIMER,     // 13 PC1
  #endif
  NOT_ON_TIMER,     // 14 PC2
  NOT_ON_TIMER,     // 15 PC3 WO3 Alt
  NOT_ON_TIMER,     // 16 PC4 WO4 Alt
  NOT_ON_TIMER,     // 17 PC5 WO5 Alt
  NOT_ON_TIMER,     // 18 PA1
  NOT_ON_TIMER,     // 19 PA2
  TIMERA0,          // 20 PA3 WO3
  NOT_ON_TIMER      // 21 PA0
  };
*/

// OK, only PIN_PA4-5:TCA0
// PIN_PC0-1: TCD0 => not OK yet for frequency. Fixed @ preprogrammed 1.2KHz
// Not OK, PIN_PA6, 7, PIN_PB0-2:TCA0

// To select correct pins for different frequencies
uint32_t PWM_Pins[] = { PIN_PA4, PIN_PC0 };
float frequency[]   = { 2000.0f, 8000.0f };
float dutyCycle[]   = { 30.0f, 90.0f };

#define NUM_OF_PINS   ( sizeof(PWM_Pins) / sizeof(uint32_t) )

ATtiny_PWM* PWM_Instance[NUM_OF_PINS];

char dashLine[] = "=====================================================================================";

void printPWMInfo(ATtiny_PWM* PWM_Instance)
{
  Serial.println(dashLine);
  Serial.print("Actual data: pin = ");
  Serial.print(PWM_Instance->getPin());
  Serial.print(", PWM DC = ");
  Serial.print(PWM_Instance->getActualDutyCycle());
  Serial.print(", PWMPeriod = ");
  Serial.print(PWM_Instance->getPWMPeriod());
  Serial.print(", PWM Freq (Hz) = ");
  Serial.println(PWM_Instance->getActualFreq(), 4);
  Serial.println(dashLine);
}

void setup()
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(500);

  Serial.print(F("\nStarting PWM_Multi on "));
  Serial.println(BOARD_NAME);
  Serial.println(AT_TINY_PWM_VERSION);

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    PWM_Instance[index] = new ATtiny_PWM(PWM_Pins[index], frequency[index], dutyCycle[index]);

    if (PWM_Instance[index])
    {
      PWM_Instance[index]->setPWM();
    }
  }

  Serial.println(dashLine);
  Serial.println("Index\tPin\tPWM_freq\tDutyCycle\tActual Freq");
  Serial.println(dashLine);

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    if (PWM_Instance[index])
    {
      Serial.print(index);
      Serial.print("\t");
      Serial.print(PWM_Pins[index]);
      Serial.print("\t");
      Serial.print(frequency[index]);
      Serial.print("\t\t");
      Serial.print(dutyCycle[index]);
      Serial.print("\t\t");
      Serial.println(PWM_Instance[index]->getActualFreq(), 4);
    }
    else
    {
      Serial.println();
    }
  }

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    printPWMInfo(PWM_Instance[index]);
  }
}

void loop()
{
  //Long delay has no effect on the operation of hardware-based PWM channels
  delay(1000000);
}
