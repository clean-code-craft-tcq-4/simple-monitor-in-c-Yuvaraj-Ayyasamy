#include "Battery_Checker.h"

void updateBatteryFactorsRange() {
  battery_checkcase[TEMPERATURE].checkStatus = NOT_OK;
  battery_checkcase[TEMPERATURE].minRange = 0;
  battery_checkcase[TEMPERATURE].maxRange = 45;
  
  battery_checkcase[SOC].checkStatus = NOT_OK;
  battery_checkcase[SOC].minRange = 20;
  battery_checkcase[SOC].maxRange = 80;
  
  battery_checkcase[CHARGE_RATE].checkStatus = NOT_OK;  
  battery_checkcase[CHARGE_RATE].minRange = 0.8;  
  battery_checkcase[CHARGE_RATE].maxRange = 1; 
}
