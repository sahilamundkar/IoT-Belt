#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ljcOfkZRIR_JicYVuKcma0jcxBx7Badq";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Sahil1950_5G";
char pass[] = "sahil123$";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
