#ifndef html_h
#define html_h

new Supla::Html::DeviceInfo(&SuplaDevice);
new Supla::Html::WifiParameters;
new Supla::Html::EthernetParameters;
new Supla::Html::ProtocolParameters;
new Supla::Html::CustomTextParameter(DEV_NAME, "Device name", 30);
new Supla::Html::CustomParameter(DIM_QTY, "Dimmers quantity",
                                                          DEFAULT_DIMMERS_QTY);
auto btnlockSelect = new Supla::Html::SelectInputParameter(BTN_LOCK,
                                                               "Buttons lock");
btnlockSelect->registerValue("DISABLED", 0);
btnlockSelect->registerValue("ENABLED", 1);
new Supla::Html::StatusLedParameters;
new Supla::Html::DivEnd();
new Supla::Html::DivBegin("box");
new Supla::Html::H3Tag("Parameters Adjustment");
new Supla::Html::CustomParameter(HT_VALUE, "Hold time (ms)",
                                                            DEFAULT_HOLD_TIME);
new Supla::Html::CustomParameter(ROH_VALUE, "Repeat on hold (ms)",
                                                       DEFAULT_REPEAT_ON_HOLD);
new Supla::Html::CustomParameter(MCT_VALUE, "Multiclick time (ms)",
                                                      DEFAULT_MULTICLICK_TIME);
new Supla::Html::CustomParameter(BUTTON_STEP, "Button step (ms)",
                                                          DEFAULT_BUTTON_STEP);
new Supla::Html::CustomParameter(FADE_EFFECT, "Fade effect (ms)",
                                                          DEFAULT_FADE_EFFECT);
new Supla::Html::CustomParameter(ITERATION_DELAY, "Iteration delay (ms)",
                                                      DEFAULT_ITERATION_DELAY);
for (int i = 0; i < dimmersQuantity; i++) {
  char minBuffer[10], maxBuffer[10], labelBuff1[25], labelBuff2[25];
  snprintf(minBuffer, sizeof(minBuffer), "min_%d", i);
  snprintf(maxBuffer, sizeof(maxBuffer), "max_%d", i);
  snprintf(labelBuff1, sizeof(labelBuff1), "Min.%d brightness (%%)", i+1);
  snprintf(labelBuff2, sizeof(labelBuff2), "Max.%d brightness (%%)", i+1);
  new Supla::Html::CustomParameter(minBuffer, labelBuff1);
  new Supla::Html::CustomParameter(maxBuffer, labelBuff2, 100);
}
new Supla::Html::CustomParameter(PWM_FREQ, "PWM frequency (Hz)", 223);

#endif