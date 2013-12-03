/*
  ButtonIO - A button helper for Arudino
  Created by Simon Andersson. November 16, 2013.

  http://hiddencode.me
  https://github.com/hellozimi
  https://twitter.com/hellozimi
*/
  
#include "Arduino.h"
#include "ButtonIO.h"

Action init_action(type_t type) {
    Action action;
    action.type = type;
    action.lastState = 0;
    action.startTime = -1;
    action.duration = 0;
    action.least = 0;
    action.pin = -1;
    return action;
}

ButtonIO::ButtonIO(int pin) {
    pinMode(pin, INPUT);
    _pin = pin;
    _maxPressedDuration = -1;
}

void ButtonIO::pressed(callback_t callback) {
    Action action = Action();
    action.callback = callback;
    action.type = TypePressed;
    action.pin = _pin;

    _actions[0] = action;
}

void ButtonIO::hold(callback_t callback, int duration) {
    Action action = Action();
    action.callback = callback;
    action.type = TypeHold;
    action.pin = _pin;
    action.duration = duration;

    _maxPressedDuration = duration;

    _actions[1] = action;
}

void ButtonIO::between(callback_t callback, int least, int duration) {

    Action action = Action();
    action.callback = callback;
    action.type = TypeBetween;
    action.pin = _pin;
    action.duration = duration;
    action.least = least;

    _actions[2] = action;
}

void ButtonIO::update() {
    int value = digitalRead(_pin);
    int i = 0;
    for (; i < 3; i++) {
        Action &action = _actions[i];

        // Is set
        if (action.pin > -1) {
            
            switch(action.type) {
                case TypePressed:
                    handle_pressed(action, value);
                    break;
                case TypeHold:
                    handle_hold(action, value);
                    break;
                case TypeBetween:
                    handle_between(action, value);
                    break;
            }
            
            action.lastState = value;
        }
    }
}

void ButtonIO::handle_pressed(Action &action, int value) {
    if ( action.startTime > 0 ) {
        if (action.lastState == HIGH && value == LOW) {

            long time = millis() - action.startTime;

            if ( _maxPressedDuration > 0 && time > _maxPressedDuration ) {
                action.startTime = -1;
                return;
            }
            action.callback(action.pin);
            action.startTime = -1;
        }
    }
    else {
        if (action.lastState == LOW && value == HIGH) {
            action.startTime = millis();
        }
    }
}

void ButtonIO::handle_hold(Action &action, int value) {
    
    if ( action.startTime > 0 ) {
        if (action.lastState == HIGH && value == LOW) {

            long time = millis();
            long time_down = time - action.startTime;
            int duration = action.duration;

            if ( time_down > duration ) {
                action.callback(action.pin);
            }
            action.startTime = -1;
        }
    }
    else {
        if (action.lastState == LOW && value == HIGH) {
            action.startTime = millis();
        }
    }
}

void ButtonIO::handle_between(Action &action, int value) {
    
    if ( action.startTime > 0 ) {
        if (action.lastState == HIGH && value == LOW) {

            long time = millis();
            long time_down = time - action.startTime;
            int duration = action.duration;
            int least = action.least;
            bool is_between = time_down > least && time_down < duration;

            if (is_between) {
                action.callback(action.pin);
            }

            action.startTime = -1;
        }
    }
    else {
        if (action.lastState == LOW && value == HIGH) {
            action.startTime = millis();
        }
    }
}