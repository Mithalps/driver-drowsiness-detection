#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BUZZER 8
LiquidCrystal_I2C lcd(0x27, 16, 2);

char prevState = '0'; // store previous state

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(BUZZER, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Driver Drowsiness");
  delay(1500);
  lcd.clear();
  lcd.print("Monitoring...");
}

void loop() {
  if (Serial.available()) {
    char state = Serial.read();

    // React only if state changes
    if (state != prevState) {
      prevState = state;

      if (state == '1') {
        // 🔴 Drowsy detected
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DROWSY!");
        lcd.setCursor(0, 1);
        lcd.print("WAKE UP!");

        // Long beep alert (about 15 seconds total)
        for (int i = 0; i < 20; i++) {  // Repeat beep 20 times
          tone(BUZZER, 2000);  // Start buzzer (2 kHz)
          delay(400);          // Sound duration
          noTone(BUZZER);      // Stop buzzer
          delay(300);          // Pause between beeps
        }
      } 
      else if (state == '0') {
        // 🟢 Awake
        noTone(BUZZER);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("You are alert");
        lcd.setCursor(0, 1);
        lcd.print("Monitoring...");
      }
    }
  }
}
