#ifndef MODE_PARAMETER_H_
#define MODE_PARAMETER_H_

namespace Supla {
namespace Html {

class ModeParameter : public Supla::HtmlElement {
 public:
  ModeParameter() : HtmlElement(HTML_SECTION_FORM) {}

  void send(Supla::WebSender* sender) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg) {
      uint32_t value = 0; // default value
      cfg->getUInt32(SELECT_MODE, &value);

      // form-field BEGIN
      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(SELECT_MODE, "Module mode *");
      sender->send("<select");
      sender->sendNameAndId(SELECT_MODE);
      sender->send("onchange=\"modeToggle();\">");
      sender->send("<option value=\"0\"");
      sender->send(selected(value == 0));
      sender->send(">BLIND</option>");
      sender->send("<option value=\"1\"");
      sender->send(selected(value == 1));
      sender->send(">2CH SWITCH</option>");
      sender->send("</select>");
      sender->send("</div>");
      // form-field END

      sender->send("</div>"); // end previous box

      // hidden div begin
      sender->send("<div id=\"blind_hidden_div\" style=\"display: ");
      sender->send(displayed(!value));

       // box begin
      sender->send("<div class=\"box\">");

      // form-field BEGIN
      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(COMFORT_UP, "Comfort up (%)");
      sender->send(
              "<input type=\"number\" min=\"0\" max=\"100\" step=\"1\" ");
      sender->sendNameAndId(COMFORT_UP);
      sender->send(" value=\"");
      uint32_t inCfgValue = 25; // default value
      cfg->getUInt32(COMFORT_UP, &inCfgValue);
      sender->send(inCfgValue);
      sender->send("\">");
      sender->send("</div>");
      // form-field END

      // form-field BEGIN
      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(COMFORT_DOWN, "Comfort down (%)");
      sender->send(
              "<input type=\"number\" min=\"0\" max=\"100\" step=\"1\" ");
      sender->sendNameAndId(COMFORT_DOWN);
      sender->send(" value=\"");
      inCfgValue = 75; // default value
      cfg->getUInt32(COMFORT_DOWN, &inCfgValue);
      sender->send(inCfgValue);
      sender->send("\">");
      sender->send("</div>");
      // form-field END

      sender->send("</div>"); // end box

      sender->send("</div>"); // hidden div end

      // hidden div begin
      sender->send("<div id=\"switch_hidden_div\" style=\"display: ");
      sender->send(displayed(value));

       // box begin
      sender->send("<div class=\"box\">");
      int32_t type_value[2] = {0,0}; // default value
      uint32_t state_value[2] = {0,0}; // default value
      for (int i = 0; i < 2; i++) {

        // form-field BEGIN
        char tagTypeBuf[15], labelTypeBuf[25];
        snprintf(tagTypeBuf, sizeof(tagTypeBuf), "%d_btn_type", i+1);
        snprintf(labelTypeBuf, sizeof(labelTypeBuf), "Button %d type", i+1);

        sender->send("<div class=\"form-field\">");
        sender->sendLabelFor(tagTypeBuf, labelTypeBuf);
        sender->send("<select");
        sender->sendNameAndId(tagTypeBuf);
        sender->send(">");
        cfg->getInt32(tagTypeBuf, &type_value[i]);
        sender->send("<option value=\"0\"");
        sender->send(selected(type_value[i] == 0));
        sender->send(">MONOSTABLE</option>");
        sender->send("<option value=\"1\"");
        sender->send(selected(type_value[i] == 1));
        sender->send(">BISTABLE</option>");
        sender->send("</select>");
        sender->send("</div>");
        // form-field END

        // form-field BEGIN
        char tagStateBuf[15], labelStateBuf[25];
        snprintf(tagStateBuf, sizeof(tagStateBuf), "%d_rel_state", i+1);
        snprintf(labelStateBuf, sizeof(labelStateBuf), "Relay %d default state", i+1);

        sender->send("<div class=\"form-field\">");
        sender->sendLabelFor(tagStateBuf, labelStateBuf);
        sender->send("<select");
        sender->sendNameAndId(tagStateBuf);
        sender->send(">");
        cfg->getUInt32(tagStateBuf, &state_value[i]);
        sender->send("<option value=\"0\"");
        sender->send(selected(state_value[i] == 0));
        sender->send(">OFF</option>");
        sender->send("<option value=\"1\"");
        sender->send(selected(state_value[i] == 1));
        sender->send(">ON</option>");
        sender->send("<option value=\"2\"");
        sender->send(selected(state_value[i] == 2));
        sender->send(">RESTORE</option>");
        sender->send("</select>");
        sender->send("</div>");
        // form-field END
      }
      sender->send("</div>"); // end box

      sender->send("</div>"); // hidden div end

      sender->send("<div>"); // begin next box


      sender->send("<script>"
        "function modeToggle() {"
          "var mp_select = document.getElementById(\"");
      sender->send(SELECT_MODE);
      sender->send("\");"
          "var mp_blind = document.getElementById(\"blind_hidden_div\");"
          "var mp_switch = document.getElementById(\"switch_hidden_div\");"
          "if (mp_select.value == 0) {"
            "mp_blind.style.display = \"block\";"
            "mp_switch.style.display = \"none\";"
          "} else {"
            "mp_blind.style.display = \"none\";"
            "mp_switch.style.display = \"block\";"
          "}"
        "}"
      "</script>");

    } // cfg

  } // sender

  bool handleResponse(const char* key, const char* value) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg && strcmp(key, SELECT_MODE) == 0) {
      int inFormValue = stringToUInt(value);
      cfg->setUInt32(SELECT_MODE, inFormValue);
      selectMode = inFormValue;
      return true;
    }
    if (cfg && strcmp(key, COMFORT_UP) == 0) {
      int inFormValue = stringToUInt(value);
      if (inFormValue >= 0 && inFormValue <= 100) {
        cfg->setUInt32(COMFORT_UP, inFormValue);
        comfortUpState = inFormValue;
      }
      return true;
    }
    if (cfg && strcmp(key, COMFORT_DOWN) == 0) {
      int inFormValue = stringToUInt(value);
      if (inFormValue >= 0 && inFormValue <= 100) {
        cfg->setUInt32(COMFORT_DOWN, inFormValue);
        comfortDownState = inFormValue;
      }
      return true;
    }
    for (int i = 0; i < 2; i++) {
      char tagStateBuf[15];
      snprintf(tagStateBuf, sizeof(tagStateBuf), "%d_rel_state", i+1);
      if (cfg && strcmp(key, tagStateBuf) == 0) {
        int inFormValue = stringToUInt(value);
        cfg->setUInt32(tagStateBuf, inFormValue);
        relayState[i] = inFormValue;
        return true;
      }
      char tagTypeBuf[15];
      snprintf(tagTypeBuf, sizeof(tagTypeBuf), "%d_btn_type", i+1);
      if (cfg && strcmp(key, tagTypeBuf) == 0) {
        int inFormValue = stringToInt(value);
        inFormValue = (selectMode == SWITCH) ? inFormValue : 0;
        cfg->setInt32(tagTypeBuf, inFormValue);
        return true;
      }
    }
    return false;
  }

 protected:

}; // ModeParameter

}; // namespace Html
}; // namespace Supla

#endif