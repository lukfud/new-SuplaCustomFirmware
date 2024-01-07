#ifndef HTML_H_
#define HTML_H_

new Supla::Html::DeviceInfo(&SuplaDevice);
new Supla::Html::WifiParameters;
new Supla::Html::ProtocolParameters;
new Supla::Html::CustomTextParameter(DEV_NAME, "Device name", 30);
new Supla::Html::StatusLedParameters;
auto textCmd =
            new Supla::Html::TextCmdInputParameter("cmd1", "Reset to factory");
textCmd->registerCmd("RESET", Supla::ON_EVENT_1);
textCmd->addAction(Supla::RESET_TO_FACTORY_SETTINGS,
                                               SuplaDevice, Supla::ON_EVENT_1);
new Supla::Html::DivEnd();

new Supla::Html::DivBegin("box");
new Supla::Html::H3Tag("Module Configuration");
new Supla::Html::ButtonHoldTimeParameters();
new Supla::Html::ButtonMulticlickParameters();
/*
auto sm = new Supla::Html::SelectInputParameter(
                                                SELECT_MODE, "Module mode *");
sm->registerValue("BLIND", 0);
sm->registerValue("2CH SWITCH", 1);

if (selectMode == BLIND) {
  new Supla::Html::DivEnd();
  new Supla::Html::DivBegin("box");
  new Supla::Html::CustomParameter(COMFORT_UP, "Comfort Up", 25);
  new Supla::Html::CustomParameter(COMFORT_DOWN, "Comfort down", 75);
}
*/
new Supla::Html::ModeParameter();
/*
if (selectMode == SWITCH) {
  new Supla::Html::DivEnd();
  for (int i = 0; i < 2; i++) {
    char tagBuf[15], labelBuf[25];
    snprintf(tagBuf, sizeof(tagBuf), "%d_rel_state", i);
    snprintf(labelBuf, sizeof(labelBuf), "Relay%d default state", i+1);
    new Supla::Html::DivBegin("box");
    buttonType_[i] = new Supla::Html::ButtonTypeParameters(i+1);
    buttonType_[i]->addMonostableOption();
    buttonType_[i]->addBistableOption();
    relayState_[i] = new Supla::Html::SelectInputParameter(tagBuf, labelBuf);
    relayState_[i]->registerValue("OFF", 0);
    relayState_[i]->registerValue("ON", 1);
    relayState_[i]->registerValue("RESTORE", 2);
    new Supla::Html::DivEnd();
  }
  new Supla::Html::DivBegin();
}
*/
#endif