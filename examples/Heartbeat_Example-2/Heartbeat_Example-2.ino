//******************************************************************
//
//     A r n o T e k   H e a r t B e a t   E x a m p l e   2  
//
//        Toggle default pin 13 every half second
//        Toggle pin 12 evry 90 seconds
//
//------------------------------------------------------------------
//
//  Copyright 2026 Anthony J. Arnovitz  All rights reserved.
//
//******************************************************************



// Include the HearBeat class library
#include <ArnoTek_HeartBeat.h>

// Instantiate an object for toggling pin 13 every half a second
ArnoTek_HeartBeat HeartBeat(static_cast<long unsigned>(500)); 

// Instantiate an object for toggling pin 12 every minute
ArnoTek_HeartBeat Pin12_signal(static_cast<long unsigned>(60000), 12); 




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
}



