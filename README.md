# ButtonIO.h

**ButtonIO** is a Arduino library to make it easier to work with buttons.  
No more bloated `loop()` with all the state handling.

**Features**

* Easly see when a button is release
* Execute a function when the button is holded for n milliseconds
* Make it execute a function when the button was hold between to time intervals.

-----

**Important**  

At the moment one can only put one of each handler (pressed, hold, between) to a single ButtonIO object.  

*This is only tested on an Arduino Uno*

-----

## Usage

```cpp

#include <ButtonIO.h>

ButtonIO button(4);

void setup() {
    Serial.begin(9600);

    button.pressed(press); // Assign void press as listener
}

void press(int pin) {
    Serial.println("Button was pressed");
}

void loop() {
    button.update(); // Make the button update each loop

    delay(15);
}

```

-----

## Install

Download the files in this repo and put them into your Arduino library folder.

For Mac it's located default located at `~/Documents/Arduino/libraries`

-----

## Docs

```cpp

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

```


## Todo

* Make it run on more Arduino devices
* Add multiple of the same handler to the same ButtonIO object