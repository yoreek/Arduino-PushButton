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
}

