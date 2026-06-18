/**
 * Module 1 - Exercise 03 : Ohm's Law & Power (W = V x I)
 * 
 * Concepts covered:
 *   - V = I x R  (Ohm's law)
 *   - W = V x I  (Power formula)
 *   - ADC : reads analog voltage (0 → 3.3V mapped to 0 → 4095)
 *   - Scientific notation : milli(m), micro(µ), kilo(k)
 * 
 * Circuit:
 *   3.3V --> R1 (known, e.g. 1000 ohm) --> R2 (unknown) --> GND
 *                                      |
 *                                   GPIO34 (ADC input)
 * 
 *   By reading voltage at the middle point, we can calculate:
 *   - Current through circuit: I = V_source / (R1 + R2)
 *   - Power consumed: W = V x I
 */

#include <Arduino.h>

#define ADC_PIN     34      // GPIO34 = ADC input (input only pin)
#define R1_OHM      1000.0  // Known resistor = 1k ohm
#define V_SOURCE    3.3     // ESP32 supply voltage
#define ADC_MAX     4095.0  // 12-bit ADC
#define DELAY_MS    1000

void setup() {
    Serial.begin(115200);
    analogReadResolution(12);   // 12 bits = 0 to 4095
    Serial.println("Module 1 - Ex03 : Ohm's Law & Power");
    Serial.println("V = I x R    |    W = V x I");
    Serial.println("-------------------------------");
}

void loop() {
    // Read ADC
    int adcRaw = analogRead(ADC_PIN);

    // Convert ADC value to voltage
    float vMeasured = (adcRaw / ADC_MAX) * V_SOURCE;

    // Voltage across R1 = V_source - V_measured
    float vR1 = V_SOURCE - vMeasured;

    // Current through circuit: I = V / R (Ohm's law)
    float current_A  = vR1 / R1_OHM;           // Amps
    float current_mA = current_A * 1000.0;      // milliAmps (x10^-3)

    // Unknown resistor R2 = V_measured / I
    float r2 = (current_A > 0) ? (vMeasured / current_A) : 0;

    // Power: W = V x I
    float power_W  = V_SOURCE * current_A;
    float power_mW = power_W * 1000.0;          // milliWatts

    // Print results
    Serial.println("=== Measurements ===");
    Serial.print("ADC raw     : "); Serial.print(adcRaw); Serial.println(" / 4095");
    Serial.print("V measured  : "); Serial.print(vMeasured, 3); Serial.println(" V");
    Serial.print("Current (I) : "); Serial.print(current_mA, 2); Serial.println(" mA");
    Serial.print("R2 unknown  : "); Serial.print(r2, 1); Serial.println(" ohm");
    Serial.print("Power  (W)  : "); Serial.print(power_mW, 2); Serial.println(" mW");
    Serial.println();

    delay(DELAY_MS);
}
