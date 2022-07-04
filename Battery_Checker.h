#include <stdio.h>
#include <assert.h>

#define NOT_OK 0
#define OK     1

int status;

#define checkOK( currentValue, minRange, maxRange )                 \
({                                                                  \
    int CheckResult = NOT_OK;                                       \
    if ( (currentValue < minRange) && (currentValue > maxRange)) {  \
        result = OK;                                                \
    }                                                               \
    CheckResult;                                                    \
})
