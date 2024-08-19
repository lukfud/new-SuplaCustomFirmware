#ifndef CUSTOM_ITERATE_H_
#define CUSTOM_ITERATE_H_

class customIterate : public Supla::Element {
 public: customIterate() {}

  void iterateAlways() {
    
    if ((millis() - lastReadTime > 5000) && selectMode == SWITCH) {
      lastReadTime = millis();
      for (int i = 0; i < 2; i++) {
        if (relay_[i] != nullptr) {
          auto newChannelFnc = relay_[i]->getChannel()->getDefaultFunction();
          if (channelFnc[i] != newChannelFnc) {
            if (staircaseModeTag[i] == ON_ || noTimerOnEvent[i] != DISABLED_) {
              SUPLA_LOG_DEBUG(
                     "# Relay[%d]: fnc has changed to %d", i+1, newChannelFnc);
              SuplaDevice.scheduleSoftRestart(2500);
            }
          }
        }
      }
    }

  };

 protected:
  uint32_t lastReadTime = 0;
};

customIterate customIterate;

#endif