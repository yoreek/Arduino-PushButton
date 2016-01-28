#include <Arduino.h>
#include <PushButton.h>

#define BUTTON_PIN 2
#define LED_PIN    13

PushButton btn(BUTTON_PIN);

void setup() {
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void loop() {
    btn.loop();

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
}
