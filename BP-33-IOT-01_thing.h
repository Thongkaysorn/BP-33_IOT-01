#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>


const char THING_ID[] = "182c01ce-ed3a-4a53-b09a-bdcef465152f";

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)

void onStatusChange();
void onSoilHumiDryChange();
void onSwitch1Change();

String status;
CloudTemperature airTemp;
int soilHumiDry;
float light;
float airHumi;
float soilHumi;
bool switch1;

void initProperties(){

  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(status, READWRITE, ON_CHANGE, onStatusChange);
  ArduinoCloud.addProperty(airTemp, READ, 60 * SECONDS, NULL);
  ArduinoCloud.addProperty(soilHumiDry, READWRITE, ON_CHANGE, onSoilHumiDryChange);
  ArduinoCloud.addProperty(light, READ, 60 * SECONDS, NULL);
  ArduinoCloud.addProperty(airHumi, READ, 60 * SECONDS, NULL);
  ArduinoCloud.addProperty(soilHumi, READ, 60 * SECONDS, NULL);
  ArduinoCloud.addProperty(switch1, READWRITE, ON_CHANGE, onSwitch1Change);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
