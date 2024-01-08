#ifndef CUSTOM_ITERATE_H_
#define CUSTOM_ITERATE_H_

class customIterate : public Supla::Element {
 public: customIterate() {}

  void iterateAlways() {
    
    if ((millis() - lastReadTime > 5000) && selectMode == SWITCH) {
      lastReadTime = millis();
      for (int i = 0; i < 2; i++) {
        if (channelFnc[i] != relay_[i]->getChannel()->getDefaultFunction()) {
          if (staircaseModeTag[i] == ON_) {
            SuplaDevice.scheduleSoftRestart(2500);
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