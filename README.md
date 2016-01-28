# Arduino PushButton library [![Build Status](https://travis-ci.org/yoreek/Arduino-PushButton.svg?branch=master)](https://travis-ci.org/yoreek/Arduino-PushButton)

* Version: 1.0.0
* Release Date: 2016-01-28

## How do I get set up? ##

 * [Download](https://github.com/yoreek/Arduino-PushButton/archive/master.zip) the Latest release from gitHub.
 * Unzip and modify the Folder name to "PushButton".
 * Paste the modified folder on your library folder (On your `Libraries` folder inside Sketchbooks or Arduino software).
 * Download and Install [StateMachine](https://github.com/yoreek/Arduino-StateMachine) library.
 * Restart the Arduino Software


## Usage ##


```
#include <Arduino.h>
#include <PushButton.h>

#define BUTTON_PIN 2
#define LED_PIN    13

void pressed(PushButton *, PushButtonState) {
    Serial.println("Button is pressed");
    digitalWrite(LED_PIN, HIGH);
}

void released(PushButton *, PushButtonState) {
    Serial.println("Button is released");
    digitalWrite(LED_PIN, HIGH);
}

void changed(PushButton *, PushButtonState) {
    Serial.println("Button state is changed");
}

PushButton btn(BUTTON_PIN);

void setup() {
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    btn.onPress(pressed);
    btn.onRelease(released);
    btn.onChange(changed);
}

void loop() {
    btn.loop();

/*
    if (btn.isStateChanged()) {
        if (btn.isPressed()) {
            Serial.println("Button is pressed");
            digitalWrite(LED_PIN, HIGH);
        }
        else {
            Serial.println("Button is released");
            digitalWrite(LED_PIN, LOW);
        }
    }
*/
}

```

## Example ##

Included on example folder, available on Arduino IDE.


## Version History ##

 * 1.0.0 (2016-01-28): Initial version.


## Links

 * [State Machine library](https://github.com/yoreek/Arduino-StateMachine)


## Who do I talk to? ##

 * [Yoreek](https://github.com/yoreek)
