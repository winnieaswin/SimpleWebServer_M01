/**
 * Module 1 - Exercise 07 : ADC — Potentiometer → 5 LEDs Brightness
 *
 * Wiring:
 *   POTENTIOMETER:
 *     Left  pin → GND
 *     Middle pin → GPIO34 (ADC input)
 *     Right pin → 3.3V
 *
 *   LEDs (each with 330Ω resistor to GND):
 *     LED 1 → GPIO26
 *     LED 2 → GPIO27
 *     LED 3 → GPIO14
 *     LED 4 → GPIO12
 *     LED 5 → GPIO13
 *
 * How it works:
 *   0    → 819  : LED1 dims up
 *   819  → 1638 : LED2 dims up
 *   1638 → 2457 : LED3 dims up
 *   2457 → 3276 : LED4 dims up
 *   3276 → 4095 : LED5 dims up
 */

#include <Arduino.h>

#define ADC_PIN     34
#define NUM_LEDS    5

// PWM settings
#define PWM_FREQ    5000
#define PWM_BITS    8       // 0 to 255

// One PWM channel per LED
const int LED_PINS[NUM_LEDS]     = {26, 27, 14, 12, 13};
const int PWM_CHANNELS[NUM_LEDS] = { 0,  1,  2,  3,  4};

// Each LED covers 1/5 of the ADC range
// 0─────819─────1638─────2457─────3276─────4095
// │    LED1  │  LED2  │  LED3  │  LED4  │  LED5 │
#define ZONE (4095 / NUM_LEDS)  // = 819 per LED

void setup() {
    Serial.begin(115200);
    analogReadResolution(12);

    // Setup one PWM channel per LED
    for (int i = 0; i < NUM_LEDS; i++) {
        ledcSetup(PWM_CHANNELS[i], PWM_FREQ, PWM_BITS);
        ledcAttachPin(LED_PINS[i], PWM_CHANNELS[i]);
    }

    Serial.println("Module 1 - Ex07 : Potentiometer → 5 LEDs");
    Serial.println("ADC raw | Voltage | LED1 | LED2 | LED3 | LED4 | LED5");
    Serial.println("--------|---------|------|------|------|------|-----");
}

void loop() {
    int raw       = analogRead(ADC_PIN);
    float voltage = (raw / 4095.0) * 3.3;

    // Update each LED brightness based on its zone
    for (int i = 0; i < NUM_LEDS; i++) {
        int zoneStart = i * ZONE;           // e.g. LED2 starts at 819
        int zoneEnd   = zoneStart + ZONE;   // e.g. LED2 ends  at 1638

        int brightness = 0;

        if (raw <= zoneStart) {
            brightness = 0;                 // before this LED zone → off
        } else if (raw >= zoneEnd) {
            brightness = 255;               // past this LED zone   → full on
        } else {
            // inside this LED zone → fade in
            brightness = map(raw, zoneStart, zoneEnd, 0, 255);
        }

        ledcWrite(PWM_CHANNELS[i], brightness);
    }

    // Print table
    Serial.print(raw);    Serial.print("\t| ");
    Serial.print(voltage, 2); Serial.print("V\t| ");

    for (int i = 0; i < NUM_LEDS; i++) {
        int zoneStart  = i * ZONE;
        int brightness = 0;
        if      (raw <= zoneStart)        brightness = 0;
        else if (raw >= zoneStart + ZONE) brightness = 255;
        else                              brightness = map(raw, zoneStart, zoneStart + ZONE, 0, 255);

        if (brightness < 100) Serial.print(" ");
        if (brightness < 10)  Serial.print(" ");
        Serial.print(brightness);
        Serial.print(" | ");
    }
    Serial.println();

    delay(100);
}