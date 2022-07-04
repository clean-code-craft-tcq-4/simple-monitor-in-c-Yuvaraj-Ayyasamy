#include <stdio.h>
#include <assert.h>

#define NOT_OK 0
#define OK     1

 #define checkOK( currentValue, minRange, maxRange )                 \
({                                                                  \
    int checkResult = NOT_OK;                                       \
    if ( (currentValue > minRange) && (currentValue < maxRange)) {  \
        checkResult = OK;                                           \
    }                                                               \
    checkResult;                                                    \
})
