#include <ThingerESP32.h>

#define USERNAME "hazem.thecla.ht@gmail.com"
#define DEVICE_ID "nodeMCU"
#define DEVICE_CREDENTIAL "xRGQ@4uu6niCtB"

#define SSID "Jo"
#define SSID_PASSWORD "1234567890joker"

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(LED_BUILTIN);

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
}
