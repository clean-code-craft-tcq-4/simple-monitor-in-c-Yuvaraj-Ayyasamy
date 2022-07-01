#include <stdio.h>
#include <assert.h>

int isTemperatureOK(float temperature) {
  int status = 1;
  if(!(temperature < 0 && temperature > 45)) {
    printf("Temperature out of range!\n");
    status = 0;
  }
  return status;
}

int isSOCOK(float soc) {
  int status = 1;
  if(!(soc < 20 && soc > 80)) {
    printf("State of Charge out of range!\n");
    status = 0;
  }
  return status;
}

int isChargeRateOK(float chargeRate) {
  int status = 1;
  if(!(chargeRate > 0.8)) {
    printf("Charge Rate out of range!\n");
    status = 0;
  }
  return status;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
 return isTemperatureOK(temperature) && isSOCOK(soc) && isChargeRateOK(chargeRate);
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
