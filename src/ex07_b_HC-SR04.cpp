/**
 * Module 1 - Exercise 07 : HC-SR04 → 5 LEDs Brightness
 *
 * Concepts covered:
 *   - HC-SR04 ultrasonic sensor (distance measurement)
 *   - PWM to control LED brightness
 *   - map() to scale distance to brightness
 *
 * Wiring:
 *   HC-SR04:
 *     VCC  → 5V
 *     GND  → GND
 *     TRIG → GPIO32
 *     ECHO → GPIO33
 *
 *   LEDs (each with 330Ω resistor to GND):
 *     LED1 → GPIO26
 *     LED2 → GPIO27
 *     LED3 → GPIO14
 *     LED4 → GPIO12
 *     LED5 → GPIO13
 *
 * How it works:
 *   Close hand (5cm)  → all LEDs on
 *   Far away  (50cm)  → all LEDs off
 */

#include <Arduino.h>

#define TRIG_PIN    32
#define ECHO_PIN    33
#define NUM_LEDS    5

// Distance range (cm)
#define DIST_MIN    5       // closest  → all on
#define DIST_MAX    50      // furthest → all off

// PWM settings
#define PWM_FREQ    5000
#define PWM_BITS    8       // 0 to 255

const int LED_PINS[NUM_LEDS]     = {26, 27, 14, 12, 13};
const int PWM_CHANNELS[NUM_LEDS] = { 0,  1,  2,  3,  4};

// --------------------------------------------------------
//  Read distance from HC-SR04
//  1. Send 10µs pulse on TRIG
//  2. Measure how long ECHO stays HIGH
//  3. Distance (cm) = duration / 58
// --------------------------------------------------------
float readDistance() {
    // Send trigger pulse
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Measure echo duration (timeout after 30ms = ~5m)
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);

    if (duration == 0) return -1;           // nothing detected

    return duration / 58.0;                 // convert to cm
}

void setup() {
    Serial.begin(115200);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    for (int i = 0; i < NUM_LEDS; i++) {
        ledcSetup(PWM_CHANNELS[i], PWM_FREQ, PWM_BITS);
        ledcAttachPin(LED_PINS[i], PWM_CHANNELS[i]);
    }

    Serial.println("Module 1 - Ex07 : HC-SR04 → 5 LEDs");
    Serial.println("Dist(cm) | LED1 | LED2 | LED3 | LED4 | LED5");
    Serial.println("---------|------|------|------|------|-----");
}

void loop() {
    float dist = readDistance();

    // Handle out of range
    if (dist < 0) {
        Serial.println("No object detected");
        for (int i = 0; i < NUM_LEDS; i++) ledcWrite(PWM_CHANNELS[i], 0);
        delay(100);
        return;
    }

    // Clamp distance to our range
    dist = constrain(dist, DIST_MIN, DIST_MAX);

    // Each LED covers 1/5 of the distance range
    float zone = (DIST_MAX - DIST_MIN) / (float)NUM_LEDS;   // = 9cm per LED

    // dist close → LEDs on  /  dist far → LEDs off
    // so we invert: work with (DIST_MAX - dist) instead of dist
    float invertedDist = DIST_MAX - dist;
    float invertedMax  = DIST_MAX - DIST_MIN;   // = 45cm

    // Update each LED
    for (int i = 0; i < NUM_LEDS; i++) {
        float zoneStart = i * zone;
        float zoneEnd   = zoneStart + zone;

        int brightness = 0;

        if (invertedDist <= zoneStart) {
            brightness = 0;
        } else if (invertedDist >= zoneEnd) {
            brightness = 255;
        } else {
            brightness = (int)((invertedDist - zoneStart) / zone * 255);
        }

        ledcWrite(PWM_CHANNELS[i], brightness);
    }

    // Print table
    Serial.print(dist, 1); Serial.print("cm\t| ");

    for (int i = 0; i < NUM_LEDS; i++) {
        float zoneStart    = i * zone;
        float zoneEnd      = zoneStart + zone;
        float invertedDist = DIST_MAX - dist;

        int brightness = 0;
        if      (invertedDist <= zoneStart) brightness = 0;
        else if (invertedDist >= zoneEnd)   brightness = 255;
        else    brightness = (int)((invertedDist - zoneStart) / zone * 255);

        if (brightness < 100) Serial.print(" ");
        if (brightness < 10)  Serial.print(" ");
        Serial.print(brightness);
        Serial.print(" | ");
    }
    Serial.println();

    delay(100);
}