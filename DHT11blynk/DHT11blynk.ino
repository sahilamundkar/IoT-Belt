#include <BlynkSimpleStream.h>
#include <SimpleDHT.h>
#include <SimpleTimer.h>

#define BLYNK_PRINT Serial

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 4;
SimpleDHT11 dht11(pinDHT11);
char auth[] = "UYhdR8NzCJqyPwzZSVdxRzEWUkBoZ_AN";
SimpleTimer timer;
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, Serial);
 
timer.setInterval(2000, sendUptime);
  
  }
void sendUptime()
{
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");

  Blynk.virtualWrite(V5, temperature);//send the value to blynk application
  Blynk.virtualWrite(V6, humidity);
}


void loop()
{
   Blynk.run();
    timer.run();
  }
