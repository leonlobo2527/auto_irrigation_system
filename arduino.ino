#include <LiquidCrystal.h>

const int moisturePin = A5;
const int pumpPin = 7;
const int soil_threshold = 50;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(moisturePin, INPUT);
  pinMode(pumpPin, OUTPUT);
}

void loop() {
  // Read the moisture level from the sensor
  int moistureLevel = analogRead(moisturePin);

  // Map the moisture level to a range (0 - 100)
  int moisturePercentage = map(moistureLevel, 0, 1023, 100, 0);
  String moistureString = String(moisturePercentage);

  // Print the moisture level on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Moisture% = ");
  lcd.print(appendZero(moistureString));

  if (moisturePercentage < soil_threshold) {
    // Turn on the pump
    digitalWrite(pumpPin, LOW);
  } else {
    // Turn off the pump
    digitalWrite(pumpPin, HIGH);
  }
  // Send data to NodeMCU
  Serial.println(moistureString);
  delay(1000);
}

String appendZero(String numberString) {
  if (numberString.length() == 1) {
    numberString = "0" + numberString;
  }
  return numberString;
}
