//******************************************************************
//
//     A r n o T e k   H e a r t B e a t   E x a m p l e   5  
//
//        Toggle default pin 13 every half second
//        Toggle pin 12 evry 90 seconds
//        Call user defined function once after 90 seconds
//        Call user defined function every 5 minutes
//
//------------------------------------------------------------------
//
//  Copyright 2026 Anthony J. Arnovitz  All rights reserved.
//
//******************************************************************



// Include the HearBeat class library
#include <ArnoTek_HeartBeat.h>

// Declare function definition
void My90SecFunction(long unsigned myCurrentTime);
void My5MinFunction(long unsigned myCurrentTime);



// Instantiate an object for toggling pin 13 every half a second
ArnoTek_HeartBeat HeartBeat(static_cast<long unsigned>(500));

// Instantiate an object for toggling pin 12 every minute
ArnoTek_HeartBeat Pin12_signal(static_cast<long unsigned>(60000), 12); 

// Instantiate an object for calling user defined function every 90 seconds
ArnoTek_HeartBeat Seconds90(static_cast<long unsigned>(90000), &My90SecFunction);

// Instantiate an object for calling user defined function every 5 minutes
ArnoTek_HeartBeat Minutes5(static_cast<long unsigned>(300000), &My5MinFunction);



//                  * * *   S E T U P   * * *
void setup() 
{
  delay(4000);
  Serial.begin(115200);
  Serial.println("\n\n*** Setup begin ***\n");



  Serial.println("*** Setup complete ***\n");
}


//                  * * *   L O O P   * * *
void loop() 
{
  HeartBeat.Toggle();     // Toggle the heartbeat LED (if it is time)    
  Pin12_signal.Toggle();  // Toggle the heartbeat timer (if it is time)  
  Seconds90.Toggle();     // Call the user defined function "My90SecFunction" evry 90 seconds
  Minutes5.Toggle();      // Call the user defined function "My5MinFunction" evry 5 minutes

}


//                  * * *   C a l l b a c k   F u n c t i o n s   * * *

void My90SecFunction(long unsigned myCurrentTime)
{
  Serial.print("My90SecFunction entered - current timer value: ");
  Serial.println(myCurrentTime);

  Seconds90.Callback(nullptr); 	  // Disable callback
  Seconds90.Delay(4294967000);	  // Set the timer delay to a very high number

}

void My5MinFunction(long unsigned myCurrentTime)
{
  Serial.print("\tMy5MinFunction entered - current timer value: ");
  Serial.println(myCurrentTime);
}

