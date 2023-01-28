/****************************************************************************************************************************
  PWM_SpeedTest.ino
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

// Using setPWM_DCPercentage_manual if true
//#define USING_DC_PERCENT      false
#define USING_DC_PERCENT      true

#if USING_DC_PERCENT
  float    dutycyclePercent = 0.0f;
  float    DCStepPercent    = 5.0f;

  // dutycyclePercentInt = dutycyclePercent * 65535 / 100
  uint16_t    dutycyclePercentInt = 0;
#else
  uint16_t dutycycle = 0;
  uint16_t DCStep;
#endif

uint16_t PWMPeriod;

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

  Serial.print(F("\nStarting PWM_SpeedTest on "));
  Serial.println(BOARD_NAME);
  Serial.println(AT_TINY_PWM_VERSION);

  // Create a dummy instance
  PWM_Instance = new ATtiny_PWM(pinToUse, frequency, 0);

  if ( (PWM_Instance) && PWM_Instance->isPWMEnabled() )
  {
    // setPWM_manual(uint8_t pin, uint16_t level)
    PWM_Instance->setPWM(pinToUse, frequency, 0);

#if USING_DC_PERCENT
    dutycyclePercent = 50.0f;
    
    // dutycyclePercentInt = dutycyclePercent * 65535 / 100
    dutycyclePercentInt = MAX_16BIT / 2;
#else
    // 5% steps
    DCStep = round( MAX_16BIT / 20.0f);
    
    // 50%
    dutycycle = MAX_16BIT / 2;
#endif

    printPWMInfo(PWM_Instance);
  }
 
  Serial.print(F("Average time of setPWM function"));

#if USING_DC_PERCENT  
  Serial.println(F(" USING_DC_PERCENT"));
#else
  Serial.println(F(" not USING_DC_PERCENT"));
#endif
}

void loop()
{
  static unsigned long update_timeout = UPDATE_INTERVAL + millis();
  static uint32_t count = 0;

#if USING_DC_PERCENT
    // v1.2.0: 129500ns. Previous v1.1.0 : 169577ns
    //PWM_Instance->setPWM_DCPercentage_manual(pinToUse, dutycyclePercent);

    // dutycyclePercent = 0-65535 == 0-100%
    // Faster, 94197ns
    PWM_Instance->setPWM_DCPercentageInt_manual(pinToUse, dutycyclePercentInt);
#else
    // 97465ns
    PWM_Instance->setPWM_manual(pinToUse, dutycycle);   
#endif

  count++;

  // Update DC every UPDATE_INTERVAL (1000) milliseconds
  if (millis() > update_timeout)
  {
    Serial.print(F("count="));
    Serial.print( count);
    Serial.print(F(", ns="));
    Serial.println( (uint32_t) (UPDATE_INTERVAL * 1000000 / count));

    count = 0;
    update_timeout = millis() + UPDATE_INTERVAL;
  }
}
