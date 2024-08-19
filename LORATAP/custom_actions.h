#ifndef CUSTOM_ACTIONS_H_
#define CUSTOM_ACTIONS_H_

namespace Supla {
enum default_actions {
  START_WEB_SERVER,
  STOP_WEB_SERVER,
  RS_MOVE_UP,
  RS_MOVE_DOWN,
  RS_STOP
};
}; // namespace Supla

class addedActionsClass : public Supla::ActionHandler, public Supla::Element {
 public: addedActionsClass() {}
  void handleAction(int event, int action) {
    if (action == Supla::START_WEB_SERVER) {
      SuplaDevice.handleAction(0, Supla::START_LOCAL_WEB_SERVER);
    }
    if (action == Supla::STOP_WEB_SERVER) {
      SuplaDevice.handleAction(0, Supla::STOP_LOCAL_WEB_SERVER);
    }
    if (action == Supla::RS_MOVE_UP) {
      SUPLA_LOG_DEBUG("# move UP on hold");
      pressed = true;
      rs_->moveUp();
    }
    if (action == Supla::RS_MOVE_DOWN) {
      SUPLA_LOG_DEBUG("# move DOWN on hold");
      pressed = true;
      rs_->moveDown();
    }
    if (action == Supla::RS_STOP) {
      if (pressed) {
        SUPLA_LOG_DEBUG("# stop on release");
        rs_->stop();
        pressed = false;
      }
    }
  }
};
addedActionsClass *custAct = new addedActionsClass;

#endif
