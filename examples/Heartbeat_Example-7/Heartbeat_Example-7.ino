//******************************************************************
//
//     A r n o T e k   H e a r t B e a t   E x a m p l e   7 
//
//        Toggle default pin 13 every half second
//        Toggle pin 12 every 90 seconds
//        Call user defined function once after 90 seconds
//        Call user defined function every 5 minutes
//
//  NOTE: This demo uses default construcctors with Init functions.
//
//------------------------------------------------------------------
//
//  Copyright 2026 Anthony J. Arnovitz  All rights reserved.
//
//******************************************************************



// Include the HearBeat class library
#include <ArnoTek_HeartBeat.h>


// Instantiate the HeartBeat objects (initialize them later in the setup function)
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

  // Get current millis value to use for initializing all heartbeat objects
  long unsigned initialTimer = millis();


  // Initialize the object for toggling pin 13 every half a second
  HeartBeat.Init(initialTimer, (long unsigned)500);

  // Initialize the object for toggling pin 12 every minute
  Pin12_signal.Init(initialTimer, (long unsigned)60000, 12); 

  // Initialize the object for calling user defined function every 90 seconds
  Seconds90.Init(initialTimer, (long unsigned)90000, 0, &My90SecFunction);

  // Initialize the object for calling user defined function every 5 minutes
  Minutes5.Init(initialTimer, (long unsigned)300000, 0, &My5MinFunction);


  Serial.println("*** Setup complete ***\n");
}


//                  * * *   L O O P   * * *
void loop() 
{
  long unsigned currentTimer = millis();

  HeartBeat.Toggle(currentTimer);     // Toggle the heartbeat LED (if it is time)    
  Pin12_signal.Toggle(currentTimer);  // Toggle the heartbeat timer (if it is time)  
  Seconds90.Toggle(currentTimer);     // Call the user defined function "My90SecFunction" every 90 seconds
  Minutes5.Toggle(currentTimer);      // Call the user defined function "My5MinFunction" every 5 minutes

}


//                  * * *   C a l l b a c k   F u n c t i o n s   * * *

void My90SecFunction(ArnoTek_HeartBeat *myObject, long unsigned myCurrentTime)
{
  Serial.print("My90SecFunction entered - current timer value: ");
  Serial.println(myCurrentTime);

  myObject->Callback(nullptr); 	  // Disable callback
  myObject->Delay(4294967000);	  // Set the timer delay to a very high number

}

void My5MinFunction(ArnoTek_HeartBeat *myObject, long unsigned myCurrentTime)
{
  Serial.print("\tMy5MinFunction entered - current timer value: ");
  Serial.println(myCurrentTime);
}

