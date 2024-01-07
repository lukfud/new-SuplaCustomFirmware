#ifndef classes_h
#define classes_h

enum default_actions {
  START_WEB_SERVER,
  STOP_WEB_SERVER,
};

class addedActionsClass : public Supla::ActionHandler, public Supla::Element {
 public: addedActionsClass() {}
  void handleAction(int event, int action) {
    if (action == START_WEB_SERVER) {
      SuplaDevice.handleAction(0, Supla::START_LOCAL_WEB_SERVER);
    }
    if (action == STOP_WEB_SERVER) {
      SuplaDevice.handleAction(0, Supla::STOP_LOCAL_WEB_SERVER);
    }
  }
};
addedActionsClass *custAct = new addedActionsClass;
#endif