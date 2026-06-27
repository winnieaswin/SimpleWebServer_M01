#include <Arduino.h>
#include <esp_adc_cal.h>

#define ADC_PIN     34
#define R2_OHM      1000.0
#define V_SOURCE    3.3
#define DELAY_MS    1000
#define SAMPLES     64

esp_adc_cal_characteristics_t adc_chars;

void setup() {
    Serial.begin(115200);

    // Calibrate ADC using chip's eFuse Vref
    analogReadResolution(12);
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12, 1100, &adc_chars);

    Serial.println("Module 1 - Ex03 : Ohm's Law & Power");
    Serial.println("-------------------------------");
}

void loop() {
    // Average samples using standard analogRead
    uint32_t sum = 0;
    // for (int i = 0; i < SAMPLES; i++) {
    //     sum += analogRead(ADC_PIN);
    // }
    // uint32_t adcRaw = sum / SAMPLES;

    uint32_t adcRaw = analogRead(ADC_PIN);

    // Convert raw to millivolts using calibration (instead of raw * 3.3 / 4095)
    float vMeasured = esp_adc_cal_raw_to_voltage(adcRaw, &adc_chars) / 1000.0;

    // Ohm's law
    float current_mA    = (vMeasured / R2_OHM) * 1000.0;
    float vR1           = V_SOURCE - vMeasured;
    float r1_calculated = (current_mA > 0) ? (vR1 / (current_mA / 1000.0)) : 0;
    float power_mW      = V_SOURCE * (current_mA / 1000.0) * 1000.0;

    Serial.println("=== Measurements ===");
    Serial.print("ADC raw     : "); Serial.print(adcRaw); Serial.println(" / 4095");
    Serial.print("V measured  : "); Serial.print(vMeasured, 3); Serial.println(" V");
    Serial.print("V across R1 : "); Serial.print(vR1, 3); Serial.println(" V");
    Serial.print("Current (I) : "); Serial.print(current_mA, 2); Serial.println(" mA");
    Serial.print("R1 unknown  : "); Serial.print(r1_calculated, 1); Serial.println(" ohm");
    Serial.print("Power  (W)  : "); Serial.print(power_mW, 2); Serial.println(" mW");
    Serial.println();

    delay(DELAY_MS);
}