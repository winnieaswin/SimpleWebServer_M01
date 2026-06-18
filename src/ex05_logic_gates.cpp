/**
 * Module 1 - Exercise 05 : Logic Gates
 * 
 * Demonstrates all logic gates using:
 *   - 2 push buttons as inputs  (A and B)
 *   - 5 LEDs as outputs         (AND, OR, NOT, NAND, XOR)
 * 
 * Wiring:
 * 
 *   INPUTS (buttons):
 *     GPIO 18 --> Button A --> GND   (INPUT_PULLUP: pressed = 0, released = 1)
 *     GPIO 19 --> Button B --> GND
 * 
 *   OUTPUTS (LEDs with 330 ohm resistor each):
 *     GPIO 26 --> 330ohm --> LED_AND  --> GND
 *     GPIO 27 --> 330ohm --> LED_OR   --> GND
 *     GPIO 14 --> 330ohm --> LED_NOT  --> GND   (shows NOT A)
 *     GPIO 12 --> 330ohm --> LED_NAND --> GND
 *     GPIO 13 --> 330ohm --> LED_XOR  --> GND
 * 
 * Truth Tables:
 * 
 *   AND : Q = A & B       OR  : Q = A | B
 *   A B Q                 A B Q
 *   0 0 0                 0 0 0
 *   0 1 0                 0 1 1
 *   1 0 0                 1 0 1
 *   1 1 1                 1 1 1
 * 
 *   NOT : Q = !A          NAND: Q = !(A & B)
 *   A Q                   A B Q
 *   0 1                   0 0 1
 *   1 0                   0 1 1
 *                         1 0 1
 *                         1 1 0
 * 
 *   XOR : Q = A ^ B  (eXclusive OR)
 *   A B Q
 *   0 0 0
 *   0 1 1
 *   1 0 1
 *   1 1 0  <-- difference vs OR: both same = 0
 */

#include <Arduino.h>

// ── Pin definitions ──────────────────────────────────────────
#define BTN_A       18
#define BTN_B       19

#define LED_AND     26
#define LED_OR      27
#define LED_NOT_A   14
#define LED_NAND    12
#define LED_XOR     13

// ── State ─────────────────────────────────────────────────────
bool prevA = false;
bool prevB = false;

// ── Helpers ───────────────────────────────────────────────────

// Read button: INPUT_PULLUP means pressed = LOW = true
bool readButton(int pin) {
    return digitalRead(pin) == LOW;
}

void printGateResult(const char* name, bool a, bool b, bool q) {
    Serial.print("  ");
    Serial.print(name);
    Serial.print(" : A=");
    Serial.print(a);
    Serial.print(" B=");
    Serial.print(b);
    Serial.print(" => Q=");
    Serial.println(q);
}

void printSeparator() {
    Serial.println("─────────────────────────────");
}

void printTruthTables() {
    Serial.println("\n╔═══════════════════════════╗");
    Serial.println("║    LOGIC GATES - MODULE 1  ║");
    Serial.println("╚═══════════════════════════╝");

    Serial.println("\n── AND Gate ──  (both must be 1)");
    Serial.println("  A  B  Q");
    Serial.println("  0  0  0");
    Serial.println("  0  1  0");
    Serial.println("  1  0  0");
    Serial.println("  1  1  1  ← only case Q=1");

    Serial.println("\n── OR Gate ──   (at least one = 1)");
    Serial.println("  A  B  Q");
    Serial.println("  0  0  0  ← only case Q=0");
    Serial.println("  0  1  1");
    Serial.println("  1  0  1");
    Serial.println("  1  1  1");

    Serial.println("\n── NOT Gate ──  (inverts A)");
    Serial.println("  A  Q");
    Serial.println("  0  1");
    Serial.println("  1  0");

    Serial.println("\n── NAND Gate ── (AND then NOT)");
    Serial.println("  A  B  Q");
    Serial.println("  0  0  1");
    Serial.println("  0  1  1");
    Serial.println("  1  0  1");
    Serial.println("  1  1  0  ← only case Q=0");

    Serial.println("\n── XOR Gate ──  (different inputs = 1)");
    Serial.println("  A  B  Q");
    Serial.println("  0  0  0");
    Serial.println("  0  1  1");
    Serial.println("  1  0  1");
    Serial.println("  1  1  0  ← same inputs = 0 (diff vs OR)");

    printSeparator();
    Serial.println("Press buttons A and B to test !");
    printSeparator();
}

void updateGates(bool a, bool b) {
    // ── Compute all gates ──────────────────────────
    bool q_and  = a & b;          // AND
    bool q_or   = a | b;          // OR
    bool q_not  = !a;             // NOT A
    bool q_nand = !(a & b);       // NAND
    bool q_xor  = a ^ b;          // XOR

    // ── Drive LEDs ────────────────────────────────
    digitalWrite(LED_AND,   q_and);
    digitalWrite(LED_OR,    q_or);
    digitalWrite(LED_NOT_A, q_not);
    digitalWrite(LED_NAND,  q_nand);
    digitalWrite(LED_XOR,   q_xor);

    // ── Print results ─────────────────────────────
    Serial.println("\n>>> Button change detected !");
    Serial.print("Input  : A="); Serial.print(a);
    Serial.print("  B=");        Serial.println(b);
    Serial.println("Results:");
    printGateResult("AND ", a, b, q_and);
    printGateResult("OR  ", a, b, q_or);
    printGateResult("NOT ", a, b, q_not);
    printGateResult("NAND", a, b, q_nand);
    printGateResult("XOR ", a, b, q_xor);
    printSeparator();
}

// ── Setup ─────────────────────────────────────────────────────
void setup() {
    Serial.begin(115200);

    // Inputs
    pinMode(BTN_A, INPUT_PULLUP);
    pinMode(BTN_B, INPUT_PULLUP);

    // Outputs
    pinMode(LED_AND,   OUTPUT);
    pinMode(LED_OR,    OUTPUT);
    pinMode(LED_NOT_A, OUTPUT);
    pinMode(LED_NAND,  OUTPUT);
    pinMode(LED_XOR,   OUTPUT);

    // Boot: show truth tables
    delay(500);
    printTruthTables();

    // Initial state
    prevA = readButton(BTN_A);
    prevB = readButton(BTN_B);
    updateGates(prevA, prevB);
}

// ── Loop ──────────────────────────────────────────────────────
void loop() {
    bool a = readButton(BTN_A);
    bool b = readButton(BTN_B);

    // Only update when input changes
    if (a != prevA || b != prevB) {
        prevA = a;
        prevB = b;
        updateGates(a, b);
        delay(50);  // debounce
    }
}
