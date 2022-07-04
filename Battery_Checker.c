#include "Battery_Checker.h"

int isTemperatureOK(float temperature) {
  return checkOK(temperature, 0, 45);
}

int isSOCOK(float soc) {
  return checkOK(soc, 20, 80);
}

int isChargeRateOK(float chargeRate) {
  return checkOK(chargeRate, 0.8, 1);
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
 return isTemperatureOK(temperature) && isSOCOK(soc) && isChargeRateOK(chargeRate);
}

int main() {
  assert(batteryIsOk(25, 70, 0.9));
  assert(batteryIsOk(50, 80, 0));
}
