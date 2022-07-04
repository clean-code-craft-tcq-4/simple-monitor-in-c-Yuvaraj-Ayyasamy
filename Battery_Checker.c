#include "Battery_Checker.h"

void updateBatteryStatus_ParameterRange(void){
  //batteryCheck[TEMPERATURE].bms_Parameter.status = {FALSE, 0, 45};
  batteryCheck[TEMPERATURE].minRange = 0;
  batteryCheck[TEMPERATURE].maxRange = 45;
  
  //batteryCheck[SOC].bms_Parameter = FALSE;
  batteryCheck[SOC].minRange = 20;
  batteryCheck[SOC].maxRange = 80;
  
  //batteryCheck[CHARGE_RATE].bms_Parameter = FALSE;  
  batteryCheck[CHARGE_RATE].minRange = 0.8;  
  batteryCheck[CHARGE_RATE].maxRange = 1;
}

/*int isTemperatureOK(float temperature) {
  return checkOK(temperature, 0, 45);
}

int isSOCOK(float soc) {
  return checkOK(soc, 20, 80);
}

int isChargeRateOK(float chargeRate) {
  return checkOK(chargeRate, 1, 0.8);
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
 return isTemperatureOK(temperature) && isSOCOK(soc) && isChargeRateOK(chargeRate);
}*/

int batteryIsOk(float temperature, float soc, float chargeRate) {
   return checkOK(TEMPERATURE, temperature) && checkOK(SOC, soc) && checkOK(CHARGE_RATE, chargeRate);
}

int main() {
  updateBatteryStatus_ParameterRange();
  assert(!batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
