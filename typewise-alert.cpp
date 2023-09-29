#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  int upperLimit = 0;
  if (coolingType == PASSIVE_COOLING) {
    upperLimit = 35;
  } else if (coolingType == HI_ACTIVE_COOLING) {
    upperLimit = 45;
  } else if (coolingType == MED_ACTIVE_COOLING) {
    upperLimit = 40;
  }
  return inferBreach(temperatureInC, 0, upperLimit);
}


void checkAndAlert(AlertTarget alertTarget, EquipmentCharacter characteristic, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(characteristic.coolingType, temperatureInC);

  if (alertTarget == TO_CONTROLLER) {
    sendToController(breachType);
  } else if (alertTarget == TO_EMAIL) {
    sendToEmail(breachType);
  }
}


void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
