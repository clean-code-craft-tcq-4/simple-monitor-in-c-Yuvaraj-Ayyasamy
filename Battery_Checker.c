#include "Battery_Checker.h"

int isTemperatureOK(float temperature) {
  return checkOK(temperature, );
}

int isSOCOK(float soc) {
  return checkOK(soc, );
}

int isChargeRateOK(float chargeRate) {
  return checkOK(chargeRate, );
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
 return isTemperatureOK(temperature) && isSOCOK(soc) && isChargeRateOK(chargeRate);
}

int main() {
  updateBatteryFactorsRange();
  assert(!batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
