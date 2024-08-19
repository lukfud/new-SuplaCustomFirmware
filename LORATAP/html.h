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
new Supla::Html::ModeParameter();

#endif
