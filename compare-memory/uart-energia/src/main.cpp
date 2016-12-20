#include <Energia.h>

void setup()
{
  Serial.begin(9600);
}

void loop() {

   Serial.println("hello");
   Serial.println(123.456);
   // while( Serial.available() ) {
   //    String storedData = Serial.readString();
   //    Serial.println(storedData);
   //    if(storedData.equals(str)) {
   //       Serial.println("MATCHED !");
   //    }
   //    else {
   //       Serial.println("NOT MATCH !");
   //    }
   // }
}

// Programming...
// Writing 2470 bytes at c000...
// Writing   32 bytes at ffe0...
// Done, 2502 bytes total
