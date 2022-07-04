#include <stdio.h>
#include <assert.h>

#define NOT_OK 0
#define OK     1

typedef enum 
{
  TEMPERATURE = 0,
  SOC,
  CHARGE_RATE,
}batteryFactors_e;

typedef struct
{
  int checkStatus;
  float minRange;
  float maxRange;
}batteryFactorsRange;

batteryFactorsRange batteryFactorStatus[3];

#define checkOK( currentValue, batteryFactor )                 \
({                                                                  \
    if ( (currentValue < batteryFactorStatus[batteryFactor].minRange) && (currentValue > batteryFactorStatus[batteryFactor].maxRange)) {  \
        batteryFactorStatus[batteryFactor].checkStatus = OK;                                           \
    }                                                               \
})

/*#define checkOK( currentValue, batteryFactor)                           \
({                                                                            \
    ((currentValue < minRange) && (currentValue > maxRange)) ? OK : NOT_OK;   \
})*/

/* #define checkOK( currentValue, minRange, maxRange )                 \
({                                                                  \
    int checkResult = NOT_OK;                                       \
    if ( (currentValue < minRange) && (currentValue > maxRange)) {  \
        checkResult = OK;                                           \
    }                                                               \
    checkResult;                                                    \
})*/
