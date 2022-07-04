#include "Battery_Checker.h"

int isTemperatureOK(float temperature) {
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
}

int main() {
  updateBatteryStatus_ParameterRange();
  assert(!batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}