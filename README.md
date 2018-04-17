IntelliLight
======
### An intelligent lighting information system.
In order to use this system you need to add and fill in the following content to a file called *secrets.h*.
This file needs to be placed in your arduino library, in a folder called *secrets*. (You arduino library will usually be placed in *../documents/Arduino/..*)
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
The essential information is wifi credentials, mqtt host adress and your darksky key (obtained from darksky.com). The rest can be used with default values. 
