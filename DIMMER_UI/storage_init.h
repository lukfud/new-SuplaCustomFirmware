#ifndef storage_init_h
#define storage_init_h

  Supla::Storage::Init();

#ifdef ARDUINO_ARCH_ESP32
  if (Supla::Storage::ConfigInstance()->getInt8(
                      Supla::Html::ConnectionSettingsTag, &selectConnection)) {
    SUPLA_LOG_DEBUG("# Param[%s]: %d", Supla::Html::ConnectionSettingsTag,
                                                             selectConnection);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s]: is not set",
                                           Supla::Html::ConnectionSettingsTag);
  }
#endif

  if (Supla::Storage::ConfigInstance()->getString(DEV_NAME, devName, 30)) {
    SUPLA_LOG_DEBUG("# Param[%s]: %s", DEV_NAME, devName);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s] is not set", DEV_NAME);
  }

  if (Supla::Storage::ConfigInstance()->getInt32(DIM_QTY, &dimmersQuantity)) {
    if (dimmersQuantity < 1 || dimmersQuantity > 16) {
      dimmersQuantity = DEFAULT_DIMMERS_QTY;
      Supla::Storage::ConfigInstance()->setInt32(DIM_QTY, dimmersQuantity);
    }
    SUPLA_LOG_DEBUG("# Param[%s]: %d", DIM_QTY, dimmersQuantity);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s]: is not set", DIM_QTY);
  }

  if (Supla::Storage::ConfigInstance()->getInt32(BTN_LOCK, &lockEnabled)) {
    SUPLA_LOG_DEBUG("# Param[%s]: %d", BTN_LOCK, lockEnabled);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s]: is not set", BTN_LOCK);
  }
  
  if (Supla::Storage::ConfigInstance()->getInt32(HT_VALUE, &holdTimeValue)) {
    if (holdTimeValue <= 0 || holdTimeValue > 1000) {
      holdTimeValue = DEFAULT_HOLD_TIME;
      Supla::Storage::ConfigInstance()->setInt32(HT_VALUE, holdTimeValue);
    }
    SUPLA_LOG_DEBUG("# Param[%s]: %d", HT_VALUE, holdTimeValue);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s] is not set", HT_VALUE);
  }

  if (Supla::Storage::ConfigInstance()->getInt32(ROH_VALUE,
                                                         &repeatOnHoldValue)) {
    if (repeatOnHoldValue <= 0 || repeatOnHoldValue > 150) {
      repeatOnHoldValue = DEFAULT_REPEAT_ON_HOLD;
      Supla::Storage::ConfigInstance()->setInt32(ROH_VALUE, repeatOnHoldValue);
    }
    SUPLA_LOG_DEBUG("# Param[%s]: %d", ROH_VALUE, repeatOnHoldValue);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s] is not set", ROH_VALUE);
  }

  if (Supla::Storage::ConfigInstance()->getInt32(MCT_VALUE,
                                                       &multiclickTimeValue)) {
    if (multiclickTimeValue <= 0 || multiclickTimeValue > 1500) {
      multiclickTimeValue = DEFAULT_MULTICLICK_TIME;
      Supla::Storage::ConfigInstance()->setInt32(MCT_VALUE,
                                                          multiclickTimeValue);
    }
    SUPLA_LOG_DEBUG("# Param[%s]: %d", MCT_VALUE, multiclickTimeValue);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s] is not set", MCT_VALUE);
  }

  if (Supla::Storage::ConfigInstance()->getInt32(BUTTON_STEP, &btnStep)) {
    if (btnStep <= 0 || btnStep > 20) {
      btnStep = DEFAULT_BUTTON_STEP;
      Supla::Storage::ConfigInstance()->setInt32(BUTTON_STEP, btnStep);
    }
    SUPLA_LOG_DEBUG("# Param[%s]: %d", BUTTON_STEP, btnStep);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s] is not set", BUTTON_STEP);
  }

  if (Supla::Storage::ConfigInstance()->getInt32(FADE_EFFECT, &fadeEffect_)) {
    if (fadeEffect_ <= 0 || fadeEffect_ > 1000) {
      fadeEffect_ = DEFAULT_FADE_EFFECT;
      Supla::Storage::ConfigInstance()->setInt32(FADE_EFFECT, fadeEffect_);
    }
    SUPLA_LOG_DEBUG("# Param[%s]: %d", FADE_EFFECT, fadeEffect_);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s] is not set", FADE_EFFECT);
  }

  if (Supla::Storage::ConfigInstance()->getInt32(ITERATION_DELAY,
                                                            &iterationDelay)) {
    if (iterationDelay <= 0 || iterationDelay > 5000) {
      iterationDelay = DEFAULT_ITERATION_DELAY;
      Supla::Storage::ConfigInstance()->setInt32(ITERATION_DELAY,
                                                               iterationDelay);
    }
    SUPLA_LOG_DEBUG("# Param[%s]: %d", ITERATION_DELAY, iterationDelay);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s] is not set", ITERATION_DELAY);
  }

  for (int i = 0; i < dimmersQuantity; i++) {
    char minBuffer[10], maxBuffer[10] = {};
    snprintf(minBuffer, sizeof(minBuffer), "min_%d", i);
    snprintf(maxBuffer, sizeof(maxBuffer), "max_%d", i);
    if (Supla::Storage::ConfigInstance()->getInt32(minBuffer, &minValue[i])) {
      if (minValue[i] < 0 || minValue[i] > 100) {
        minValue[i] = DEFAULT_MIN_VALUE;
        Supla::Storage::ConfigInstance()->setInt32(minBuffer, minValue[i]);
      }
      SUPLA_LOG_DEBUG("# Param[%s]: %d", minBuffer, minValue[i]);
    } else {
      SUPLA_LOG_DEBUG("# Param[%s] is not set, setting default value: %d",
                                                 minBuffer, DEFAULT_MIN_VALUE);
      minValue[i] = DEFAULT_MIN_VALUE;
      Supla::Storage::ConfigInstance()->setInt32(minBuffer, minValue[i]);
    }
    if (Supla::Storage::ConfigInstance()->getInt32(maxBuffer, &maxValue[i])) {
      if (maxValue[i] < 0 || maxValue[i] > 100) {
        maxValue[i] = DEFAULT_MAX_VALUE;
        Supla::Storage::ConfigInstance()->setInt32(maxBuffer, maxValue[i]);
      }
      SUPLA_LOG_DEBUG("# Param[%s]: %d", maxBuffer, maxValue[i]);
    } else {
      SUPLA_LOG_DEBUG("# Param[%s] is not set, setting default value: %d",
                                                 maxBuffer, DEFAULT_MAX_VALUE);
      maxValue[i] = DEFAULT_MAX_VALUE;
      Supla::Storage::ConfigInstance()->setInt32(maxBuffer, maxValue[i]);
    }
  }

  if (Supla::Storage::ConfigInstance()->getInt32(PWM_FREQ, &pwmFrequency)) {
    if (pwmFrequency <= 24 || pwmFrequency > 1526) {
      pwmFrequency = 223;
      Supla::Storage::ConfigInstance()->setInt32(PWM_FREQ, pwmFrequency);
    }
    SUPLA_LOG_DEBUG("# Param[%s]: %d", PWM_FREQ, pwmFrequency);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s] is not set", PWM_FREQ);
  }

#endif