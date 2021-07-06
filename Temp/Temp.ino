#include <BlynkSimpleStream.h>

char auth[] = "BqFgFWZCl1WCrrjJi-XaDzcVgbsLXdGy";
void setup()
{
  Serial.begin(9600);
  Serial.begin(9600);
  Blynk.begin(auth, Serial);
 
  pinMode(A1, INPUT);
 //  pinMode(12, OUTPUT);
  // pinMode(13, OUTPUT);
  
  }

void loop()
{
   Blynk.run();
 
  }
