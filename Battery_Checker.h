#include <stdio.h>
#include <assert.h>

#define NOT_OK 0
#define OK     1

int status;

#define checkOK( CurrentValue, minRange, maxRange )                 \
({                                                                  \
    int result = NOT_OK;                                            \
    if ( (CurrentValue < MinRange) && (CurrentValue > MaxRange)) {  \
        result = OK;                                                \
    }                                                               \
    result;                                                         \
})
