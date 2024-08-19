
#include "definitions.h"
#include "main_env.h"
#include "variables.h"
#include "html_classes.h"
#include "custom_actions.h"
#include "custom_iterate.h"

void setup() {

  Serial.begin(115200);
  wifi_ = new Supla::ESPWifi;
  #include "storage_init.h"

  cfgButton = new Supla::Control::Button(CFG_BUTTON, true, true);
  cfgButton->configureAsConfigButton(&SuplaDevice);

  if (selectMode == BLIND) {
    rs_ = new Supla::Control::RollerShutter(RELAY_1, RELAY_2);
    rs_->configComfortUpValue(comfortUpState);
    rs_->configComfortDownValue(comfortDownState);
    for (int i = 0; i < 2; i++) {
      button_[i]  = new Supla::Control::Button(buttonPin[i], true, true);
      button_[i]->setButtonNumber(i+1);
      button_[i]->addAction(Supla::OPEN_OR_STOP + i, rs_, Supla::ON_CLICK_1);
      button_[i]->addAction(Supla::COMFORT_UP_POSITION + i, rs_, Supla::ON_CLICK_2);
      button_[i]->addAction(Supla::RS_MOVE_UP + i, custAct, Supla::ON_HOLD);
      button_[i]->addAction(Supla::RS_STOP, custAct, Supla::ON_RELEASE, true);
      at_[i] = new Supla::Control::ActionTrigger();
      at_[i]->setRelatedChannel(rs_);
      at_[i]->attach(button_[i]);
    }
  }

  if (selectMode == SWITCH) {
    for (int i = 0; i < 2; i++) {
      relay_[i] = new Supla::Control::Relay(relayPin[i], true, 224);
      relay_[i]->getChannel()->setDefault(SUPLA_CHANNELFNC_LIGHTSWITCH);
      if (relayState[i] == OFF_) {
        relay_[i]->setDefaultStateOff();
      } else if (relayState[i] == ON_) {
        relay_[i]->setDefaultStateOn();
      } else if (relayState[i] == RESTORE_) {
        relay_[i]->setDefaultStateRestore();
      }
      button_[i] = new Supla::Control::Button(buttonPin[i], true, true);
      button_[i]->setButtonNumber(i+1);
      if (channelFnc[i] == SUPLA_CHANNELFNC_STAIRCASETIMER &&
                                                  staircaseModeTag[i] == ON_) {
        button_[i]->addAction(Supla::TURN_ON, relay_[i], Supla::ON_CLICK_1);
        SUPLA_LOG_DEBUG("# Staircase function[%d] - reset time", 2*i);
      } else {
        button_[i]->addAction(Supla::TOGGLE, relay_[i], Supla::ON_CLICK_1);
      }
      if (channelFnc[i] == SUPLA_CHANNELFNC_STAIRCASETIMER &&
                                              noTimerOnEvent[i] != DISABLED_) {
        button_[i]->addAction(
                   Supla::TURN_ON_WITHOUT_TIMER, relay_[i], noTimerOnEvent[i]);
      }
      at_[i] = new Supla::Control::ActionTrigger();
      at_[i]->setRelatedChannel(relay_[i]);
      at_[i]->attach(button_[i]);
    }
  }
  
  #include "html.h"

  new Supla::Device::EnterCfgModeAfterPowerCycle(5000, 3, true);

  httpUpdater.setup(suplaServer.getServerPtr(), "/update");
  SuplaDevice.setName(devName);
  SuplaDevice.setSwVersion(SOFT_VERSION);
  SuplaDevice.setSuplaCACert(suplaCACert);
  SuplaDevice.setSupla3rdPartyCACert(supla3rdCACert);
  SuplaDevice.begin();
  SuplaDevice.setProtoVerboseLog(false);
}

void loop() {
  SuplaDevice.iterate();
}
