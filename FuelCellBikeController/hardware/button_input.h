unsigned long button_action_allowed = 0;

int button_down() {
  int button = 0;
  if (millis() > button_action_allowed) {
    if (digitalRead(BUTTON_1) == LOW) button = BUTTON_NEXT;
    if (digitalRead(BUTTON_2) == LOW) button = BUTTON_PREVIOUS;
    if (digitalRead(BUTTON_3) == LOW) button = BUTTON_ACTION;
    if (digitalRead(BUTTON_4) == LOW) button = BUTTON_UNUSED_1;
    if (digitalRead(BUTTON_5) == LOW) button = BUTTON_UNUSED_2;
  }
  if (button > 0) button_action_allowed = millis()+BUTTON_DEAD_TIME;
  return button;
// the above code could be cleaned up.
}
