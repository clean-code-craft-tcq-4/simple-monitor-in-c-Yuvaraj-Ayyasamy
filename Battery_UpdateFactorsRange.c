#include "Battery_Checker.h"

void updateBatteryFactorsRange() {
  batteryFactorStatus[TEMPERATURE].checkStatus = NOT_OK;
  batteryFactorStatus[TEMPERATURE].minRange = 0;
  batteryFactorStatus[TEMPERATURE].maxRange = 45;
  
  batteryFactorStatus[SOC].checkStatus = NOT_OK;
  batteryFactorStatus[SOC].minRange = 20;
  batteryFactorStatus[SOC].maxRange = 80;
  
  batteryFactorStatus[CHARGE_RATE].checkStatus = NOT_OK;  
  batteryFactorStatus[CHARGE_RATE].minRange = 0.8;  
  batteryFactorStatus[CHARGE_RATE].maxRange = 1; 
}
