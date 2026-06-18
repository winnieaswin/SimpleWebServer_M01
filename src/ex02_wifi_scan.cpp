#include <Arduino.h>

void setup() {
  Serial.begin(115200);
}

void loop() {

  // ── Step 1: Define a string ──────────────────────────
  String text = "Hello Module2";

  // ── Step 2: Loop through each character ──────────────
  for (int i = 0; i < text.length(); i++) {

    char c = text[i];           // Get each character
    int  ascii = (int)c;        // Convert char → ASCII number

    // ── Step 3: Print Char and HEX ───────────────────────
    Serial.print("'");
    Serial.print(c);            // Show the character
    Serial.print("'  ->  HEX: ");
    Serial.println(ascii, HEX); // Print as HEX (built-in Arduino)
  }

  Serial.println("--- Done ---");
  delay(3000); // Wait 3 sec then repeat
}
