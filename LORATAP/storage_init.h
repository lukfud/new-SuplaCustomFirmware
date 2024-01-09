#ifndef STORAGE_INIT_H_
#define STORAGE_INIT_H_

Supla::Storage::Init();

auto cfg = Supla::Storage::ConfigInstance();

//--------------------------------- 80 signs ---------------------------------|
//                                                                         name
if (cfg->getString(DEV_NAME, devName, 30)) {
  SUPLA_LOG_DEBUG("# Param[%s]: %s", DEV_NAME, devName);
} else {
  SUPLA_LOG_DEBUG("# Param[%s] is not set", DEV_NAME);
}
//--------------------------------- 80 signs ---------------------------------|
//                                                                         mode
if (cfg->getUInt32(SELECT_MODE, &selectMode)) {
  SUPLA_LOG_DEBUG("# Param[%s]: %d", SELECT_MODE, selectMode);
} else {
  SUPLA_LOG_DEBUG("# Param[%s] is not set", SELECT_MODE);
}

if (cfg->getUInt32(COMFORT_UP, &comfortUpState)) {
  if (comfortUpState < 0 || comfortUpState > 100) {
    comfortUpState = 25;
  }
  cfg->setUInt32(COMFORT_UP, comfortUpState);
  SUPLA_LOG_DEBUG("# Param[%s]: %d", COMFORT_UP, comfortUpState);
} else {
  SUPLA_LOG_DEBUG("# Param[%s] is not set", COMFORT_UP);
}

if (cfg->getUInt32(COMFORT_DOWN, &comfortDownState)) {
  if (comfortDownState < 0 || comfortDownState > 100) {
    comfortDownState = 75;
  }
  cfg->setUInt32(COMFORT_DOWN, comfortDownState);
  SUPLA_LOG_DEBUG("# Param[%s]: %d", COMFORT_DOWN, comfortDownState);
} else {
  SUPLA_LOG_DEBUG("# Param[%s] is not set", COMFORT_DOWN);
}

for (int i = 0; i < 2; i++) {
  char tagStateBuf[15];
  snprintf(tagStateBuf, sizeof(tagStateBuf), "%d_rel_state", i+1);
  if (cfg->getUInt32(tagStateBuf, &relayState[i])) {
    SUPLA_LOG_DEBUG("# Param[%s]: %d", tagStateBuf, relayState[i]);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s] is not set", tagStateBuf);
  }
  char tagStairBuf[15];
  snprintf(tagStairBuf, sizeof(tagStairBuf), "%d_stair_mode", i+1);
  if (cfg->getUInt8(tagStairBuf, &staircaseModeTag[i])) {
    SUPLA_LOG_DEBUG("# Param[%s]: %d", tagStairBuf, staircaseModeTag[i]);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s] is not set", tagStairBuf);
  }
  char fncBuf[15];
  snprintf(fncBuf, sizeof(fncBuf), "%d_fnc", 2*i);
  if (cfg->getInt32(fncBuf, &channelFnc[i])) {
    SUPLA_LOG_DEBUG("# Param[%s]: %d", fncBuf, channelFnc[i]);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s] is not set", fncBuf);
  }
  char tagNoTimerBuf[15];
  snprintf(tagNoTimerBuf, sizeof(tagNoTimerBuf), "%d_no_timer", i+1);
  if (cfg->getUInt32(tagNoTimerBuf, &noTimerOnEvent[i])) {
    SUPLA_LOG_DEBUG("# Param[%s]: %d", tagNoTimerBuf, noTimerOnEvent[i]);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s] is not set", tagNoTimerBuf);
  }
}

#endif