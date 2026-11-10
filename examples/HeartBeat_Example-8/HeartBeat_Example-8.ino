//******************************************************************
//
//     A r n o T e k   H e a r t B e a t   E x a m p l e   8 
//
//        Toggle default pin 13 every half second
//
//        Toggle pin 12 every 2 seconds and call a user defined
//        function which in turn calls another user defiinded 
//        function
//
//        Toggle pin 11 every 5 and a half seconds and call the 
//        same userdefined function which in turn calls a third 
//        user defined function
//
//------------------------------------------------------------------
//
//  Copyright 2026 Anthony J. Arnovitz  All rights reserved.
//
//******************************************************************


#include "ArnoTek_HeartBeat.h"

// Instantiate an object for toggling pin 13 every half a second
ArnoTek_HeartBeat HeartBeat; 

// Instantiate an object for toggling pin 12 every two seconds and call a user callbaack function
ArnoTek_HeartBeat Pin12_signal((long unsigned)2000, 12, &Callback); 

// Instantiate an object for toggling pin 11 every five and a half seconds and call a user callbaack function
ArnoTek_HeartBeat Pin11_signal((long unsigned)5500, 11, &Callback); 
 




//                  * * *   S E T U P   * * *

void setup() 
{
  delay(4000);
  Serial.begin(115200);
  Serial.println("\n\n*** Starting setup ***\n");

  // Specify the address of the function to be called by the HeartBeat objects
  Pin12_signal.UserSaveValue1((unsigned long)Function1);
  Pin11_signal.UserSaveValue1((unsigned long)Function2);

  // Set the parameter value to be passed to the function defined in the HeartBeat object
  Pin12_signal.UserSaveValue2((unsigned long)5);
  Pin11_signal.UserSaveValue2((unsigned long)7);

  Serial.println("*** Setup complete ***\n");
}




//                  * * *   L O O P   * * *

void loop() 
{
  HeartBeat.Toggle();       // Toggle the heartbeat LED (if it is time)    

  Pin12_signal.Toggle();    // Toggle pin 12 and call the callback routine (if it is time) 
  Pin11_signal.Toggle();    // Toggle pin 11 and call the callback routine (if it is time)  
}



//         * * *   U s e r   D e f i n e d   F u n c t i o n s   * * *


// This function is called from multiple HeartBeat objects.  It in turn calls
// the function that was specified in the calling HeartBeat's variable
// "UserSaveValue1" and passes to it the value that was saved in the 
// calling HeartBeat's "UserSaveValue2".
//
// The callback function receives two parameters from the calling Heartbeat
// object.  The first is the address of the calling Heartbeat object and
// the second is the current value from the miilis function that triggered
// the callback.
 
void Callback(ArnoTek_HeartBeat *myObject, long unsigned myCurrentTime)
{
  Serial.print("\n\nCallback entered for object: ");
  Serial.println((uintptr_t)myObject, HEX);

  // Get the address of the function that is to be called from the calling 
  // HeartBeat object's saved user save value and define a function pointer
  void(*myNextFunction)(long unsigned) = myObject->UserSaveValue1();

  // Call the specified function using the function pointer and pass it the 
  // value that was saved in the calling HeartBeat object's second 
  // saved user save value
  myNextFunction(myObject->UserSaveValue2());

  Serial.print("Callback exited for object: ");
  Serial.println((uintptr_t)myObject, HEX);
}



// This function is called from the function that is specified in the HeartBeat object.
void Function1(long unsigned myParm)
{
  Serial.println("\tFunction 1 entered");

  Serial.print("\t\tThe parameter value is: ");
  Serial.println(myParm);

  Serial.println("\tFunction 1 exited ");
}



// This function is called from the function that is specified in the HeartBeat object.
void Function2(long unsigned myParm)
{
  Serial.println("\tFunction 2 entered");

  Serial.print("\t\tThe parameter value is: ");
  Serial.println(myParm);

  Serial.println("\tFunction 2 exited ");
}
