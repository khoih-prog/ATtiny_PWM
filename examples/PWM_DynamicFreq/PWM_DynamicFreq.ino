/****************************************************************************************************************************
  PWM_DynamicFreq.ino

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
// PIN_PC0-1: TCD0 => not OK yet for frequency
// Not OK, PIN_PA6, 7, PIN_PB0-2:TCA0

#define pinToUse       PIN_PA5    //PIN_PB4

//creates pwm instance
ATtiny_PWM* PWM_Instance;

float frequency;

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

  Serial.print(F("\nStarting PWM_DynamicFreq on "));
  Serial.println(BOARD_NAME);
  Serial.println(AT_TINY_PWM_VERSION);

  frequency = 10000.0f;

  PWM_Instance = new ATtiny_PWM(pinToUse, frequency, 50.0f);

  if ( (!PWM_Instance) || !PWM_Instance->isPWMEnabled())
  {
    Serial.print(F("Stop here forever"));

    while (true)
      delay(10000);
  }

  Serial.println(dashLine);
}

void loop()
{
  delay(5000);

  frequency = 20000.0f;

  Serial.print(F("Change PWM Freq to "));
  Serial.println(frequency);
  PWM_Instance->setPWM(pinToUse, frequency, 50.0f);
  printPWMInfo(PWM_Instance);

  delay(5000);

  frequency = 10000.0f;

  Serial.print(F("Change PWM Freq to "));
  Serial.println(frequency);
  PWM_Instance->setPWM(pinToUse, frequency, 50.0f);
  printPWMInfo(PWM_Instance);
}
