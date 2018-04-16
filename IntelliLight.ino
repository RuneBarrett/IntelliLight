/* 
 *  Intelligent Ambient Light System 
 *  !!! SEE README FOR CREDENTIAL SETUP !!! 
 *  MIT licence bla bla legal stuff. Dont be a dick.
 */
 
#define FASTLED_ALLOW_INTERRUPTS 0
#include "FastLED.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>
#include <Counter.h>
#include <ArduinoJson.h>
#include <secrets.h>
#include <NTPClient.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

//wifi
ESP8266WiFiMulti wifiMulti;
char ssid[] = WIFI_UNAME; //SSID of your Wi-Fi router
char pass[] = WIFI_PASSWORD;//Password of your Wi-Fi router

//mqtt
char mqtt_server[] = MQTT_SERVER;
char mqtt_user[] = MQTT_USER; //user+pass only needed if the mqtt server requires it. 
char mqtt_password[] = MQTT_PASSWORD;

//mqtt client
WiFiClient espClient;
PubSubClient client(espClient);

//leds
#define DATA_PIN D2
#define NUM_LEDS 46
CRGB leds[NUM_LEDS];
CRGB last_leds[NUM_LEDS];
CHSV mainColor(180, 100, 160);

//webservices
String dark_key = DARK_KEY;
float lati = LATI;
float longti = LONGTI;
String response;

//NTP 
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String formatedTime;

//An amount of counter objects that run between 0 and 255 in different speeds. Defined in the Counter.h library
const int counterAmount = 10;
Counter counters[counterAmount];

//Web request timing
unsigned long timer = 0;

//Variables for storing weather data
char* currently_precipType;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(115200);

  wifiMulti.addAP(ssid, pass);
  connect_wifi_multi();
  connect_mqtt();
  initCounters();
  timeClient.begin();
}

void loop() {
  timeClient.update();
  //Serial.println(timeClient.getFormattedTime());
  formatedTime = timeClient.getFormattedTime();
  stateLoop();   // The main state loop manages solid full lamp light (normal livingroom / party / movie etc.)
  webserviceLoop(); // Manage webservice changes and input from connected sensors, used for "alerts"
  alertLoop();// The alert loop overwrites some, but not all, led-settings from the main state loop (someone at the door, its raining, train is late etc)

  showLeds(); // Only address the leds if any changes has been made
  utilityLoops(); // Background stuff such as listening for mqtt, running counters, keeping connection up etc.
}
