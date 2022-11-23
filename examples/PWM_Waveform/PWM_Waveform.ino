/****************************************************************************************************************************
  PWM_Waveform.ino

  For Arduino AVR ATtiny-based boards (ATtiny3217, etc.) using megaTinyCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/ATtiny_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

#define _PWM_LOGLEVEL_       3

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

typedef struct
{
  uint16_t level;
} PWD_Data;

// Data for 0-100%
PWD_Data PWM_data[] =
{
  {   0 },
  {   5 },
  {  10 },
  {  15 },
  {  20 },
  {  25 },
  {  30 },
  {  35 },
  {  40 },
  {  45 },
  {  50 },
  {  55 },
  {  60 },
  {  65 },
  {  70 },
  {  75 },
  {  80 },
  {  85 },
  {  90 },
  {  95 },
  { 100 },
  {  95 },
  {  90 },
  {  85 },
  {  80 },
  {  75 },
  {  70 },
  {  65 },
  {  60 },
  {  55 },
  {  50 },
  {  45 },
  {  40 },
  {  35 },
  {  30 },
  {  25 },
  {  20 },
  {  15 },
  {  10 },
  {   5 },
  {   0 },
};

#define NUM_PWM_POINTS      ( sizeof(PWM_data) / sizeof(PWD_Data) )

float frequency = 2000.0f;
float dutyCycle = 0.0f;

uint8_t channel = 0;

// You can select any value
PWD_Data PWM_data_idle = PWM_data[0];

char dashLine[] = "============================================================================================";

void printPWMInfo(ATtiny_PWM* PWM_Instance)
{
  Serial.println(dashLine);
  Serial.print("Actual data: pin = ");
  Serial.print(PWM_Instance->getPin());
  Serial.print(", PWM DutyCycle = ");
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

  Serial.print(F("\nStarting PWM_Waveform on "));
  Serial.println(BOARD_NAME);
  Serial.println(AT_TINY_PWM_VERSION);

  // Create a dummy instance
  PWM_Instance = new ATtiny_PWM(pinToUse, frequency, dutyCycle);

  if ( (PWM_Instance) && PWM_Instance->isPWMEnabled() )
  {
    // setPWM_manual(uint8_t pin, uint16_t level)
    PWM_Instance->setPWM(pinToUse, frequency, 0);

    printPWMInfo(PWM_Instance);
  }
  else
  {
    Serial.print(F("Stop here forever"));

    while (true)
      delay(10000);
  }
}

void updateDC()
{
  static uint16_t index = 0;

  // Mapping data to any other frequency from original data 0-100 to actual 16-bit Dutycycle
  PWM_Instance->setPWM_manual(pinToUse, ( (uint32_t) PWM_data[index].level * MAX_16BIT ) / 100 );

  // Use at low freq to check
  //printPWMInfo(PWM_Instance);

  index = (index + 1) % NUM_PWM_POINTS;
}

void check_status()
{
#define UPDATE_INTERVAL     100L

  static unsigned long update_timeout = UPDATE_INTERVAL;

  // Update DC every UPDATE_INTERVAL (100) milliseconds
  if (millis() > update_timeout)
  {
    updateDC();
    update_timeout = millis() + UPDATE_INTERVAL;
  }
}

void loop()
{
  check_status();
}
