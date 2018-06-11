IntelliLight
======
An intelligent lighting information system.
------
Description will arrive shortly

Setup Instructions
------
### Needed parts and software
1. The Arduino IDE with the ESP8266 addon. Install Arduino and follow these steps if you dont have it already: https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/installing-the-esp8266-arduino-addon

2. An ESP8266 (any should do)
3. A bunch of adressable LED's compatible with the FastLED library (most lightpatterns are currently hardcoded to 46 leds organized in rows of 20, 16, 9, 1)
4. Something to stick your LED's on. (Inside an old lamp, the backside of a screen, the inside of your motorcycle helmet(not recommended) or wherever you would like them.)

### Creating *secrets.h*
In order to use this system you need to add and fill in the following content to a file called *secrets.h*.
This file needs to be placed in your arduino library, in a folder called *secrets*. (You arduino library will usually be placed in *../Documents/Arduino/libraries*)
```c
//WIFI credentials
#define WIFI_PASSWORD "..."
#define WIFI_UNAME "..."

//MQTT credentials
#define MQTT_SERVER "192.168.1...."
#define MQTT_USER "" //user+pass only needed if the mqtt server requires it.
#define MQTT_PASSWORD ""

//Information for DarkSky requests
#define DARK_KEY "c6a779..."
#define LATI 55.414403// change to match your location
#define LONGTI 12.149739

// -------- Timers --------
//Webrequest
#define WEB_REQ_INTERVAL 900     //How often to collect new weather information (max 1000 free a day) - Defined in seconds (900 -> 15 minutes)

//Weather
#define FORECAST_TIME 60         //How long into the future should we look - Defined in minutes.
#define WEATHER_INTERVAL 20      //How often to go into weather mode - Defined in seconds
#define SHOW_WEATHER_TIME 10     //How long time the weather mode shows - Defined in seconds
#define TEMP_WARM 22             //How many degrees celcius till you definite dont need a jacket to go outside
#define TEMP_COLD 8              //How many degrees celcius till you definite do need a jacket to go outside
```
The essential information you need to fill out is **wifi credentials**, **mqtt host address** and your **darksky key** (obtained from https://darksky.net/dev). The rest can be used with default values.
### Required libraries
These libraries can be installed using the *Arduino Library Manager*.
1. **FastLED** - for contolling the LED's
2. **ESP8266HTTPClient** - For sending web requests
3. **PubSubClient** - for MQTT publishing/subscribing
4. **ArduinoJson** - for working with json responses from webservices
5. **NTPClient** - For getting accurate time from an NTP server
6. **WiFiUdp** - For sending UDP requests

The following libraries are found elsewhere, or created by yourself.

1. **Counter** - Fluctuating counters used for easially making complex LED patterns
  * Download ZIP from this link, place it in your arduino libraries folder and use the *extract here* option (not *extract to*): https://runebarrett.github.io/DownGit/#/home?repo=https://github.com/RuneBarrett/Fluctuating-Counters/tree/master&paths=Counter.h|Counter.cpp&subfolder=Counter
- Note: You can delete the ZIP file after the above step.

2. **Secrets** - Holds your credentials and settings
  * Created by you (see the *creating secrets.h* section in *README.md*)

### Soldering of the neopixels** - Heres two images to help with the soldering of the neopixels and wemos board 
![alt text](http://i36.photobucket.com/albums/e44/kcschou/Intellilight_bb_zpssmg0mtdz.png)
![alt text](http://i36.photobucket.com/albums/e44/kcschou/Intellilight_schem_zpso60ljxor.png)
