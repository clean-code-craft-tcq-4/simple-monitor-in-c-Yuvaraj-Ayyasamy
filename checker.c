#include <stdio.h>
#include <assert.h>
int status;
#define NOT_OK 0
#define OK 1
#define checkOK( x, y, z )                            \
({                                                    \
    int result;                                       \
    if ( (x < y) && (x > z)) {                        \
        result = OK;                                  \
    } else {                                          \
        result = NOT_OK;                              \
    }                                                 \
    result;                                           \
})

int isTemperatureOK(float temperature) {
  status = checkOK(temperature, 0, 45);
  return status;
}

int isSOCOK(float soc) {
  status = checkOK(soc, 20, 80);
  return status;
}

int isChargeRateOK(float chargeRate) {
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
