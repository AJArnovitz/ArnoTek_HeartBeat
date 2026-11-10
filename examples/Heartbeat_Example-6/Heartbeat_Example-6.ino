//******************************************************************
//
//     A r n o T e k   H e a r t B e a t  E x a m p l e   6  
//
//        Toggle default pin 13 every quarter second
//        Toggle pin 12 every 90 seconds
//        Call user defined function once after 90 seconds
//        Call user defined function every 5 minutes
//
//  NOTE: This demo uses default constructors with Init functions.
//
//------------------------------------------------------------------
//
//  Copyright 2026 Anthony J. Arnovitz  All rights reserved.
//
//******************************************************************



// Include the HearBeat class library
#include <ArnoTek_HeartBeat.h>


// Instantiate the HeartBeat objects that will be initialized in the setup function
ArnoTek_HeartBeat HeartBeat;
ArnoTek_HeartBeat Pin12_signal; 
ArnoTek_HeartBeat Seconds90;
ArnoTek_HeartBeat Minutes5;


//                  * * *   S E T U P   * * *
void setup() 
{
  delay(4000);
  Serial.begin(115200);
  Serial.println("\n\n*** Setup begin ***\n");


  // Initialize the object for toggling pin 13 every quarter of a second
  HeartBeat.Init((long unsigned)250);

  // Initialize the object for toggling pin 12 every minute
  Pin12_signal.Init((long unsigned)60000, 12); 

  // Initialize the object for calling user defined function every 90 seconds
  Seconds90.Init((long unsigned)90000, 0, &My90SecFunction);

  // Initialize the object for calling user defined function every 5 minutes
  Minutes5.Init((long unsigned)300000, 0, &My5MinFunction);


  Serial.println("*** Setup complete ***\n");
}


//                  * * *   L O O P   * * *
void loop() 
{
  HeartBeat.Toggle();     // Toggle the heartbeat LED (if it is time)    
  Pin12_signal.Toggle();  // Toggle the heartbeat timer (if it is time)  
  Seconds90.Toggle();     // Call the user defined function "My90SecFunction" every 90 seconds
  Minutes5.Toggle();      // Call the user defined function "My5MinFunction" every 5 minutes

}


//                  * * *   C a l l b a c k   F u n c t i o n s   * * *

void My90SecFunction(ArnoTek_HeartBeat *myObject, long unsigned myCurrentTime)
{
  Serial.print("My90SecFunction entered - current timer value: ");
  Serial.println(myCurrentTime);

  myObject->Callback(nullptr); 	  // Disable callback
  myObject->Delay(4294967000);	  // Set the timer delay to a very high number

}


// This callback function sets up toggling pins the first time it is caller
// and then alternates which pin is toggled every other time it is called.
// This produces the effect of toggling one pin on then off at the timeout
// value and then it changes to a different pin which is toggled on and off
// and then it switches back to the initial pin.
void My5MinFunction(ArnoTek_HeartBeat *myObject, long unsigned myCurrentTime)
{
  Serial.print("\tMy5MinFunction entered - current timer value: ");
  Serial.println(myCurrentTime);
  static int  flagCount = 0;
  static bool flag      = false;
  static bool firstTime = true;


  // If this is the first time this function is called, it needs to 
  // mark the GPIO pins as output because the pins were not initialized
  // as output when the HeartBeat object was initialized since the pin
  // to be toggled was originally set to 0.
  if(firstTime)
  {
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    firstTime = false;
  }

  // Swap which pins are being toggled after toggling the pin on then off
  if((flagCount % 2) == 0 ) 
  {
    if(flag) myObject->Pin(10);
    else myObject->Pin(11);
    flag = !flag;
  }
  flagCount++;
}

