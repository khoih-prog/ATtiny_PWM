/****************************************************************************************************************************
  PWM_manual.ino
  For Arduino AVR ATtiny-based boards (ATtiny3217, etc.) using megaTinyCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/ATtiny_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

#define _PWM_LOGLEVEL_       1

// Select false to use PWM
#define USING_TIMER       false   //true

#include "ATtiny_PWM.h"

#define UPDATE_INTERVAL       1000L

// Using setPWM_DCPercentage_manual if true
#define USING_DC_PERCENT      true

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

// Min freq. is 1220Hz = F_CPU / (256 * 64) for TCA0
float    frequency = 2000.0f;
//float    frequency = 10000.0f;

#if USING_DC_PERCENT
  float    dutycyclePercent = 0.0f;
  float    DCStepPercent    = 5.0f;
#else
  uint16_t dutycycle = 0;
  uint16_t DCStep;
#endif

char dashLine[] = "=================================================================================================";

void printPWMInfo(ATtiny_PWM* PWM_Instance)
{
  Serial.println(dashLine);
  Serial.print("Actual data: pin = ");
  Serial.print(PWM_Instance->getPin());
  Serial.print(", PWM DutyCycle % = ");
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

  delay(100);

  Serial.print(F("\nStarting PWM_manual on "));
  Serial.println(BOARD_NAME);
  Serial.println(AT_TINY_PWM_VERSION);

  // Create a dummy instance
  PWM_Instance = new ATtiny_PWM(pinToUse, frequency, 0);

  if ( (PWM_Instance) && PWM_Instance->isPWMEnabled() )
  {
    // setPWM_manual(uint8_t pin, uint16_t level)
    PWM_Instance->setPWM(pinToUse, frequency, 0);

    //printPWMInfo(PWM_Instance);
  }
  else
  {
    Serial.print(F("Stop here forever"));

    while (true)
      delay(10000);
  }

#if !USING_DC_PERCENT    
  // 5% steps
  DCStep = round(MAX_16BIT / 20.0f);
#endif
}

void loop()
{
  static unsigned long update_timeout = UPDATE_INTERVAL;

  // Update DC every UPDATE_INTERVAL (1000) milliseconds
  if (millis() > update_timeout)
  {
#if USING_DC_PERCENT
    PWM_Instance->setPWM_DCPercentage_manual(pinToUse, dutycyclePercent);

    dutycyclePercent += DCStepPercent;

    if (dutycyclePercent > 100.0f)
      dutycyclePercent = 0.0f;
#else
    if (dutycycle > MAX_16BIT)
    {
      PWM_Instance->setPWM_manual(pinToUse, MAX_16BIT);
      dutycycle = 0;
    }
    else
    {
      PWM_Instance->setPWM_manual(pinToUse, dutycycle);
      dutycycle += DCStep;
    }
#endif

    printPWMInfo(PWM_Instance);
    
    update_timeout = millis() + UPDATE_INTERVAL;
  }
}
