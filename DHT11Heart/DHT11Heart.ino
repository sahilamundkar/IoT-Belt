#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>

#include <SoftwareSerial.h>
SoftwareSerial SwSerial(0, 1); // RX, TX

#include <BlynkSimpleStream.h>

char auth[] = "TnetmtR-wM_J-VpCx7BpmjPnO9Pnf3jE";

#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value.
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
BlynkTimer timer;

void setup() {

  Serial.begin(9600);        
  dht.begin();

  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   
 
   if (pulseSensor.begin()) {
    SwSerial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
  Blynk.begin(Serial, auth);
  
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
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t); 
  
  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 

  if (isnan(myBPM)) {
    SwSerial.println("Failed to read from HeartBeat Sensor!");
    return;
  }                                             
 
  Blynk.virtualWrite(V0, myBPM); 
  delay(20);     

}

void loop() {
  Blynk.run();
  timer.run();

}
