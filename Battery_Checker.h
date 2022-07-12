#include <stdio.h>
#include <assert.h>

#define NOT_OK 0
#define OK     1

char bmsFactors[3][13] = {"TEMPERATURE", "SOC", "CHARGE RATE"};

enum BMSFactor {
    TEMPERATURE = 0,
    SOC,
    CHARGERATE
};

enum BMSValueRange {
 LOW_BREACH = 0,
 LOW_WARNING,
 NORMAL_STATE,
 HIGH_WARNING,
 HIGH_BREACH
};

float bmsFactorRanges[15][2]={
/*Temperature*/
 /*Low Breach   Low Warning   Normal     High Warning   Hign Breach*/
   {-30, -1},    {0, 15},    {16, 30},      {31, 45},     {46, 63}, 

/*SOC*/
 /*Low Breach   Low Warning   Normal     High Warning   Hign Breach*/
   {1, 20},      {21, 24},   {25, 75},     {76, 80},       {81, 100},

/*Charge Rate*/
 /*Low Breach   Low Warning    Normal     High Warning   Hign Breach*/
   {0, 0.7},     {0.8, 0.8}, {0.9, 0.9},   {1.0, 1.0},     {1.1, 1.2},
};

#define MSG_LOW_BREACH     "Error: Complete Low"
#define MSG_LOW_WARNING    "Warning: Approaching Low"
#define MSG_NORMAL_STATE   "OK: Normal"
#define MSG_HIGH_WARNING   "Warning: Approaching peak"
#define MSG_HIGH_BREACH    "Error: Peaked"

#define Print(message) MSG_##message              

#define THROW_WARNING(message, currentFactor) printf("%s: %s\n", bmsFactors[currentFactor], Print(message));

#define ISLOWLIMITBREACH(currentValue, currentFactor)                                                      \
({                                                                                                         \
    int checkResult = (int)((currentValue >= bmsFactorRanges[(currentFactor*5)+LOW_BREACH][0])             \
                           && (currentValue <= bmsFactorRanges[(currentFactor*5)+LOW_BREACH][1]));         \
    checkResult;                                                                                           \
})

#define ISLOWLIMITWARNING(currentValue, currentFactor)                                                      \
({                                                                                                          \
    int checkResult = (int)((currentValue >= bmsFactorRanges[(currentFactor*5)+LOW_WARNING][0])             \
                           && (currentValue <= bmsFactorRanges[(currentFactor*5)+LOW_WARNING][1]));         \
    checkResult;                                                                                            \
})

#define ISNORMALLIMIT(currentValue, currentFactor)                                                          \
({                                                                                                          \
    int checkResult = (int)((currentValue >= bmsFactorRanges[(currentFactor*5)+NORMAL_STATE][0])            \
                           && (currentValue <= bmsFactorRanges[(currentFactor*5)+NORMAL_STATE][1]));        \
    checkResult;                                                                                            \
})

#define ISHIGHLIMITWARNING(currentValue, currentFactor)                                                     \
({                                                                                                          \
    int checkResult = (int)((currentValue >= bmsFactorRanges[(currentFactor*5)+HIGH_WARNING][0])            \
                           && (currentValue <= bmsFactorRanges[(currentFactor*5)+HIGH_WARNING][1]));        \
    checkResult;                                                                                            \
})

#define ISHIGHLIMITBREACH(currentValue, currentFactor)                                                      \
({                                                                                                          \
    int checkResult = (int)((currentValue >= bmsFactorRanges[(currentFactor*5)+HIGH_BREACH][0])             \
                           && (currentValue <= bmsFactorRanges[(currentFactor*5)+HIGH_BREACH][1]));         \
    checkResult;                                                                                            \
})

#define checkOK(currentValue, currentFactor)                       \
({                                                                 \
    int checkResult = NOT_OK;                                      \
    if (ISLOWLIMITBREACH(currentValue, currentFactor)) {           \
        THROW_WARNING(LOW_BREACH, currentFactor);                  \
        checkResult = OK;                                          \
    }                                                              \
    if(ISLOWLIMITWARNING(currentValue, currentFactor)) {           \
        THROW_WARNING(LOW_WARNING, currentFactor);                 \
        checkResult &= OK;                                         \
    }                                                              \
    if(ISNORMALLIMIT(currentValue, currentFactor)) {               \
        THROW_WARNING(NORMAL_STATE, currentFactor);                \
        checkResult &= OK;                                         \
    }                                                              \
    if(ISHIGHLIMITWARNING(currentValue, currentFactor)) {          \
        THROW_WARNING(HIGH_WARNING, currentFactor);                \
        checkResult &= OK;                                         \
    }                                                              \
    if(ISHIGHLIMITBREACH(currentValue, currentFactor)) {           \
        THROW_WARNING(HIGH_BREACH, currentFactor);                 \
        checkResult &= OK;                                         \
    }                                                              \
    checkResult;                                                   \
})
