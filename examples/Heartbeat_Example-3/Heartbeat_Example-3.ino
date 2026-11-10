//******************************************************************
//
//     A r n o T e k   H e a r t B e a t   E x a m p l e   3  
//
//        Toggle default pin 13 every half second
//        Toggle pin 12 every minute
//        Call user defined function every 90 seconds
//
//------------------------------------------------------------------
//
//  Copyright 2026 Anthony J. Arnovitz  All rights reserved.
//
//******************************************************************



// Include the HearBeat class library
#include <ArnoTek_HeartBeat.h>


// Instantiate an object for toggling pin 13 every half a second (the defaults)
ArnoTek_HeartBeat HeartBeat;

// Instantiate an object for toggling pin 12 every minute
ArnoTek_HeartBeat Pin12_signal((long unsigned)60000, 12); 

// Instantiate an object for calling user defined function every 90 seconds
// Note that specifying 0 as the pin to toggle indicates that no pin is to be toggled
ArnoTek_HeartBeat Seconds90((long unsigned)90000, 0, &My90SecFunction);



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
  Pin12_signal.Toggle();  // Toggle pin 12 (if it is time) 
  Seconds90.Toggle();     // Call the user defined function "My90SecFunction" every 90 seconds

}


//                  * * *   C a l l b a c k   F u n c t i o n s   * * *

void My90SecFunction(ArnoTek_HeartBeat *myObject, long unsigned myCurrentTime)
{
  Serial.print("My90SecFunction entered - current timer value: ");
  Serial.println(myCurrentTime);
}


