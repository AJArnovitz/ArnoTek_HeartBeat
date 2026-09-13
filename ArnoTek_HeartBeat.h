//*******************************************************************************************
//                                                                                          *
//                                A r n o T e k _ H e a r t B e a t                         *
//                                                                                          *
//                   Copyright Anthony J. Arnovitz 2023    All rights reserved.             *
//                                                                                          *
//------------------------------------------------------------------------------------------*
//                                                                                          *
//      This class defines a Heartbeat utility for Arduino applications. It may use         *
// internally referenced millis() time values or the time value may be passed in using a    *
// parameter as desired. When the "Toggle" method is called, the heartbeat will be toggled  *
// if the amount of time (in milliseconds) specified at initialization has passed since the *
// last time the heartbeat was toggled.  If the specified amount of time has not passed,    *
// the "Toggle" method exits without doing anything.                                        *
//                                                                                          *
//      Optionally, a callback function my be specified when this object is initialized.    *
// If a callback was defined, it will be called when the timer expires and it will be       *
// passed the current timer value.                                                          *
//                                                                                          *
//      More than one hearbeat object may be defined whenever desired.  Thus, one hearbeat  *
// object may be defined to toggle an output pin and to call a callback function and        *
// a second may be define to call another (or the same) callback function with different    *
// timeout values.                                                                          *
//                                                                                          *
//      NOTE: The Arduino millisecond timer will rollover every 4,294,967,295 (0xFFFF FFFF) *
// milliseconds which is 49 days, 17 hours, 2 minutes, 47 seconds, and 296 milliseconds.    *
// This code will properly handle the rollover of the Arduino timer value.                  *
//                                                                                          *
//------------------------------------------------------------------------------------------*
//                                                                                          *
// How to use this code:                                                                    *
//     1. Copy this code to your Arduino library                                            *
//     2. Add "#include <ArnoTek_HeartBeat.h>" to your source code                          *
//     3. Define heartbeat object before the setup routine                                  *
//     4. Call the "Init" method of the heartbeat object in the setup routine to set the    *
//        values.  (Note - maybe exclude if values were specified at object definition.)    *
//     5. Call the "Toggle" method of the heartbeat object in the loop routine to toggle    * 
//        the heartbeat and/or invoke a specified callback function.                        *
//                                                                                          *
// Example:                                                                                 *
//    #include <ArnoTek_HeartBeat.h>                                                        *
//        .                                                                                 *
//        .                                                                                 *
//        .                                                                                 *
//    const int HeartBeatPin             = 13;     // Define the putput pin                 *
//    const long unsigned HeartBeatDelay = 500;    // Define delay value in milliseconds    *
//    ArnoTek_HeartBeat HeartBeat;                 // Define heartbeat object               *
//                                                                                          *
//                      - - - O R   - - -                                                   *
//                                                                                          *
//         Define heartbeat object with a timer value of 500 milliseconds and use the       *
//         default output pin (13)                                                          *
//                                                                                          *
//    ArnoTek_HeartBeat HeartBeat(static_cast<long unsigned>(500));     // No need to init  *
//                                                                         in setup()       *
//                                                                                          *
//        .                                                                                 *
//        .                                                                                 *
//        .                                                                                 *
//    void setup()                                                                          *
//    {                                                                                     *
//          NOTE: Call to "Init" is not needed if values are specified when the Heartbeat   *
//                object was defined.                                                       *
//                                                                                          *
//       HeartBeat.Init(HeartBeatDelay, HeartBeatPin);   // Initialize the heartbeat object *
//           .                                                                              *
//           .                                                                              *
//           .                                                                              *
//                      - - - O R   - - -                                                   *
//                                                                                          *
//       HeartBeat.Init(HeartBeatDelay, HeartBeatPin, &myCallback);                         *
//                                                                                          *
//    }                                                                                     *
//                                                                                          *
//                                                                                          *
//    void loop()                                                                           *
//    {                                                                                     *
//       HeartBeat.Toggle();     // Toggle the heartbeat LED (if it is time)                *
//           NOTE: If a callback function was specified, it will be called when the timer   *
//                 has expired.                                                             *
//           .                                                                              *
//           .                                                                              *
//           .                                                                              *
//    }                                                                                     *
//                                                                                          *
//                                                                                          *
//    void myCallback(long unsigned myCurrentTime)                                          *
//    {                                                                                     *
//       Serial.print("Timer value: ");                                                     *
//       Serial.println(myCurrentTime);                                                     *
//    }                                                                                     *
//                                                                                          *
//*******************************************************************************************

#ifndef ArnoTekHeartBeat_h
#define ArnoTekHeartBeat_h

// This class controls the hearbeat signal and/or calling a specified calllback routine
class ArnoTek_HeartBeat
{
  private:
    bool          Value;                            // current value of the heartbeat signal
    int           myPin      = 0;                   // pin that is used for the heartbeat signal
    const int     defaultPin = 13;                  // define default output pin
    long unsigned myExpirationTime;                 // value for when the timeout last expired
    long unsigned myDelay = 429496700;              // delay (in milliseconds) between heartbeat signal toggles
    void          (*myCallback)(long unsigned ct) = nullptr;  // Pointer to callback routine for when timer expires


  public:  

    //*************************************************************************************
    // CONSTRUCTOR - No paramaters specified.
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             {NONE}
    //
    //             NOTE - If this constructor is used, an Init method must be called in
    //                    the setup routine to initialize control variables.
    //*************************************************************************************

    ArnoTek_HeartBeat()
    {}


    //*************************************************************************************
    // CONSTRUCTOR - Specify timer delay and use default output pin (No callback)
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             delay - number of miliseconds between toggling of the output signal
    //*************************************************************************************

    ArnoTek_HeartBeat(long unsigned delay)
    {
      Init(millis(), delay, defaultPin, nullptr); 
    }
    

    //*************************************************************************************
    // CONSTRUCTOR - Specify timer delay and output pin (No callback)
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             delay - number of miliseconds between toggling of the output signal
    //               pin - the digital pin that is used to output the heartbeat signal
    //*************************************************************************************

    ArnoTek_HeartBeat(long unsigned delay, int pin)
    {
      Init(millis(), delay, pin, nullptr); 
    }


    //*************************************************************************************
    // CONSTRUCTOR - Specify timer delay, output pin, and address of callback function
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             delay - number of miliseconds between toggling of the output signal
    //               pin - the digital pin that is used to output the heartbeat signal
    //          callback - address of the routine to call when the timer expires
    //*************************************************************************************

    ArnoTek_HeartBeat(long unsigned delay, int pin, void(*callback)(long unsigned ct))
    {
    	Init(millis(), delay, pin, callback);        // Go initialize the heartbeat object
    }


    //*************************************************************************************
    // CONSTRUCTOR - Specify timer delay and address of callback function
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             delay - number of miliseconds between toggling of the output signal
    //          callback - address of the routine to call when the timer expires
    //*************************************************************************************

    ArnoTek_HeartBeat(long unsigned delay, void(*callback)(long unsigned ct))
    {
    	Init(millis(), delay, 0, callback);        // Go initialize the heartbeat object
    }


    //=====================================================================================


    //*************************************************************************************
    // Initialize the heartbeat control using the specified timer delay and the default 
    // output pin (No callback)
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             delay - number of miliseconds between toggling of the output signal
    //*************************************************************************************

    Init(long unsigned delay)
    {
      Init(millis(), delay, defaultPin, nullptr); 
    }


    //*************************************************************************************
    // Initalize the heartbeat control object using an internal timer value
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             delay - number of miliseconds between toggling of the output signal
    //               pin - the digital pin that is used to output the heartbeat signal
    //*************************************************************************************

    Init(long unsigned delay, int pin)
    {
    	Init(millis(), delay, pin, nullptr);        // Go initialize the heartbeat object
    }
	

    //*************************************************************************************
    // Initalize the heartbeat control object using an internal timer value and a
    // callabck function
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             delay - number of miliseconds between toggling of the output signal
    //          callback - address of the routine to call when the timer expires
    //                     NOTE: If set to nullptr, no callback function is called.
    //*************************************************************************************

    Init(long unsigned delay, void(*callback)(long unsigned ct))
    {
    	Init(millis(), delay, 0, callback);        // Go initialize the heartbeat object
    }
	

  
    //*************************************************************************************
    // Initalize the heartbeat control object using an internal timer value and a
    // callabck function
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             delay - number of miliseconds between toggling of the output signal
    //               pin - the digital pin that is used to output the heartbeat signal
    //          callback - address of the routine to call when the timer expires
    //                     NOTE: If set to nullptr, no callback function is called.
    //*************************************************************************************

    Init(long unsigned delay, int pin, void(*callback)(long unsigned ct))
    {
    	Init(millis(), delay, pin, callback);        // Go initialize the heartbeat object
    }




    //*************************************************************************************
    // Initialize the heartbeat control using the specified timer delay and the default 
    // output pin (No callback)
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             curTime - current value of the Arduino millisecond time
    //             delay - number of miliseconds between toggling of the output signal
    //*************************************************************************************

    Init(long unsigned curTime, long unsigned delay)
    {
      Init(curTime, delay, defaultPin, nullptr); 
    }



    //*************************************************************************************
    // Initialize the heartbeat control using the specified timer delay and the default 
    // output pin (No callback)
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             curTime - current value of the Arduino millisecond time
    //                 pin - the digital pin that is used to output the heartbeat signal
    //                       NOTE: If set to 0, no pin is toggled.
    //             delay - number of miliseconds between toggling of the output signal
    //*************************************************************************************

    Init(long unsigned curTime, long unsigned delay, int pin)
    {
      Init(curTime, delay, pin, nullptr); 
    }


    //*************************************************************************************
    // Initalize the heartbeat control object using a specified timer valuea and a
    // callback function
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             curTime - current value of the Arduino millisecond time
    //               delay - number of miliseconds between toggling of the output signal
    //                       NOTE: This passed in parameter value MUST be defined as a long 
    //                             unsigned value.  If a literal value, such as 2000 is
    //                             specified, the value will be treated as an "int" which 
    //                             will call a different Init function because the value 
    //                             will be interpreted as an integer pin value.
    //            callback - address of the routine to call when the timer expires
    //                       NOTE: If set to nullptr, no callback function is called.
    //*************************************************************************************

    Init(long unsigned curTime, long unsigned delay, void(*callback)(long unsigned ct))
    {
    	Init(curTime, delay, 0, callback);        // Go initialize the heartbeat object
    }


    //*************************************************************************************
    // Initalize the heartbeat control object using a specified timer value, an output pin
    // number and a callback function
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             curTime - current value of the Arduino millisecond time
    //               delay - number of miliseconds between toggling of the output signal
    //                 pin - the digital pin that is used to output the heartbeat signal
    //                       NOTE: If set to 0, no pin is toggled.
    //            callback - address of the routine to call when the timer expires
    //                       NOTE: If set to nullptr, no callback function is called.
    //*************************************************************************************

    Init(long unsigned curTime, long unsigned delay, int pin, void(*callback)(long unsigned ct))
    {
      // Save the initial values
      myDelay    = delay;
      myPin      = pin;
      myCallback = callback;
      Value    = false;

      // If there is an utput pin to toggle, configure the pin for the heartbeat and set its initial signal
      if(myPin != 0)
      {
        pinMode(myPin, OUTPUT);
        digitalWrite(myPin, Value);
      }

      // Save the current time
      myExpirationTime = curTime;
    }


    //=====================================================================================


    //*************************************************************************************
    // Update the output pin number that is being toggled.
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             pin - the digital pin that is used to output the heartbeat signal
    //                   NOTE: A value of 0 will stop toggling of the output pin.
    //*************************************************************************************

    void Pin(int pin)
    {
      myPin = pin;
    }


    //*************************************************************************************
    // Update the number of milliseconds between toggling of the output signal and/or 
    // call the callback function.
    //-------------------------------------------------------------------------------------
    // Parameters:
    //               delay - number of miliseconds between toggling of the output signal
    //*************************************************************************************

    void Delay(long unsigned delay)
    {
      myDelay = delay;
    }


    //*************************************************************************************
    // Returns the number of milliseconds between toggling of the output signal and/or 
    // call the callback function.
    //-------------------------------------------------------------------------------------
    // Parameters:
    //               NONE
    //
    // Returns:
    //               Number of miliseconds between toggling of the output signal
    //*************************************************************************************

    long unsigned Delay()
    {
      return myDelay;
    }


    //*************************************************************************************
    // Update the address of the callback function that is called when the timer delay
    // expires.
    //-------------------------------------------------------------------------------------
    // Parameters:
    //            callback - address of the routine to call when the timer expires
    //                       NOTE: If set to nullptr, no callback function is called.
    //*************************************************************************************

    void Callback(void(*callback)(long unsigned ct))
    {
      myCallback = callback;
    }


    //=====================================================================================


    //*************************************************************************************
    // Toggle the heartbeat when the previously specified amount of time has passed
    // using an internal timer value
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             {NONE}
    //*************************************************************************************

    void Toggle()
    {
	    Toggle(millis());        // Go toggle the heartbeat when appropriate
    }


    //*************************************************************************************
    // Toggle the heartbeat when the previously specified amount of time has passed
    // using a specified timer value
    //-------------------------------------------------------------------------------------
    // Parameters:
    //             curTime - current value of the Arduino time
    //*************************************************************************************

    void Toggle(long unsigned curTime)
    {
      // Has the timeout period expired?
      if (curTime - myExpirationTime >= myDelay) // This works even when the timer value rolls over
      {
        // Yes - toggle the heartbeat and save the time the last time the heartbeat was toggled
        myExpirationTime = curTime;        // Save the time for when the heartbeat last expired

        // Is there a pin to toggle?
        if(myPin != 0)
        {
          // Yes - toggle the output pin
	        Value          = !Value;         // Toggle the heartbeat
          digitalWrite(myPin, Value);      // output the new heartbeat state
        }

        // If a callback function was defined, call it with the current timer value
        if(myCallback)
        {
          myCallback(curTime);             // Call the user's specified callback function
        }
      }
   }

};
#endif  // ArnoTekHeartBeat_h