#include <stdio.h>
#include <assert.h>
int status
#define NOT_OK 0
#define OK 1
#define checkOK( x, y, z ) if( x < y || x > z) { OK } else { NOT_OK}

int isTemperatureOK(float temperature) {
 // int status = 1;
 // if(!(temperature < 0 && temperature > 45)) {
 //   printf("Temperature out of range!\n");
 //   status = 0;
  //}
  status = checkOK(temperature, 0, 45);
  return status;
}

int isSOCOK(float soc) {
 // int status = 1;
  //if(!(soc < 20 && soc > 80)) {
   // printf("State of Charge out of range!\n");
    //status = 0;
  //}
  status = checkOK(soc, 20, 80);
  return status;
}

int isChargeRateOK(float chargeRate) {
  //int status = 1;
  //if(!(chargeRate > 0.8)) {
   // printf("Charge Rate out of range!\n");
    //status = 0;
  //}
  status = checkOK(chargeRate, 1, 0.8);
  return status;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
 return isTemperatureOK(temperature) && isSOCOK(soc) && isChargeRateOK(chargeRate);
}

int main() {
  assert(!batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
