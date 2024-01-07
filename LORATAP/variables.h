#ifndef VARIABLES_H_
#define VARIABLES_H_
//--------------------------------- 80 signs ---------------------------------|
//                                                                         Core
const char DEV_NAME[] = "dev_name";
char devName[30] = {};
const char SELECT_MODE[] = "select_mode";
uint32_t selectMode = 0;
uint32_t relayState[2] = {};
const char COMFORT_UP[] = "comfort_up";
uint32_t comfortUpState = 25;
const char COMFORT_DOWN[] = "comfort_down";
uint32_t comfortDownState = 75;
uint8_t staircaseTag[2] = {0,0};
uint8_t isStaircase[2] = {0,0};

int relayPin[2] = {RELAY_1, RELAY_2};
int buttonPin[2] = {BUTTON_1, BUTTON_2};
bool pressed = false;

#endif