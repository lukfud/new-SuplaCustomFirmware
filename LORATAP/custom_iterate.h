#ifndef CUSTOM_ITERATE_H_
#define CUSTOM_ITERATE_H_

class customIterate : public Supla::Element {
 public: customIterate() {}

  void iterateAlways() {
    
    if ((millis() - lastReadTime > 5000) && selectMode == SWITCH) {
      lastReadTime = millis();
      auto cfg = Supla::Storage::ConfigInstance();
      uint8_t inCfgValue[2] = {0,0};
      for (int i = 0; i < 2; i++) {
        char isStairBuf[15];
        snprintf(isStairBuf, sizeof(isStairBuf), "%d_is_stair", i+1);
        cfg->getUInt8(isStairBuf, &inCfgValue[i]);
        if (inCfgValue[i] != relay_[i]->isStaircaseFunction()) {
          cfg->setUInt8(isStairBuf, relay_[i]->isStaircaseFunction());
          SUPLA_LOG_DEBUG("# Relay[%d] - staircase set to %d", i,
                                             relay_[i]->isStaircaseFunction());
          SuplaDevice.scheduleSoftRestart(2000);
        }
      }
    }

  };

 protected:
  uint32_t lastReadTime = 0;
};

customIterate *custIterate = new customIterate;

#endif