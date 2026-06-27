/**
 * Module 1 - Exercise 08 : ADC — Light Sensor (LDR)
 *
 * Concepts covered:
 *   - LDR (Light Dependent Resistor) — resistance changes with light
 *   - Voltage divider : two resistors sharing a voltage
 *   - ADC reading and threshold detection
 *   - Mapping sensor values to real-world meaning
 *
 * Wiring (Voltage Divider):
 *
 *   3.3V
 *    |
 *   [10kΩ fixed resistor]
 *    |
 *    +────→ GPIO34 (ADC reads voltage here)
 *    |
 *   [LDR]   ← resistance decreases when light increases
 *    |
 *   GND
 *
 * How it works:
 *   Bright light → LDR resistance LOW  → more voltage on GPIO34 → ADC reads HIGH
 *   Dark         → LDR resistance HIGH → less voltage on GPIO34 → ADC reads LOW
 *
 * LEDs:
 *   GPIO26 → 330Ω → GREEN LED  (lights up when BRIGHT)
 *   GPIO27 → 330Ω → RED LED    (lights up when DARK)
 */

#include <Arduino.h>

#define ADC_PIN         34
#define LED_GREEN       26      // Bright indicator
#define LED_RED         27      // Dark indicator

// Threshold: above = bright, below = dark
// Adjust this value based on your environment (0-4095)
#define THRESHOLD       2000

// Smoothing: average of last N readings
#define SAMPLES         10

int readings[SAMPLES];
int readIndex = 0;
long total    = 0;

void setup() {
    Serial.begin(115200);
    analogReadResolution(12);

    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED,   OUTPUT);

    // Initialize smoothing buffer
    for (int i = 0; i < SAMPLES; i++) readings[i] = 0;

    Serial.println("Module 1 - Ex08: Light Sensor (LDR) with ADC");
    Serial.println("Cover the LDR with your hand → RED LED ON");
    Serial.println("Shine a light on it          → GREEN LED ON");
    Serial.println();
    Serial.println("Raw  | Smoothed | Voltage | Level      | Status");
    Serial.println("-----|----------|---------|------------|-------");
}

// Smooth out noisy ADC readings using a rolling average
int smoothedRead(int newVal) {
    total -= readings[readIndex];
    readings[readIndex] = newVal;
    total += newVal;
    readIndex = (readIndex + 1) % SAMPLES;
    return total / SAMPLES;
}

String getLightLevel(int val) {
    if (val > 3500) return "Very bright";
    if (val > 2500) return "Bright     ";
    if (val > 1500) return "Dim        ";
    if (val > 500)  return "Dark       ";
    return "Very dark  ";
}

void loop() {
    int raw      = analogRead(ADC_PIN);
    int smoothed = smoothedRead(raw);
    float voltage = (smoothed / 4095.0) * 3.3;

    // Decide bright or dark
    bool isBright = smoothed > THRESHOLD;
    digitalWrite(LED_GREEN, isBright);
    digitalWrite(LED_RED,   !isBright);

    // Print
    Serial.print(raw);
    Serial.print("\t| ");
    Serial.print(smoothed);
    Serial.print("\t| ");
    Serial.print(voltage, 2);
    Serial.print("V\t| ");
    Serial.print(getLightLevel(smoothed));
    Serial.print(" | ");
    Serial.println(isBright ? "☀ BRIGHT → GREEN" : "🌙 DARK  → RED");

    delay(200);
}
