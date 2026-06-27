/**
 * Module 1 - Exercise 04 : Memory, Hexadecimal & ASCII
 *
 * Concepts covered:
 *   - Array = a row of boxes in memory, each with an address (index)
 *   - Each box holds 1 byte (uint8_t = 0 to 255)
 *   - Hexadecimal: 0-9 then A=10 B=11 C=12 D=13 E=14 F=15
 *   - ASCII: each character is stored as a number ('H' = 72)
 *
 * No wiring needed — output on Serial Monitor only.
 */

#include <Arduino.h>

#define MEM_SIZE 8
uint8_t memory[MEM_SIZE] = {255, 15, 26, 140, 99, 0, 72, 73};

void printBits(uint8_t val) {
    for (int i = 7; i >= 0; i--) {
        Serial.print((val >> i) & 1);
    }
}

void printAddress(int index) {
    uint8_t val = memory[index];

    Serial.println("-------------------------");
    Serial.print("memory["); Serial.print(index); Serial.println("]");
    Serial.print("  decimal : "); Serial.println(val);
    Serial.print("  binary  : "); printBits(val); Serial.println();
    Serial.print("  hex     : 0x");
    if (val < 16) Serial.print("0");
    Serial.println(val, HEX);
    Serial.print("  ASCII   : ");
    // if (val >= 32 && val < 127) {
    //     Serial.print("'"); Serial.print((char)val); Serial.println("'");
    // } else {
    //     Serial.println("(not printable)");
    // }
    Serial.println("-------------------------");
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Module 1 - Ex04 : Memory, Hex & ASCII");
    Serial.println("======================================");
    Serial.println();
    Serial.println("Array layout:");
    Serial.println("Index:  [0]   [1]   [2]   [3]   [4]   [5]   [6]   [7]");
    Serial.println("Value:  255   15    26    140   99    0     72    73");
    Serial.println("ASCII:  ---   ---   ---   ---   'c'   ---   'H'   'I'");
    Serial.println();
    Serial.print("Enter an address (0 to "); Serial.print(MEM_SIZE - 1); Serial.println(") :");
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');    // wait for Enter
        input.trim();                                   // remove spaces / \r

        int index = input.toInt();

        // validate input
        if (index >= 0 && index < MEM_SIZE) {
            printAddress(index);
        } else {
            Serial.print("  invalid address, enter 0 to ");
            Serial.println(MEM_SIZE - 1);
        }

        // prompt again
        Serial.println();
        Serial.print("Enter an address (0 to "); Serial.print(MEM_SIZE - 1); Serial.println(") :");
    }
}