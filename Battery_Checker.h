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

#define TOLERANCE_PERCENTAGE           5
#define TEMP_LOW_LIMIT                 (float)0
#define TEMP_HIGH_LIMIT                (float)45
#define TEMP_TOLERANCE_LIMIT           (float)((TEMP_HIGH_LIMIT * TOLERANCE_PERCENTAGE)/100)
#define TEMP_LOW_BREACH_LOWLIMIT       (float)-30
#define TEMP_LOW_BREACH_HIGHLIMIT      (float)(TEMP_LOW_LIMIT)
#define TEMP_LOW_WARNING_LOWLIMIT      (float)(TEMP_LOW_LIMIT + 0.56)
#define TEMP_LOW_WARNING_HIGHLIMIT     (float)(TEMP_LOW_LIMIT + TEMP_TOLERANCE_LIMIT)
#define TEMP_NORMAL_LOWLIMIT           (float)(TEMP_LOW_WARNING_HIGHLIMIT + 0.56)
#define TEMP_HIGH_WARNING_LOWLIMIT     (float)(TEMP_HIGH_LIMIT - TEMP_TOLERANCE_LIMIT)
#define TEMP_NORMAL_HIGHLIMIT          (float)(TEMP_HIGH_WARNING_LOWLIMIT - 0.56)
#define TEMP_HIGH_WARNING_HIGHLIMIT    (float)(TEMP_HIGH_LIMIT)
#define TEMP_HIGH_BREACH_LOWLIMIT      (float)(TEMP_HIGH_LIMIT + 0.56)
#define TEMP_HIGH_BREACH_HIGHLIMIT     (float)63

#define SOC_LOW_LIMIT                  (float)20
#define SOC_HIGH_LIMIT                 (float)80
#define SOC_TOLERANCE_LIMIT            (float)((SOC_HIGH_LIMIT * TOLERANCE_PERCENTAGE)/100)
#define SOC_LOW_BREACH_LOWLIMIT        (float)0
#define SOC_LOW_BREACH_HIGHLIMIT       (float)(SOC_LOW_LIMIT)
#define SOC_LOW_WARNING_LOWLIMIT       (float)(SOC_LOW_LIMIT + 1)
#define SOC_LOW_WARNING_HIGHLIMIT      (float)(SOC_LOW_LIMIT + SOC_TOLERANCE_LIMIT)
#define SOC_NORMAL_LOWLIMIT            (float)(SOC_LOW_WARNING_HIGHLIMIT + 1)
#define SOC_HIGH_WARNING_LOWLIMIT      (float)(SOC_HIGH_LIMIT - SOC_TOLERANCE_LIMIT)
#define SOC_NORMAL_HIGHLIMIT           (float)(SOC_HIGH_WARNING_LOWLIMIT - 1)
#define SOC_HIGH_WARNING_HIGHLIMIT     (float)(SOC_HIGH_LIMIT)
#define SOC_HIGH_BREACH_LOWLIMIT       (float)(SOC_HIGH_LIMIT + 1)
#define SOC_HIGH_BREACH_HIGHLIMIT      (float)100

#define CR_LOW_LIMIT                   (float)0.8
#define CR_HIGH_LIMIT                  (float)1.0
#define CR_TOLERANCE_LIMIT             (float)(CR_HIGH_LIMIT * TOLERANCE_PERCENTAGE)/100
#define CR_LOW_BREACH_LOWLIMIT         (float)0
#define CR_LOW_BREACH_HIGHLIMIT        (float)(CR_LOW_LIMIT)
#define CR_LOW_WARNING_LOWLIMIT        (float)(CR_LOW_LIMIT + 0.125)
#define CR_LOW_WARNING_HIGHLIMIT       (float)(CR_LOW_LIMIT + CR_TOLERANCE_LIMIT)
#define CR_NORMAL_LOWLIMIT             (float)(CR_LOW_WARNING_HIGHLIMIT + 0.125)
#define CR_HIGH_WARNING_LOWLIMIT       (float)(CR_HIGH_LIMIT - CR_TOLERANCE_LIMIT)
#define CR_NORMAL_HIGHLIMIT            (float)(CR_HIGH_WARNING_LOWLIMIT - 0.125)
#define CR_HIGH_WARNING_HIGHLIMIT      (float)(CR_HIGH_LIMIT)
#define CR_HIGH_BREACH_LOWLIMIT        (float)(CR_HIGH_LIMIT + 0.125)
#define CR_HIGH_BREACH_HIGHLIMIT       (float)1.2

float bmsFactorRanges[15][2]={
/*Temperature*/
   /* Low Breach */
   {TEMP_LOW_BREACH_LOWLIMIT, TEMP_LOW_BREACH_HIGHLIMIT},
   /* Low Warning */
   {TEMP_LOW_WARNING_LOWLIMIT, TEMP_LOW_WARNING_HIGHLIMIT},
   /* Normal Range */
   {TEMP_NORMAL_LOWLIMIT, TEMP_NORMAL_HIGHLIMIT},
   /* High Warning */
   {TEMP_HIGH_WARNING_LOWLIMIT, TEMP_HIGH_WARNING_HIGHLIMIT},
   /* Hign Breach */
   {TEMP_HIGH_BREACH_LOWLIMIT, TEMP_HIGH_BREACH_HIGHLIMIT},

/*SOC*/
   /* Low Breach */
   {SOC_LOW_BREACH_LOWLIMIT, SOC_LOW_BREACH_HIGHLIMIT},
   /* Low Warning */
   {SOC_LOW_WARNING_LOWLIMIT, SOC_LOW_WARNING_HIGHLIMIT},
   /* Normal Range */
   {SOC_NORMAL_LOWLIMIT, SOC_NORMAL_HIGHLIMIT},
   /* High Warning */
   {SOC_HIGH_WARNING_LOWLIMIT, SOC_HIGH_WARNING_HIGHLIMIT},
   /* Hign Breach */
   {SOC_HIGH_BREACH_LOWLIMIT, SOC_HIGH_BREACH_HIGHLIMIT},

/*Charge Rate*/
   /* Low Breach */
   {CR_LOW_BREACH_LOWLIMIT, CR_LOW_BREACH_HIGHLIMIT},
   /* Low Warning */
   {CR_LOW_WARNING_LOWLIMIT, CR_LOW_WARNING_HIGHLIMIT},
   /* Normal Range */
   {CR_NORMAL_LOWLIMIT, CR_NORMAL_HIGHLIMIT},
   /* High Warning */
   {CR_HIGH_WARNING_LOWLIMIT, CR_HIGH_WARNING_HIGHLIMIT},
   /* Hign Breach */
   {CR_HIGH_BREACH_LOWLIMIT, CR_HIGH_BREACH_HIGHLIMIT},
};

#define MSG_LOW_BREACH     "Error: Complete Low"
#define MSG_LOW_WARNING    "Warning: Approaching Low"
#define MSG_NORMAL_STATE   "OK: Normal"
#define MSG_HIGH_WARNING   "Warning: Approaching peak"
#define MSG_HIGH_BREACH    "Error: Peaked"
#define MSG_OUT_OF_BOX     "Error: Value out of range"

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
    int checkResult = OK;                                          \
    if (ISLOWLIMITBREACH(currentValue, currentFactor)) {           \
        THROW_WARNING(LOW_BREACH, currentFactor);                  \
        checkResult = NOT_OK;                                      \
    } else if(ISLOWLIMITWARNING(currentValue, currentFactor)) {    \
        THROW_WARNING(LOW_WARNING, currentFactor);                 \
        checkResult &= OK;                                         \
    } else if(ISNORMALLIMIT(currentValue, currentFactor)) {        \
        THROW_WARNING(NORMAL_STATE, currentFactor);                \
        checkResult &= OK;                                         \
    } else if(ISHIGHLIMITWARNING(currentValue, currentFactor)) {   \
        THROW_WARNING(HIGH_WARNING, currentFactor);                \
        checkResult &= OK;                                         \
    } else if(ISHIGHLIMITBREACH(currentValue, currentFactor)) {    \
        THROW_WARNING(HIGH_BREACH, currentFactor);                 \
        checkResult &= NOT_OK;                                     \
    } else {                                                       \
        THROW_WARNING(OUT_OF_BOX, currentFactor);                  \
        checkResult &= NOT_OK;                                     \
    }                                                              \
    checkResult;                                                   \
})
