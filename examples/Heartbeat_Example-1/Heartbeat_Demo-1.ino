
  +
///**************************************************
//
//     H e a r t B e a t   D e m o   1  
//
//        Toggle default pin 13 every half second
//
//**************************************************



// Include the HearBeat class library
#include <ArnoTek_HeartBeat.h>


// Instantiate an object for toggling pin 13 every half a second
ArnoTek_HeartBeat HeartBeat(static_cast<long unsigned>(500)); 



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
  // Toggle the heartbeat LED (if it is time)
  HeartBeat.Toggle();     // Toggle the heartbeat LED (if it is time)




}