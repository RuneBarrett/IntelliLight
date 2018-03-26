#define FASTLED_ALLOW_INTERRUPTS 0
#include "FastLED.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Counter.h>
#include <ArduinoJson.h>

//wifi
char ssid[] = "..."; //SSID of your Wi-Fi router
char pass[] = "..."; //Password of your Wi-Fi router

//mqtt
#define mqtt_server "192.168.1.175"
#define mqtt_user "" //user+pass only needed if the mqtt server requires it. 
#define mqtt_password ""

//mqtt client
WiFiClient espClient;
PubSubClient client(espClient); 

//leds
#define DATA_PIN D2
#define NUM_LEDS 46
CRGB leds[NUM_LEDS];
CRGB last_leds[NUM_LEDS];
CHSV mainColor(180, 100, 200);

//webservices
float lati = 51.5033640;
float longti = -0.1276250;
String response;

//An amount of counter objects that run between 0 and 255 in different speeds. Defined in the Counter.h library
const int counterAmount = 10;
Counter counters[counterAmount];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(115200);//9600

  connect_wifi();
  connect_mqtt();
  initCounters();
}

void loop() {
  // The main state loop manages solid full lamp light (normal livingroom / party / movie etc.)
  stateLoop();
  
  webserviceLoop(); // Manage webservice changes and input from connected sensors
  sensorLoop();
  
  alertLoop();// The alert loop overwrites some, but not all, led-settings from the main state loop (someone at the door, its raining, train is late etc)
  showLeds(); // Only address the leds if any changes has been made
  utilityLoops(); // Background stuff such as listening for mqtt, running counters, keeping connection up etc.
}







