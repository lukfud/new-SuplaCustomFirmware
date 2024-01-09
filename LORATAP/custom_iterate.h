#ifndef CUSTOM_ITERATE_H_
#define CUSTOM_ITERATE_H_

class customIterate : public Supla::Element {
 public: customIterate() {}

  void iterateAlways() {
    
    if ((millis() - lastReadTime > 5000) && selectMode == SWITCH) {
      lastReadTime = millis();
      for (int i = 0; i < 2; i++) {
        for (auto element = Supla::Element::begin(); element !=nullptr;
                                                   element = element->next()) {
          if (element->getChannel()) {
            auto channel = element->getChannel();
            if (channel->getChannelType() == SUPLA_CHANNELTYPE_RELAY &&
                  channel->getDefaultFunction() !=
                            SUPLA_CHANNELFNC_CONTROLLINGTHEROLLERSHUTTER) {
              if (channelFnc[i] !=
                             relay_[i]->getChannel()->getDefaultFunction()) {
                if (staircaseModeTag[i] == ON_ ||
                                              noTimerOnEvent[i] != DISABLED_) {
                  SuplaDevice.scheduleSoftRestart(2500);
                }
                break;
              }
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