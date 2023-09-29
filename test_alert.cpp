
#include "typewise-alert.h"

#include "gtest/gtest.h"


// Test cases for inferBreach function
TEST(TypewiseAlert, InferBreachAsPerLimits) {
  ASSERT_EQ(inferBreach(12.0, 20.0, 30.0), TOO_LOW);
  ASSERT_EQ(inferBreach(25.0, 20.0, 30.0), NORMAL);
  ASSERT_EQ(inferBreach(35.0, 20.0, 30.0), NORMAL);
  ASSERT_EQ(inferBreach(40.0, 20.0, 30.0), TOO_HIGH);
}

// Test cases for classifyTemperatureBreach function
TEST(TypewiseAlert, ClassifyTemperatureBreach) {
  ASSERT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 25.0), NORMAL);
  ASSERT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50.0), TOO_HIGH);
  ASSERT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 35.0), NORMAL);
}

// Test cases for checkAndAlert function
TEST(TypewiseAlert, CheckAndAlertToController) {
  EquipmentCharacter char1 = {PASSIVE_COOLING, "Brand1"};
  EquipmentCharacter char2 = {HI_ACTIVE_COOLING, "Brand2"};
  
  // Test for alerting to controller
  ASSERT_NO_FATAL_FAILURE(checkAndAlert(TO_CONTROLLER, char1, 25.0));
  ASSERT_NO_FATAL_FAILURE(checkAndAlert(TO_CONTROLLER, char2, 50.0));
}

TEST(TypewiseAlert, CheckAndAlertToEmail) {
  EquipmentCharacter char1 = {PASSIVE_COOLING, "Brand1"};
  EquipmentCharacter char2 = {HI_ACTIVE_COOLING, "Brand2"};
  
  // Test for alerting via email
  ASSERT_NO_FATAL_FAILURE(checkAndAlert(TO_EMAIL, char1, 15.0));
  ASSERT_NO_FATAL_FAILURE(checkAndAlert(TO_EMAIL, char2, 55.0));
}

// Test cases for sendToController function
TEST(TypewiseAlert, SendToController) {
  ASSERT_NO_FATAL_FAILURE(sendToController(TOO_LOW));
  ASSERT_NO_FATAL_FAILURE(sendToController(TOO_HIGH));
  ASSERT_NO_FATAL_FAILURE(sendToController(NORMAL));
}

// Test cases for sendToEmail function
TEST(TypewiseAlert, SendToEmail) {
  ASSERT_NO_FATAL_FAILURE(sendToEmail(TOO_LOW));
  ASSERT_NO_FATAL_FAILURE(sendToEmail(TOO_HIGH));
  ASSERT_NO_FATAL_FAILURE(sendToEmail(NORMAL));
}
