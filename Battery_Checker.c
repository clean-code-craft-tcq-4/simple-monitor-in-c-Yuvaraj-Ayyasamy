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
  /* All Temp, SOC & Charge Rate values are inside range */
  assert(batteryIsOk(25, 70, 0.9));
  
  /* Only Temp value outside range */
  assert(!batteryIsOk(50, 70, 0.9));
  
    /* Only SOC value outside range */
  assert(!batteryIsOk(30, 85, 0.9));
  
    /* Only Charge Rate outside range */
  assert(!batteryIsOk(40, 70, 0.7));
  
  /* All Temp, SOC & Charge Rate values are outside range */
  assert(!batteryIsOk(50, 85, 0));
}
