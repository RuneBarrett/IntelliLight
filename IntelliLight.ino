#define FASTLED_ALLOW_INTERRUPTS 0
#include "FastLED.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>
#include <Counter.h>
#include <ArduinoJson.h>
#include <secrets.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

/*
    Intelligent Ambient Light Information System
    !!! SEE README FOR SETUP !!!

    This is the main program file. Contains all global variables, the setup method and the main loop.
    Arduino treats all files as if they were one - thus, the file separation based on respective responsibilities and is purely for improving readability. 
    All global variables are defined in this main file but can be referenced anywhere due to the single file treatment mentioned above. 
*/

//wifi
ESP8266WiFiMulti wifiMulti;
char ssid[] = WIFI_UNAME; //SSID of your Wi-Fi router
char pass[] = WIFI_PASSWORD;//Password of your Wi-Fi router

//mqtt credentials
char mqtt_server[] = MQTT_SERVER;
char mqtt_user[] = MQTT_USER; //user+pass only needed if the mqtt server requires it.
char mqtt_password[] = MQTT_PASSWORD;


//mqtt client
WiFiClient espClient;
PubSubClient client(espClient);

//NTP (time)
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String unixTime;

//leds
#define DATA_PIN D2
#define NUM_LEDS 46
CRGB leds[NUM_LEDS];
CRGB last_leds[NUM_LEDS];
//CHSV mainColor(180, 100, 160);255, 241, 224
CHSV mainColor(0, 30, 255);
//webservices
String dark_key = DARK_KEY;
float lati = LATI;
float longti = LONGTI;
String response;

//An amount of counter objects that run between 0 and 255 in different speeds. Defined in the Counter.h library
const int counterAmount = 10;
Counter counters[counterAmount];

//Timers
unsigned long webserviceTimer = WEB_REQ_INTERVAL * 1000;
unsigned long lightTimer = LIGHT_INTERVAL * 1000 ;
unsigned long fadeTimer = FADE_TIME * 1000;

//Variables for storing weather data
char* currently_precipType;

boolean fading = false;


void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(115200);
  wifiMulti.addAP(ssid, pass);
  connect_wifi_multi();
  connect_mqtt();
  initCounters();
  timeClient.begin();
  timeClient.update(); //calling an update here seems to provide the right time for the first request sent when the program starts
}

void loop() {
  timeClient.update(); //Collects and updates the current time from an NTP server at set time intervals

  stateLoop();   // The main state loop manages solid full lamp light (normal livingroom / party / movie etc.)
  webserviceLoop(); // Manage webservice changes and potentially input from connected sensors, used for "alerts"
  alertLoop();// The alert loop overwrites some, but not all, led-settings from the main state loop (someone at the door, its raining, train is late etc)

  showLeds(); // Only address the leds if any changes has been made
  utilityLoops(); // Background stuff such as listening for mqtt, running counters, keeping connection up etc.
}
