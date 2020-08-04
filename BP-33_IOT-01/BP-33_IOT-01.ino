#include "BP-33-IOT-01_secrets.h"
#include "BP-33-IOT-01_thing.h"

#include <NodeAP.h>

//extern strSensor SensorVal;
//extern StructAddrConfig AddrConfig;
//extern StructNodeConfig NodeConfig;
//extern char ShowPara[256];

void setup() { 
  Node_AP_Init();

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  TimerInit();
}

void loop() {
  
  //StartToConfig();        //Enter "conf" to config menu
  Routine();
  //WebServerLoop();
  //Mode_Process();

  ArduinoCloud.update();
  onAirTempChange();
//  onAirHumiChange();
  //onSoilHumiChange();
//  onLightChange();
//  onStatusChange();
}

void onSoilHumiDryChange() {
  // Do something
}


void onStatusChange() {
  // Do something
}


void onSwitch1Change() {
  // Do something
}
/*--- ArduinoIoTCloud function ------------------------------*/
void onAirTempChange() {
  airTemp=10; //SensorVal.air_temp;
}
/*
void onAirHumiChange() {
  airHumi = SensorVal.air_hu;
}
*/
/*
void onSoilHumiChange()
{
  soilHumi = SensorVal.soil_hu;
}
*/
/*
void onLightChange()
{
  light = SensorVal.light;
}

void onSwitch1Change(){
}

void onTextChange() {
}

void onStatusChange() {
  status = ShowPara;
}

void onSoilHumiDryChange() {
  NodeConfig.SoilHumiDry = soilHumiDry;
  Serial.println(NodeConfig.SoilHumiDry);

  EEPROM.write(AddrConfig.SoilHumiDry, NodeConfig.SoilHumiDry);
  EEPROM.commit();
}
*/
