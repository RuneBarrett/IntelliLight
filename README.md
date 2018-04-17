IntelliLight
======
An intelligent lighting information system.
------
Description will arrive shortly
### Creating *secrets.h*
In order to use this system you need to add and fill in the following content to a file called *secrets.h*.
This file needs to be placed in your arduino library, in a folder called *secrets*. (You arduino library will usually be placed in *../Documents/Arduino/libraries*)
```c
#define WIFI_PASSWORD "<pwd>"
#define WIFI_UNAME "<uid>"

#define MQTT_SERVER "192.168.1...."
#define MQTT_USER "" //user+pass only needed if the mqtt server requires it.
#define MQTT_PASSWORD ""

#define DARK_KEY "c6a77...."
#define LATI 55.414403// change to match your location
#define LONGTI 12.149739

#define WEB_REQ_INTERVAL 600000
#define LIGHT_INTERVAL 150000
```
The essential information you need to fill out is wifi credentials, mqtt host adress and your darksky key (obtained from darksky.com). The rest can be used with default values. 
### Required libraries
These can be installed using the *Arduino Library Manager*.
1. **FastLED** - for contolling the LED's
2. **ESP8266HTTPClient** - For sending web requests
3. **PubSubClient** - for MQTT publishing/subscribing
4. **ArduinoJson** - for working with json responses from webservices
5. **NTPClient** - For getting accurate time from an NTP server
6. **WiFiUdp** - For sending UDP requests

The following are found elsewhere, or created by yourself.

1. **Counter** - Fluctuating counters used for easially making complex LED patterns
  * Download here: 
2. **Secrets** - Holds your credentials and settings
  * Created by you (see README.md)
