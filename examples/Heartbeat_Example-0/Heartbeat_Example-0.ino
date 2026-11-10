//******************************************************************
//
//     A r n o T e k   H e a r t B e a t   E x a m p l e   0  
//
//        Toggle default pin 13 every half second
//
//------------------------------------------------------------------
//
//  Copyright 2026 Anthony J. Arnovitz  All rights reserved.
//
//******************************************************************



// Include the HearBeat class library
#include <ArnoTek_HeartBeat.h>


ArnoTek_HeartBeat HeartBeat; // Instantiate an object for toggling pin 13 every half a second


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
}