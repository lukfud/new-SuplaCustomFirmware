#ifndef MAIN_ENV_H_
#define MAIN_ENV_H_
//--------------------------------- 80 signs ---------------------------------|
//                                                                         Core
#include <SuplaDevice.h>
#include <supla/tools.h>
//--------------------------------- 80 signs ---------------------------------|
//                                                                      Storage
#include <supla/storage/eeprom.h>
Supla::Eeprom eeprom;
#include <supla/storage/littlefs_config.h>
Supla::LittleFsConfig configSupla(1024);
//--------------------------------- 80 signs ---------------------------------|
//                                                                      Network
#include <supla/network/client.h>
#include <supla/network/esp_wifi.h>
Supla::ESPWifi *wifi_ = nullptr;
#include <supla/network/esp_web_server.h>
Supla::EspWebServer suplaServer;
#include <ESP8266HTTPUpdateServer.h>
ESP8266HTTPUpdateServer httpUpdater;
//--------------------------------- 80 signs ---------------------------------|
//                                                                       Device
#include <supla/device/status_led.h>
Supla::Device::StatusLed statusLed(STATUS_LED_GPIO, true);
#include <supla/device/supla_ca_cert.h>
//--------------------------------- 80 signs ---------------------------------|
//                                                                      Buttons
#include <supla/control/button.h>
Supla::Control::Button *cfgButton = nullptr;
Supla::Control::Button *button_[2] = {};
//--------------------------------- 80 signs ---------------------------------|
//                                                                      Control
#include <supla/control/relay.h>
Supla::Control::Relay *relay_[2] = {};
#include <supla/control/roller_shutter.h>
Supla::Control::RollerShutter *rs_ = nullptr;
#include <supla/control/virtual_relay.h>
Supla::Control::VirtualRelay *websrv_ = nullptr;
#include <supla/control/action_trigger.h>
Supla::Control::ActionTrigger *at_[2] = {};
//--------------------------------- 80 signs ---------------------------------|
//                                                                         Html
#include <supla/network/html/div.h>
#include <supla/network/html/h3_tag.h>
#include <supla/network/html/device_info.h>
#include <supla/network/html/protocol_parameters.h>
#include <supla/network/html/wifi_parameters.h>
#include <supla/network/html/status_led_parameters.h>
#include <supla/network/html/custom_parameter.h>
#include <supla/network/html/custom_text_parameter.h>
#include <supla/network/html/custom_checkbox_parameter.h>
#include <supla/network/html/text_cmd_input_parameter.h>
#include <supla/network/html/select_input_parameter.h>
Supla::Html::SelectInputParameter *relayState_[2] = {};
#include <supla/network/html/button_type_parameters.h>
Supla::Html::ButtonTypeParameters *buttonType_[2] = {};
#include <supla/network/html/button_hold_time_parameters.h>
#include <supla/network/html/button_multiclick_parameters.h>
#include <supla/device/enter_cfg_mode_after_power_cycle.h>

#endif
