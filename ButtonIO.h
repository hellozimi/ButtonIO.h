/*
  ButtonIO - A button helper for Arudino
  Created by Simon Andersson. November 16, 2013.

  http://hiddencode.me
  https://github.com/hellozimi
  https://twitter.com/hellozimi
*/

#ifndef ButtonIO_h
#define ButtonIO_h

#include <vector>

// Callback function structore
// Passes which pin was handeled
typedef void (*callback_t)(int pin);

// Helper enum for Action
// To determine which action were listening on 
typedef enum type_t {
    TypePressed,
    TypeHold,
    TypeBetween
} type_t;


// Struct for an action
// To create a pre-filled action use Action()
struct Action {
    Action(): pin(-1), lastState(0), startTime(0), duration(0), least(0) {}

    int pin;
    callback_t callback;
    type_t type;
    int lastState;
    long startTime;
    int duration;
    int least;
};

class ButtonIO
{
public:
    // Constructor
    // @param int pin - the pin to listen on (INPUT)
    // @usage:
    //
    //     #include <ButtonIO.h>
    //     ButtonIO button(4); // Create listener on pin 4
    ButtonIO(int pin);

    // Method for listening on presses
    // @param callback_t callback - the function to be called
    // @usage:
    
    //
    //     void press(int pin) {
    //         // This will be fiered once button is released
    //     }
    void pressed(callback_t callback);

    // Method for holding on the button for at least n milliseconds
    // @param callback_t callback - the function to be called
    // @param int duration - the duration of the minimum hold in millisedoncs
    // @usage:
    //
    //     void setup() {
    //         button.hold(holder, 1000);
    //     }
    //     
    //     void holder(int pin) {
    //         // This will be fiered once the button release
    //         // while it's been down for at least 1000 millis
    //     }
    void hold(callback_t callback, int durtaion);

    // Method for holding on the button for at least n milliseconds
    // @param callback_t callback - the function to be called
    // @param int min - the minimum value the button has to be down
    // @param int max - the maximum value the button has to be down
    // @usage:
    //
    //     void setup() {
    //         button.hold(between, 1000, 2000);
    //     }
    //
    //     void between(int pin) {
    //         // This will be fiered once the button release
    //         // while it's been down for at least 1000 millis
    //         // but not more than 2000 millis
    //     }
    void between(callback_t callback, int min, int max);

    // This needs to be called every cycle in loop
    // @tip: To get more accuracy on the button timings, 
    //       don't use too many delay()'s
    //
    // @usage:
    //
    //     void loop() {
    //         button.update();
    //         //...
    //     }
    void update();

private:

    void handle_pressed(Action &action, int value);
    void handle_hold(Action &action, int value);
    void handle_between(Action &action, int value);

    // Keeps track of which pin where listening on
    int _pin;

    // An array of the three action types we're using at the moment
    // This is a subject to change.
    Action _actions[3];

    // To suppress if hold is set
    int _maxPressedDuration;
};

#endif