#include <stdio.h>
#include <assert.h>

#define NOT_OK 0
#define OK     1

typedef enum 
{
  TEMPERATURE,
  SOC,
  CHARGE_RATE,
  MAX_FACTORS
}batteryFactor_e;

typedef struct
{
  //int status;
  float minRange;
  float maxRange;
}batteryCheckFactors;

batteryCheckFactors batteryCheck[MAX_FACTORS] = {0};

#define checkOK( currentFactor, currentValue )                 \
({                                                                  \
    int checkResult = NOT_OK;                                       \
    if ( (currentValue < batteryCheck[currentFactor].minRange) && (currentValue > batteryCheck[currentFactor].maxRange)) {  \
        checkResult = OK;                                           \
    }                                                               \
    checkResult;                                                    \
})
