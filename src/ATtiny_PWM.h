/****************************************************************************************************************************
  ATtiny_PWM.h

  For Arduino AVR ATtiny-based boards (ATtiny3217, etc.) using megaTinyCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/ATtiny_PWM
  Licensed under MIT license

  Version: 1.2.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      08/11/2022 Initial coding for AVR ATtiny (ATtiny3217, etc.) using megaTinyCore
  1.0.1   K Hoang      22/01/2023 Add `PWM_StepperControl` example
  1.1.0   K Hoang      25/01/2023 Add `PWM_manual` example and function. Catch low frequency error
  1.2.0   K Hoang      27/01/2023 Add `PWM_SpeedTest` example and faster `setPWM_DCPercentageInt_manual` function
*****************************************************************************************************************************/

#pragma once

#ifndef AT_TINY_PWM_H
#define AT_TINY_PWM_H

#if defined(MEGATINYCORE)

  #define TIMER_INTERRUPT_USING_MEGATINYCORE        true

  #if !defined(BOARD_NAME)

    ////////////////////////// Curiosity Nano //////////////////////////

    #if ( defined(ARDUINO_AVR_CuriosityNano3217) )
      #define BOARD_NAME      F("AVR_CuriosityNano3217" )
    #elif ( defined(ARDUINO_AVR_CuriosityNano1627) )
      #define BOARD_NAME      F("AVR_CuriosityNano1627")
    #elif ( defined(ARDUINO_AVR_CuriosityNano1607) )
      #define BOARD_NAME      F("AVR_CuriosityNano1607")
    #elif ( defined(ARDUINO_AVR_Xplained_Pro_3217) )
      #define BOARD_NAME      F("AVR_Xplained_Pro_3217")
    #elif ( defined(ARDUINO_AVR_Xplained_Pro_817) )
      #define BOARD_NAME      F("AVR_Xplained_Pro_817" )
    #elif ( defined(ARDUINO_AVR_XplainedMini817) )
      #define BOARD_NAME      F("AVR_XplainedMini817")
    #elif ( defined(ARDUINO_AVR_XplainedNano416) )
      #define BOARD_NAME      F("AVR_XplainedNano416")

      ////////////////////////// tinyAVR 0/1 series (atxy7) //////////////////////////

    #elif ( defined(ARDUINO_AVR_ATtiny3217) )
      #define BOARD_NAME      F("AVR_ATtiny3217" )
    #elif ( defined(ARDUINO_AVR_ATtiny1617) )
      #define BOARD_NAME      F("AVR_ATtiny1617")
    #elif ( defined(ARDUINO_AVR_ATtiny817) )
      #define BOARD_NAME      F("AVR_ATtiny817")
    #elif ( defined(ARDUINO_AVR_ATtiny417) )
      #define BOARD_NAME      F("AVR_ATtiny417")
    #elif ( defined(ARDUINO_AVR_ATtiny3227) )
      #define BOARD_NAME      F("AVR_ATtiny3227" )
    #elif ( defined(ARDUINO_AVR_ATtiny1627) )
      #define BOARD_NAME      F("AVR_ATtiny1627")
    #elif ( defined(ARDUINO_AVR_ATtiny827) )
      #define BOARD_NAME      F("AVR_ATtiny827")
    #elif ( defined(ARDUINO_AVR_ATtiny427) )
      #define BOARD_NAME      F("AVR_ATtiny427")
    #elif ( defined(ARDUINO_AVR_ATtiny1607) )
      #define BOARD_NAME      F("AVR_ATtiny1607")
    #elif ( defined(ARDUINO_AVR_ATtiny807) )
      #define BOARD_NAME      F("AVR_ATtiny807")

      ////////////////////////// tinyAVR 0/1 series (atxy6) //////////////////////////

    #elif ( defined(ARDUINO_AVR_ATtiny3216) )
      #define BOARD_NAME      F("AVR_ATtiny3216" )
    #elif ( defined(ARDUINO_AVR_ATtiny1616) )
      #define BOARD_NAME      F("AVR_ATtiny1616")
    #elif ( defined(ARDUINO_AVR_ATtiny816) )
      #define BOARD_NAME      F("AVR_ATtiny816")
    #elif ( defined(ARDUINO_AVR_ATtiny416) )
      #define BOARD_NAME      F("AVR_ATtiny416")
    #elif ( defined(ARDUINO_AVR_ATtiny3226) )
      #define BOARD_NAME      F("AVR_ATtiny3226" )
    #elif ( defined(ARDUINO_AVR_ATtiny1626) )
      #define BOARD_NAME      F("AVR_ATtiny1626")
    #elif ( defined(ARDUINO_AVR_ATtiny826) )
      #define BOARD_NAME      F("AVR_ATtiny826")
    #elif ( defined(ARDUINO_AVR_ATtiny426) )
      #define BOARD_NAME      F("AVR_ATtiny426")
    #elif ( defined(ARDUINO_AVR_ATtiny1606) )
      #define BOARD_NAME      F("AVR_ATtiny1606")
    #elif ( defined(ARDUINO_AVR_ATtiny806) )
      #define BOARD_NAME      F("AVR_ATtiny806")
    #elif ( defined(ARDUINO_AVR_ATtiny406) )
      #define BOARD_NAME      F("AVR_ATtiny406")


      ////////////////////////// tinyAVR 0/1 series (atxy4) //////////////////////////

    #elif ( defined(ARDUINO_AVR_ATtiny1614) )
      #define BOARD_NAME      F("AVR_ATtiny1614")
    #elif ( defined(ARDUINO_AVR_ATtiny814) )
      #define BOARD_NAME      F("AVR_ATtiny814")
    #elif ( defined(ARDUINO_AVR_ATtiny414) )
      #define BOARD_NAME      F("AVR_ATtiny414")
    #elif ( defined(ARDUINO_AVR_ATtiny214) )
      #define BOARD_NAME      F("AVR_ATtiny214")
    #elif ( defined(ARDUINO_AVR_ATtiny3224) )
      #define BOARD_NAME      F("AVR_ATtiny3224" )
    #elif ( defined(ARDUINO_AVR_ATtiny1624) )
      #define BOARD_NAME      F("AVR_ATtiny1624")
    #elif ( defined(ARDUINO_AVR_ATtiny824) )
      #define BOARD_NAME      F("AVR_ATtiny824")
    #elif ( defined(ARDUINO_AVR_ATtiny424) )
      #define BOARD_NAME      F("AVR_ATtiny424")
    #elif ( defined(ARDUINO_AVR_ATtiny1604) )
      #define BOARD_NAME      F("AVR_ATtiny1604")
    #elif ( defined(ARDUINO_AVR_ATtiny804) )
      #define BOARD_NAME      F("AVR_ATtiny804")
    #elif ( defined(ARDUINO_AVR_ATtiny404) )
      #define BOARD_NAME      F("AVR_ATtiny404")
    #elif ( defined(ARDUINO_AVR_ATtiny204) )
      #define BOARD_NAME      F("AVR_ATtiny204")

      ////////////////////////// tinyAVR 0/1 series (atxy2) //////////////////////////

    #elif ( defined(ARDUINO_AVR_ATtiny412) )
      #define BOARD_NAME      F("AVR_ATtiny412")
    #elif ( defined(ARDUINO_AVR_ATtiny212) )
      #define BOARD_NAME      F("AVR_ATtiny212"
    #elif ( defined(ARDUINO_AVR_ATtiny402) )
      #define BOARD_NAME      F("AVR_ATtiny402")
    #elif ( defined(ARDUINO_AVR_ATtiny202) )
      #define BOARD_NAME      F("AVR_ATtiny202")

      ////////////////////////////////////////////////////////////////

    #endif

  #endif  // #if !defined(BOARD_NAME)

#else

  #error This is designed only for AVR_ATtiny boards using megaTinyCore

#endif

///////////////////////////////////////////////////////////////////////////////

#ifndef AT_TINY_PWM_VERSION
  #define AT_TINY_PWM_VERSION           F("ATtiny_PWM v1.2.0")

  #define AT_TINY_PWM_VERSION_MAJOR     1
  #define AT_TINY_PWM_VERSION_MINOR     2
  #define AT_TINY_PWM_VERSION_PATCH     0

  #define AT_TINY_PWM_VERSION_INT       1002000
#endif

////////////////////////////////////////

#ifndef _PWM_LOGLEVEL_
  #define _PWM_LOGLEVEL_        0
#endif

////////////////////////////////////////

#include "Arduino.h"

#include "PWM_Generic_Debug.h"

////////////////////////////////////////

/*************************************

  // Pins can use for hardware PWM => PIN_PA3-5, PIN_PB0-2, PIN_PC0-1
  const uint8_t digital_pin_to_timer[] =
  {
  // Left side, top to bottom
  TIMERA0,         // 0  PA4 WO4 WOA
  TIMERA0,         // 1  PA5 WO5 WOB
  TIMERA0,         // 9  PB2 WO2
  TIMERA0,         // 10 PB1 WO1
  TIMERA0,         // 11 PB0 WO0
  #if (defined(TCD0) && defined(USE_TIMERD0_PWM))
  TIMERD0,         // 12 PC0 WOC
  TIMERD0,         // 13 PC1 WOD
  #else
  NOT_ON_TIMER,    // 12 PC0
  NOT_ON_TIMER,    // 13 PC1
  #endif
  TIMERA0,         // 20 PA3 WO3
  };

  // From https://github.com/SpenceKonde/DxCore/blob/master/megaavr/cores/dxcore/Arduino.h#L455-L462

  #define TIMERA0         (0x10) // A "simple" type A timer mapping doesn't get constants for the WO channels.
  #define TIMERA1         (0x08) // Formerly 0x11 - giving it a dedicated bit makes the takeover tracking easy and efficient instead of being a morass of tests and bitmath.
  #define TIMERB0         (0x20) // TCB0
  #define TIMERB1         (0x21) // TCB1
  #define TIMERB2         (0x22) // TCB2
  #define TIMERB3         (0x23) // TCB3
  #define TIMERB4         (0x24) // TCB4
  #define TIMERD0         (0x70) // If any of these bits match it's potentially on TCD0


*************************************/

////////////////////////////////////////

#define INVALID_AT_TINY_PIN       255

////////////////////////////////////////

#define MAX_COUNT_8BIT            256UL
#define MAX_COUNT_16BIT           65536UL

#define MAX_8BIT                  255UL
#define MAX_16BIT                 65535UL


////////////////////////////////////////

extern uint8_t __PeripheralControl;

////////////////////////////////////////
////////////////////////////////////////

class ATtiny_PWM
{
  public:

    ATtiny_PWM(const uint8_t& pin, const float& frequency, const float& dutycycle)
    {
      _pin        = pin;
      _frequency  = frequency;
      _dutycycle  = map(dutycycle, 0, 100.0f, 0, MAX_16BIT);

      _timer      = digitalPinToTimer(pin);

      if (_timer != 0 && !(_timer & __PeripheralControl))
      {
        _timer = 0;

        _PWMEnabled = false;

        PWM_LOGDEBUG1("ATtiny_PWM: Error _timer = 0; pin =", pin);

        return;
      }

      _frequency = frequency;

      _PWMEnabled = true;

      PWM_LOGDEBUG3("ATtiny_PWM: freq =", frequency, ", _dutycycle =", _dutycycle);

      pinMode(pin, OUTPUT);
    }

    ///////////////////////////////////////////

    ~ATtiny_PWM();

    ///////////////////////////////////////////
    ///////////////////////////////////////////

  private:

    ///////////////////////////////////////////

    void setPeriod_TimerA0(uint32_t microseconds) __attribute__((always_inline))
    {
      // TCA Clock is F_CPU / 64, 312.5KHz for 20MHz
      float TCA_Freq_mult = (float) 20000000 / F_CPU;

      PWM_LOGDEBUG5("setPeriod_TimerA0: F_CPU =", F_CPU, ", microseconds =", microseconds,
                    ", TCA_Freq_mult =", TCA_Freq_mult);

      pwmPeriod = ( microseconds / (TCA_Freq_mult * 3.125f * 1.02406554f) );

      TCA0.SPLIT.HPER  = pwmPeriod;

      _actualFrequency =  312500UL / (pwmPeriod * TCA_Freq_mult);

      PWM_LOGDEBUG3("setPeriod_TimerA0: pwmPeriod =", pwmPeriod, ", _actualFrequency =", _actualFrequency);
    }

    ///////////////////////////////////////////

    // #define TIMERD0_PRESCALER (TCD_CLKSEL_20MHZ_gc | TCD_CNTPRES_DIV32_gc | TCD_SYNCPRES_DIV2_gc)

    // Not working with TCD0 yet. TODO fix TCD0 frequency

    void setPeriod_TimerD0(unsigned long microseconds) __attribute__((always_inline))
    {
      // TCD Clock is F_CPU / 32, 625.0KHz for 20MHz
      float TCD_Freq_mult = (float) 20000000 / F_CPU;

      PWM_LOGDEBUG5("setPeriod_TimerD0: F_CPU =", F_CPU, ", microseconds =", microseconds,
                    ", TCD_Freq_mult =", TCD_Freq_mult);

      pwmPeriod = 625000.0f * microseconds / (TCD_Freq_mult * 1000000.0f);

      TCD0.CMPBCLR     = pwmPeriod;

      _actualFrequency =  625000UL / (pwmPeriod * TCD_Freq_mult);

      PWM_LOGDEBUG3("setPeriod_TimerD0: pwmPeriod =", pwmPeriod, ", _actualFrequency =", _actualFrequency);
    }
    
    ///////////////////////////////////////////

    bool setPWM_Reg(const uint8_t& pin, uint16_t dutycycle)
    {
      dutycycle >>= 8;
      
      uint8_t bit_mask = digitalPinToBitMask(pin);

      volatile uint8_t *timer_cmp_out;

      switch (_timer)
      {
        case TIMERA0:
        {         
          setPeriod_TimerA0(1000000UL / _frequency);

          // start from 0, so to add 1 to DC and period
          dutycycle = (( (uint32_t) (pwmPeriod  + 1) * (dutycycle + 1) ) ) >> 8;

#ifdef __AVR_ATtinyxy2__

          if (bit_mask == 0x80)
          {
            bit_mask = 1;
          }

#endif

          uint8_t offset = 0;

          if (bit_mask > 0x04)
          {
            bit_mask <<= 1;
            offset = 1;
          }

          if (bit_mask & 0x44)
            offset += 4;
          else if (bit_mask & 0x22)
            offset += 2;

          timer_cmp_out = ((volatile uint8_t *)(&TCA0.SPLIT.LCMP0)) + (offset);

          (*timer_cmp_out) = (dutycycle + 1);
          TCA0.SPLIT.CTRLB |= bit_mask;
        }

        break;

          ///////////////////////////////////////////

#if (defined(TCD0) && defined(USE_TIMERD0_PWM))

        case TIMERD0:
        {
          // Not OK yet
          //setPeriod_TimerD0(1000000UL / frequency);

          // start from 0, so to add 1 to DC and period
          //dutycycle = (( (uint32_t) (pwmPeriod  + 1) * (dutycycle + 1) ) ) >> 8;
          //////

          uint8_t oldSREG = SREG;

          cli();

          while ((TCD0.STATUS & (TCD_ENRDY_bm | TCD_CMDRDY_bm)) != (TCD_ENRDY_bm | TCD_CMDRDY_bm));

          uint8_t fc_mask;

          if (bit_mask == 2)
          {
            // PIN_PC1
            TCD0.CMPBSET = ((255 - dutycycle) << 1) - 1;
            fc_mask = 0x80;
          }
          else
          {
            // PIN_PC0
            TCD0.CMPASET = ((255 - dutycycle) << 1) - 1;
            fc_mask = 0x40;
          }

          if (!(TCD0.FAULTCTRL & fc_mask))
          {
            TCD0.CTRLA &= ~TCD_ENABLE_bm; // stop the timer
            _PROTECTED_WRITE(TCD0.FAULTCTRL, TCD0.FAULTCTRL | fc_mask);

            while (!(TCD0.STATUS & TCD_ENRDY_bm));

            TCD0.CTRLA |= TCD_ENABLE_bm;
          }
          else
          {
            TCD0.CTRLE = TCD_SYNCEOC_bm;
          }

          SREG = oldSREG;
        }

        break;

#endif    // #if (defined(TCD0) && defined(USE_TIMERD0_PWM))

        ///////////////////////////////////////////

        case NOT_ON_TIMER:
        default:
          if (dutycycle < 128)
          {
            digitalWrite(pin, LOW);
          }
          else
          {
            digitalWrite(pin, HIGH);
          }

          return false;

          break;
      }

      return true;
    }

    ///////////////////////////////////////////
    ///////////////////////////////////////////

  public:

    // dutycycle from 0-65535 for 0%-100% to make use of 16-bit top register
    bool setPWM_Int(const uint8_t& pin, const float& frequency, uint16_t dutycycle)
    {
      if (frequency != _frequency)
      {
        PWM_LOGDEBUG1("setPWM_Int: new freq =", frequency);

        _frequency = frequency;
      }
      
      if ( setPWM_Reg(pin, dutycycle) )
      {
        pinMode(pin, OUTPUT);

        _PWMEnabled = true;
        
        return true;
      }
     
      return false;      
    }

    ///////////////////////////////////////////
    ///////////////////////////////////////////

    bool setPWM()
    {
      return setPWM_Int(_pin, _frequency, _dutycycle);
    }

    ///////////////////////////////////////////

    bool setPWM(const uint8_t& pin, const float& frequency, const float& dutycycle)
    {
      _dutycycle = round(map(dutycycle, 0, 100.0f, 0, MAX_COUNT_16BIT));

      PWM_LOGDEBUG3(F("setPWM: _dutycycle ="), _dutycycle, F(", frequency ="), frequency);

      return setPWM_Int(pin, frequency, _dutycycle);
    }

    ///////////////////////////////////////////

    bool setPWM_Period(const uint8_t& pin, const float& period_us, const float& dutycycle)
    {
      _dutycycle = round(map(dutycycle, 0, 100.0f, 0, MAX_COUNT_16BIT));

      PWM_LOGDEBUG3(F("setPWM_Period: _dutycycle ="), _dutycycle, F(", period_us ="), period_us);

      return setPWM_Int(pin, round(1000000.0f / period_us), _dutycycle);
    }

    ///////////////////////////////////////////

    // Must have same frequency
    bool setPWM_manual(const uint8_t& pin, const uint16_t& DCValue)
    {
      // Not the same pin or overvalue
      if (_pin != pin)
        return false;

      _dutycycle = DCValue;

      PWM_LOGINFO3(F("setPWM_manual: _dutycycle ="), _dutycycle, F(", frequency ="), _frequency);

      return setPWM_Int(pin, _frequency, DCValue);
    }
    
    ///////////////////////////////////////////
       
    // Faster than setPWM_DCPercentage_manual by not using float
    // DCPercentage from 0-65535 for 0.0f - 100.0f
    bool setPWM_DCPercentageInt_manual(const uint8_t& pin, const uint16_t& DCPercentage)
    {    
      return ( setPWM_Reg( pin, DCPercentage ) );
    }
    
    ///////////////////////////////////////////
    
    // DCPercentage from 0.0f - 100.0f for 0-65535
    bool setPWM_DCPercentage_manual(const uint8_t& pin, const float& DCPercentage)
    {
      _dutycycle = ( DCPercentage * MAX_16BIT ) / 100.0f;
      
      // Convert to DCValue based on resolution = MAX_16BIT
      PWM_LOGDEBUG3(F("setPWM_DCPercentage_manual: DCPercentage ="), DCPercentage, F(", dc ="), ( DCPercentage * MAX_16BIT ) / 100.0f);
      
      return setPWM_Int(pin, _frequency, _dutycycle);
    }

    ///////////////////////////////////////////

    inline float getActualDutyCycle()
    {
      return ( ( (float) _dutycycle + 1 ) * 100 / MAX_16BIT );
    }

    ///////////////////////////////////////////

    inline float getActualFreq()
    {
      return _frequency;
    }

    ///////////////////////////////////////////

    inline float getPWMPeriod()
    {
      return (1000000.0f / _frequency);
    }

    ///////////////////////////////////////////

    inline uint32_t get_freq_CPU()
    {
      return F_CPU;
    }

    ///////////////////////////////////////////

    inline uint32_t getPin()
    {
      return _pin;
    }

    ///////////////////////////////////////////

    void setResolution(const uint8_t& resolution)
    {
      // Must be <= 16-bit and >= 8-bit
      if ( (resolution <= 16) && (resolution >= 8) )
      {
        _resolution = resolution;
      }
    }

    ///////////////////////////////////////////

    bool isPWMEnabled()
    {
      return _PWMEnabled;
    }

    ///////////////////////////////////////////

  private:

    uint32_t        _actualFrequency;

    float           _frequency;

    // dutycycle from 0-65535 for 0%-100% to make use of 16-bit top register
    // _dutycycle = map(dutycycle, 0, 100.0f, 0, 65535) for better accuracy
    uint16_t        _dutycycle;
    //////////

    uint8_t         _pin;

#define INVALID_TIMER     255

    uint8_t         _timer = INVALID_TIMER;

    uint16_t        pwmPeriod;

    uint8_t         _resolution = 8;

    bool            _PWMEnabled = false;

    ///////////////////////////////////////////
};

///////////////////////////////////////////


#endif    // AT_TINY_PWM_H

