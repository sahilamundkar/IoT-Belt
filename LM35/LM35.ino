#include <ESP8266WiFi.h>//Install these library
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

#define BLYNK_PRINT Serial

float vref = 3.3;
float resolution = vref / 1023.0;
float temperature;

char auth[] = "Hw1vnwJ-X6t-oL1A9LTa9amI4Whjxvd3";
char ssid[] = "Sahil1950_5G";
char pass[] = "sahil123$";
SimpleTimer timer;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000, sendUptime);
}

void sendUptime()
{
  float temperature = analogRead(A0);//lm35 is connected to pin A0 on NodeMcu
  temperature = (temperature * resolution);
  temperature = temperature * 100.0;
  Serial.print("LM35 temperature: ");//serial print the value 
  Serial.println(temperature);
  Blynk.virtualWrite(V0, temperature);//send the value to blynk application
}

void loop()
{
  Blynk.run();
  timer.run();
}
//Thanks for your use
