
#include "definitions.h"

#include <SuplaDevice.h>
#include <supla/clock/clock.h>

#include <supla/network/client.h>
#include <supla/network/esp_wifi.h>
Supla::ESPWifi *wifi = nullptr;
#ifdef ARDUINO_ARCH_ESP32
#include <supla/network/wt32_eth01.h>
Supla::WT32_ETH01 *eth = nullptr;
#include <HTTPUpdateServer.h>
HTTPUpdateServer httpUpdater;
#else
#include <ESP8266HTTPUpdateServer.h>
ESP8266HTTPUpdateServer httpUpdater;
#endif
#include <supla/network/esp_web_server.h>
Supla::EspWebServer suplaServer;

#include <supla/control/button.h>
Supla::Control::Button *button_[16] = {};
#include <supla/control/dimmer_leds.h>
Supla::Control::DimmerLeds *dimmer_[16] = {};
#include <supla/control/action_trigger.h>
Supla::Control::ActionTrigger *at_[16] = {};
#include <supla/control/virtual_relay.h>
Supla::Control::VirtualRelay *webSrvVRelay = nullptr;
Supla::Control::VirtualRelay *vrelay_[16] = {};
#include <supla/control/EXT_PCA9685.h>
Supla::Control::ExtPCA9685 *extpca = nullptr;
#include <supla/control/EXT_MCP23017.h>
Supla::Control::ExtMCP23017 *extmcp = nullptr;

#include <supla/device/status_led.h>
#ifdef ARDUINO_ARCH_ESP8266
Supla::Device::StatusLed statusLed(STATUS_LED_GPIO, true);
#else
Supla::Device::StatusLed statusLed(STATUS_LED_GPIO);
#endif
#include <supla/device/supla_ca_cert.h>

#include <supla/storage/eeprom.h>
Supla::Eeprom eeprom;
#include <supla/storage/littlefs_config.h>
Supla::LittleFsConfig configSupla(2048);

#include <supla/network/html/div.h>
#include <supla/network/html/h3_tag.h>
#include <supla/network/html/device_info.h>
#include <supla/network/html/protocol_parameters.h>
#include <supla/network/html/status_led_parameters.h>
#ifdef ARDUINO_ARCH_ESP8266
#include <supla/network/html/wifi_parameters.h>
#else
#include <supla/network/html/connection_settings.h>
#endif
#include <supla/network/html/custom_parameter.h>
#include <supla/network/html/custom_text_parameter.h>
#include <supla/network/html/select_input_parameter.h>

int8_t selectConnection = 0;
const char BTN_LOCK[] = "button_lock";
int32_t lockEnabled = 0;
const char DEV_NAME[] = "dev_name";
char devName[30] = {};
const char HT_VALUE[] = "hold_time_value";
int32_t holdTimeValue = DEFAULT_HOLD_TIME;
const char ROH_VALUE[] = "repeat_on_hold_value";
int32_t repeatOnHoldValue = DEFAULT_REPEAT_ON_HOLD;
const char MCT_VALUE[] = "multiclick_time_value";
int32_t multiclickTimeValue = DEFAULT_MULTICLICK_TIME;
const char PWM_FREQ[] = "pwm_frequency";
int32_t pwmFrequency = 223;
const char BUTTON_STEP[] = "button_step";
int32_t btnStep = DEFAULT_BUTTON_STEP;
const char FADE_EFFECT[] = "fade_effect";
int32_t fadeEffect_ = DEFAULT_FADE_EFFECT;
const char ITERATION_DELAY[] = "iteration_delay";
int32_t iterationDelay = DEFAULT_ITERATION_DELAY;
int32_t minValue[16] = {};
int32_t maxValue[16] = {};
const char DIM_QTY[] = "dimmers_quantity";
int32_t dimmersQuantity = DEFAULT_DIMMERS_QTY;

#include "classes.h"

void setup() {
  Serial.begin(115200);
  new Supla::Clock;

#include "storage_init.h"

  if (selectConnection == WLAN) {
    wifi = new Supla::ESPWifi;
  } else {
#ifdef ARDUINO_ARCH_ESP32
    eth = new Supla::WT32_ETH01(1);
#endif
  }
  extmcp = new Supla::Control::ExtMCP23017(0x20);
  extpca = new Supla::Control::ExtPCA9685();
  extpca->setPWMFrequency(pwmFrequency);

  for (int i = 0; i < dimmersQuantity; i++) {
    dimmer_[i] = new Supla::Control::DimmerLeds(extpca, i);
    dimmer_[i]->setStep(btnStep);
    dimmer_[i]->setFadeEffectTime(fadeEffect_);
    dimmer_[i]->setMinMaxIterationDelay(iterationDelay);
    at_[i] = new Supla::Control::ActionTrigger();
    button_[i] = new Supla::Control::Button(extmcp, i, true, true);
    button_[i]->setSwNoiseFilterDelay(100);
    button_[i]->setHoldTime(holdTimeValue);
    button_[i]->repeatOnHoldEvery(repeatOnHoldValue);
    button_[i]->setMulticlickTime(multiclickTimeValue);
    button_[i]->addAction(Supla::ITERATE_DIM_W, dimmer_[i], Supla::ON_HOLD);
    button_[i]->addAction(Supla::TOGGLE, dimmer_[i], Supla::ON_CLICK_1);
    at_[i]->setRelatedChannel(dimmer_[i]);
    at_[i]->attach(button_[i]);
    minValue[i] = map(minValue[i], 0, 100, 0, 1023);
    maxValue[i] = map(maxValue[i], 0, 100, 0, 1023);
    dimmer_[i]->setBrightnessLimits(minValue[i], maxValue[i]);
  }
  webSrvVRelay = new Supla::Control::VirtualRelay(32);
  webSrvVRelay->setDefaultStateOff();
  webSrvVRelay->getChannel()->setDefault(SUPLA_CHANNELFNC_POWERSWITCH);
  webSrvVRelay->addAction(START_WEB_SERVER, custAct, Supla::ON_TURN_ON);
  webSrvVRelay->addAction(STOP_WEB_SERVER, custAct, Supla::ON_TURN_OFF);
  if (lockEnabled) {
    for (int i = 0; i < dimmersQuantity; i++) {
      vrelay_[i] = new Supla::Control::VirtualRelay(32);
      vrelay_[i]->setDefaultStateRestore();
      vrelay_[i]->getChannel()->setDefault(SUPLA_CHANNELFNC_POWERSWITCH);
      vrelay_[i]->addAction(Supla::DISABLE, button_[i], Supla::ON_TURN_ON);
      vrelay_[i]->addAction(Supla::ENABLE, button_[i], Supla::ON_TURN_OFF);
    }
  }
  auto buttonCfg = new Supla::Control::Button(BUTTON_CFG_GPIO, true, true);
  buttonCfg->configureAsConfigButton(&SuplaDevice);

#include "html.h"

  httpUpdater.setup(suplaServer.getServerPtr(), "/update");
  SuplaDevice.setName(devName);
  SuplaDevice.setSuplaCACert(suplaCACert);
  SuplaDevice.setSupla3rdPartyCACert(supla3rdCACert);
  SuplaDevice.begin();
  SuplaDevice.getSrpcLayer()->client->setDebugLogs(false);
};

void loop() {
  SuplaDevice.iterate();
};
