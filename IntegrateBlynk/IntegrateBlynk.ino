#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#define BLYNK_PRINT Serial1

#include <PulseSensorPlayground.h>

#include <SoftwareSerial.h>
SoftwareSerial SwSerial(18, 19); // RX, TX

#include <BlynkSimpleStream.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "TnetmtR-wM_J-VpCx7BpmjPnO9Pnf3jE";

#include <DHT.h>
#define DHTPIN 22         // What digital pin we're connected to
#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value.
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


#include <TinyGPS.h>
TinyGPS gps;  //Creates a new instance of the TinyGPS object// Includes the PulseSensorPlayground Library.
WidgetMap myMap(V1);

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);

  Blynk.begin(Serial, auth);
  dht.begin();

  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold); 

  if (pulseSensor.begin()) {
    SwSerial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
  
  timer.setInterval(1000L, sendSensor);
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    SwSerial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);


  // Pulse

  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 
                                        
  if(isnan(myBPM)) {
    SwSerial.println("Failed to read from HeartBeat Sensor!");
    return;
  }  
  Blynk.virtualWrite(V0, myBPM); 
  delay(20);     

   //   GPS

  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      //Serial.print(c);
      if (gps.encode(c)) 
        newData = true;  
    }
  }
int index = 1;
    float flat, flon;
    unsigned long age;
    if (newData)      //If newData is true
  {
    gps.f_get_position(&flat, &flon, &age);   
  }
    if(isnan(flat) || isnan(flon)) {
    SwSerial.println("Failed to read from GPS Module!");
    return;
  }  
    /*Blynk.virtualWrite(V1, flat);
    Blynk.virtualWrite(V2, flon);*/
    myMap.location(index, flat, flon, "value");
}


void loop() {
  Blynk.run();
  timer.run();
}
