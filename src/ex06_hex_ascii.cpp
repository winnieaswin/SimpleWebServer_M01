/**
 * Module 1 - Exercise 06 : Hexadecimal & ASCII
 * 
 * Interactive lesson — type in Serial Monitor to explore:
 *
 *   Mode 1 : Type a decimal number  (0-255)  → see Hex + Binary + ASCII
 *   Mode 2 : Type a letter/word             → see ASCII codes + Hex + Binary
 *   Mode 3 : Type a hex value  (0x1F)       → convert to Dec + Binary + ASCII
 *
 * No wiring needed — Serial Monitor only.
 *
 * ── Background ──────────────────────────────────────────────────
 *
 *  HEXADECIMAL (Base 16)
 *  Uses digits: 0 1 2 3 4 5 6 7 8 9 A B C D E F
 *
 *  Dec  Hex    Dec  Hex
 *   0    0      8    8
 *   1    1      9    9
 *   2    2     10    A
 *   3    3     11    B
 *   4    4     12    C
 *   5    5     13    D
 *   6    6     14    E
 *   7    7     15    F
 *
 *  1 byte = 2 hex digits (FF = 255 = 11111111)
 *
 *  ASCII (American Standard Code for Information Interchange)
 *  Maps numbers to characters:
 *   32 = SPACE    65 = 'A'   97 = 'a'
 *   48 = '0'      66 = 'B'   98 = 'b'
 *   ...
 *   57 = '9'      90 = 'Z'  122 = 'z'
 */

#include <Arduino.h>

String inputBuffer = "";

// ── Print helpers ─────────────────────────────────────────────

void printBits(uint8_t val) {
    for (int i = 7; i >= 0; i--) {
        Serial.print((val >> i) & 1);
        if (i == 4) Serial.print(" ");  // space between nibbles
    }
}

void printSeparator() {
    Serial.println("─────────────────────────────────────");
}

// ── Full breakdown of one byte ────────────────────────────────

void printByteInfo(uint8_t val) {
    printSeparator();
    Serial.print("DEC  : ");  Serial.println(val);

    Serial.print("HEX  : 0x");
    if (val < 16) Serial.print("0");
    Serial.println(val, HEX);

    Serial.print("BIN  : ");
    printBits(val);
    Serial.println();

    Serial.print("ASCII: ");
    if (val >= 32 && val < 127) {
        Serial.print("'");
        Serial.print((char)val);
        Serial.print("'");
    } else if (val == 0)   Serial.print("NUL (null)");
    else if (val == 8)     Serial.print("BS  (backspace)");
    else if (val == 9)     Serial.print("TAB (tab)");
    else if (val == 10)    Serial.print("LF  (new line)");
    else if (val == 13)    Serial.print("CR  (carriage return)");
    else if (val == 27)    Serial.print("ESC (escape)");
    else if (val == 127)   Serial.print("DEL (delete)");
    else                   Serial.print("(non-printable)");
    Serial.println();
    printSeparator();
}

// ── Full ASCII table ──────────────────────────────────────────

void printAsciiTable() {
    Serial.println("\n╔══════════════════════════════════════╗");
    Serial.println("║           ASCII TABLE                ║");
    Serial.println("╚══════════════════════════════════════╝");
    Serial.println(" Dec | Hex | Char    Dec | Hex | Char");
    Serial.println("-----|-----|------  -----|-----|------");

    // Print printable chars in 2 columns
    for (int i = 32; i <= 79; i++) {
        // Left column
        Serial.print("  ");
        if (i < 100) Serial.print(" ");
        Serial.print(i);
        Serial.print("  | ");
        if (i < 16) Serial.print("0");
        Serial.print(i, HEX);
        Serial.print("  |  '");
        Serial.print((char)i);
        Serial.print("'");

        // Right column
        int j = i + 48;
        if (j <= 127) {
            Serial.print("    ");
            if (j < 100) Serial.print(" ");
            Serial.print(j);
            Serial.print("  | ");
            if (j < 16) Serial.print("0");
            Serial.print(j, HEX);
            Serial.print("  |  '");
            Serial.print((char)j);
            Serial.print("'");
        }
        Serial.println();
    }
    printSeparator();
}

// ── Hex table ─────────────────────────────────────────────────

void printHexTable() {
    Serial.println("\n╔══════════════════════════════════════╗");
    Serial.println("║         HEXADECIMAL TABLE            ║");
    Serial.println("╚══════════════════════════════════════╝");
    Serial.println(" Dec | Hex | Binary");
    Serial.println("-----|-----|─────────────");
    for (int i = 0; i <= 255; i += 16) {
        for (int j = i; j < i + 16 && j <= 255; j++) {
            Serial.print("  ");
            if (j < 100) Serial.print(" ");
            if (j < 10)  Serial.print(" ");
            Serial.print(j);
            Serial.print("  |  ");
            if (j < 16) Serial.print("0");
            Serial.print(j, HEX);
            Serial.print("  | ");
            printBits(j);
            Serial.println();
        }
        Serial.println();
    }
}

// ── Print word as memory table ────────────────────────────────

void printWordMemory(String word) {
    Serial.println("\n=== Memory layout of \"" + word + "\" ===");
    Serial.println(" Addr | Dec | Binary    | Hex  | ASCII");
    Serial.println("------|-----|-----------|------|------");

    for (int i = 0; i < (int)word.length(); i++) {
        uint8_t val = (uint8_t)word[i];

        Serial.print("   ");
        Serial.print(i);
        Serial.print("  |");

        if (val < 100) Serial.print(" ");
        if (val < 10)  Serial.print(" ");
        Serial.print("  ");
        Serial.print(val);
        Serial.print(" | ");

        printBits(val);
        Serial.print(" |  ");

        if (val < 16) Serial.print("0");
        Serial.print(val, HEX);
        Serial.print("  |  '");
        Serial.print((char)val);
        Serial.println("'");
    }
    printSeparator();
}

// ── Menu ──────────────────────────────────────────────────────

void printMenu() {
    Serial.println("\n╔══════════════════════════════════════════╗");
    Serial.println("║   Module 1 - Ex06 : Hex & ASCII Lesson   ║");
    Serial.println("╠══════════════════════════════════════════╣");
    Serial.println("║  Commands (type + Enter):                ║");
    Serial.println("║  0-255     → show Dec/Hex/Bin/ASCII      ║");
    Serial.println("║  hello     → show word as memory table   ║");
    Serial.println("║  table     → print full ASCII table      ║");
    Serial.println("║  hex       → print Hex table 0-255       ║");
    Serial.println("║  quiz      → start a quiz !              ║");
    Serial.println("╚══════════════════════════════════════════╝");
    Serial.println("Type a command and press Enter:");
}

// ── Quiz ──────────────────────────────────────────────────────

int quizScore   = 0;
int quizTotal   = 0;
bool quizActive = false;
uint8_t quizValue;
int quizType;   // 0=dec→hex  1=dec→ascii  2=ascii→dec

void startQuiz() {
    quizActive = true;
    quizScore  = 0;
    quizTotal  = 0;
    Serial.println("\n=== QUIZ MODE ===");
    Serial.println("Answer each question. Type 'exit' to stop.\n");
}

void askQuestion() {
    quizValue = random(32, 127);    // printable ASCII range
    quizType  = random(0, 3);

    quizTotal++;
    Serial.print("\nQuestion "); Serial.print(quizTotal);
    Serial.print(" | Score: "); Serial.print(quizScore);
    Serial.print("/"); Serial.println(quizTotal - 1);

    if (quizType == 0) {
        Serial.print("  Dec "); Serial.print(quizValue);
        Serial.println(" → Hex ? (e.g. 1F)");
    } else if (quizType == 1) {
        Serial.print("  Dec "); Serial.print(quizValue);
        Serial.println(" → ASCII character ?");
    } else {
        Serial.print("  ASCII '"); Serial.print((char)quizValue);
        Serial.println("' → Dec value ?");
    }
}

void checkQuizAnswer(String answer) {
    answer.trim();
    answer.toUpperCase();
    bool correct = false;

    if (quizType == 0) {
        // Expected: hex string
        String expected = String(quizValue, HEX);
        expected.toUpperCase();
        if (expected.length() == 1) expected = "0" + expected;
        correct = (answer == expected);
        if (!correct) {
            Serial.print("  ✗ Wrong! Answer was: ");
            Serial.println(expected);
        }
    } else if (quizType == 1) {
        // Expected: single char
        correct = (answer.length() == 1 && answer[0] == (char)quizValue);
        if (!correct) {
            Serial.print("  ✗ Wrong! Answer was: '");
            Serial.print((char)quizValue);
            Serial.println("'");
        }
    } else {
        // Expected: decimal number
        correct = (answer.toInt() == quizValue);
        if (!correct) {
            Serial.print("  ✗ Wrong! Answer was: ");
            Serial.println(quizValue);
        }
    }

    if (correct) {
        quizScore++;
        Serial.println("  ✓ Correct!");
    }

    // Show byte info after each question
    printByteInfo(quizValue);
    askQuestion();
}

// ── Process input ─────────────────────────────────────────────

void processInput(String input) {
    input.trim();
    if (input.length() == 0) return;

    // Quiz mode
    if (quizActive) {
        if (input.equalsIgnoreCase("exit")) {
            quizActive = false;
            Serial.print("\n=== Quiz finished! Score: ");
            Serial.print(quizScore); Serial.print("/");
            Serial.println(quizTotal);
            printMenu();
        } else {
            checkQuizAnswer(input);
        }
        return;
    }

    // Normal commands
    if (input.equalsIgnoreCase("table")) {
        printAsciiTable();
        printMenu();

    } else if (input.equalsIgnoreCase("hex")) {
        printHexTable();
        printMenu();

    } else if (input.equalsIgnoreCase("quiz")) {
        startQuiz();
        askQuestion();

    } else if (input.toInt() > 0 || input == "0") {
        // Decimal number
        int val = input.toInt();
        if (val >= 0 && val <= 255) {
            printByteInfo((uint8_t)val);
        } else {
            Serial.println("  ! Enter a value between 0 and 255");
        }
        printMenu();

    } else if (input.startsWith("0x") || input.startsWith("0X")) {
        // Hex input like 0x1F
        long val = strtol(input.c_str(), nullptr, 16);
        if (val >= 0 && val <= 255) {
            Serial.print("Hex input: "); Serial.println(input);
            printByteInfo((uint8_t)val);
        } else {
            Serial.println("  ! Hex value must be 0x00 to 0xFF");
        }
        printMenu();

    } else {
        // Treat as a word / string
        printWordMemory(input);
        printMenu();
    }
}

// ── Setup / Loop ──────────────────────────────────────────────

void setup() {
    Serial.begin(115200);
    delay(500);
    randomSeed(analogRead(0));
    printMenu();
}

void loop() {
    while (Serial.available()) {
        char c = Serial.read();
        if (c == '\n' || c == '\r') {
            if (inputBuffer.length() > 0) {
                Serial.print("> "); Serial.println(inputBuffer);
                processInput(inputBuffer);
                inputBuffer = "";
            }
        } else {
            inputBuffer += c;
        }
    }
}
