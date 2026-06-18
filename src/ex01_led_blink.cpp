/**
 * Module 1 - Exercise 01 : Turn LED ON / OFF
 * 
 * Concepts covered:
 *   - Digital output (DC signal = 0 or 1)
 *   - GPIO pin as voltage source (3.3V = HIGH, 0V = LOW)
 *   - Ohm's law : V = I x R
 *     => LED needs ~10mA, ESP32 outputs 3.3V
 *     => R = V / I = 3.3V / 0.010A = 330 ohm resistor
 * 
 * Wiring:
 *   GPIO2 --> 330ohm resistor --> LED (+) --> LED (-) --> GND
 */

#include <Arduino.h>

#define LED_PIN 2       // GPIO2 = built-in LED on most ESP32 DevKit
#define DELAY_MS 1000   // 1000ms = 1 second

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);   // Configure pin as OUTPUT (DC digital)
    Serial.println("Module 1 - Ex01: LED Blink");
}

void loop() {
    // Turn LED ON  => GPIO outputs 3.3V (HIGH = bit 1)
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ON  => Bit = 1 => 3.3V");
    delay(DELAY_MS);

    // Turn LED OFF => GPIO outputs 0V (LOW = bit 0)
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED OFF => Bit = 0 => 0V");
    delay(DELAY_MS);
}
