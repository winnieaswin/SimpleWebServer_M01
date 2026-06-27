/**
 * Module 1 - Exercise 02 : Decimal to Binary counter
 * 
 * Concepts covered:
 *   - Decimal vs Binary (Bit = 0 or 1)
 *   - 8 bits = 1 Byte = max value 255
 *   - 2^7=128, 2^6=64, 2^5=32, 2^4=16, 2^3=8, 2^2=4, 2^1=2, 2^0=1
 *   - Counter 0 → 255 displayed in binary on Serial Monitor
 * 
 * Wiring (4-bit version using 4 LEDs):
 *   GPIO 12 = bit 3 (value 8)
 *   GPIO 14 = bit 2 (value 4)
 *   GPIO 27 = bit 1 (value 2)
 *   GPIO 26 = bit 0 (value 1)
 *   Each pin --> 330ohm resistor --> LED --> GNDz
 */

#include <Arduino.h>

// 4 LEDs = 4 bits => counts 0 to 15
#define BIT0_PIN  26    // 2^0 = 1
#define BIT1_PIN  27    // 2^1 = 2
#define BIT2_PIN  14    // 2^2 = 4
#define BIT3_PIN  12    // 2^3 = 8

void printBinary(uint8_t value) {
    Serial.print("Dec: ");
    Serial.print(value);
    Serial.print("  Hex: 0x");
    Serial.print(value, HEX);
    Serial.print("  Bin: ");
    for (int i = 7; i >= 0; i--) {
        Serial.print((value >> i) & 1);
        if (i == 4) Serial.print(" ");  // space between nibbles
    }
    Serial.println();
}

void setLEDs(uint8_t value) {
    digitalWrite(BIT0_PIN, (value >> 0) & 1);
    digitalWrite(BIT1_PIN, (value >> 1) & 1);
    digitalWrite(BIT2_PIN, (value >> 2) & 1);
    digitalWrite(BIT3_PIN, (value >> 3) & 1);
}

void setup() {
    Serial.begin(115200);
    pinMode(BIT0_PIN, OUTPUT);
    pinMode(BIT1_PIN, OUTPUT);
    pinMode(BIT2_PIN, OUTPUT);
    pinMode(BIT3_PIN, OUTPUT);

    Serial.println("Module 1 - Ex02 : Decimal to Binary counter");
    Serial.println("Bit weights: 128 | 64 | 32 | 16 | 8 | 4 | 2 | 1");
    Serial.println("---------------------------------------------------");
}

void loop() {
    // Count from 0 to 15 (4 bits)
    for (uint8_t i = 0; i <= 15; i++) {
        setLEDs(i);
        printBinary(i);
        delay(500);
    }
    Serial.println("--- restart ---");
}
