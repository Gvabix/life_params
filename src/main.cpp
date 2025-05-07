#include <Arduino.h>
#include <Wire.h>
#include <DFRobot_MAX30102.h>
#include "heartRate.h"
#include <SPI.h>
#include <C:\Users\Gabrysia\Documents\PlatformIO\Projects\biosensor-esp32\lib\Adafruit_MLX90614\Adafruit-MLX90614-Library-master\Adafruit_MLX90614.h>


DFRobot_MAX30102 particleSensor;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#define GSR_PIN 34  // Pin analogowy dla GSR Sensor (Grove)
#define REPORTING_PERIOD_MS 1000
uint32_t tsLastReport = 0;

#define SCK_PIN 18    // Serial Clock (SCK)
#define MISO_PIN 19   // Master In Slave Out (MISO)
#define MOSI_PIN 23   // Master Out Slave In (MOSI)
#define CS_PIN 5      // Chip Select (CS)
SPIClass spi(VSPI);

void setup() {
  Wire.begin(21,22);
  Serial.begin(115200);
  delay(1000);

  // Skanowanie I2C
  Serial.println("Skanowanie I2C...");
  byte count = 0;
  for (byte i = 1; i < 127; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Znaleziono urządzenie na adresie 0x");
      Serial.println(i, HEX);
      count++;
    }
    delay(10);
  }

  if (count == 0)
    Serial.println("Nie znaleziono żadnych urządzeń.");
  else
    Serial.println("Skanowanie zakończone.");

 //  Inicjalizacja MLX90614
    if (!mlx.begin()) {
      Serial.println("Nie znaleziono czujnika MLX90614!");
      while (1);
    }
  
    Serial.println("MLX90614 gotowy.");

  spi.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  // Inicjalizacja MAX30102
//   if (!particleSensor.begin()) {
//     Serial.println("Nie znaleziono czujnika MAX30102.");
//     delay(1000);
//   }

//   Serial.println("MAX30102 gotowy.");
//   particleSensor.sensorConfiguration();
}

void loop() {
  // int32_t heartRate = 0;
  // int32_t SPO2 = 0;
  // int8_t heartRateValid = 0;
  // int8_t SPO2Valid = 0;

  // // Uzyskanie wartości tętna i saturacji
  // particleSensor.heartrateAndOxygenSaturation(&SPO2, &SPO2Valid, &heartRate, &heartRateValid);

  // if (heartRateValid) {
  //   Serial.print("Tętno: ");
  //   Serial.print(heartRate);
  //   Serial.print(" bpm | ");
  // } else {
  //   Serial.print("Niepoprawne dane tętna | ");
  // }

  // if (SPO2Valid) {
  //   Serial.print("SpO2: ");
  //   Serial.print(SPO2);
  //   Serial.println(" %");
  // } else {
  //   Serial.print("Niepoprawne dane SpO2");
  // }

  float tempMLX = mlx.readObjectTempC();
  Serial.print("Temp (bezkontaktowa): ");
  Serial.print(tempMLX);
  Serial.println(" °C");

  int gsrValue = analogRead(GSR_PIN);
  Serial.print("GSR (opór skóry): ");
  Serial.println(gsrValue);

  digitalWrite(CS_PIN, LOW);
  byte data = spi.transfer(0x00); // Przykładowa komunikacja SPI
  digitalWrite(CS_PIN, HIGH); // Dezaktywowanie czujnika

  // Wyświetlanie odczytów EKG na Serial Monitorze
  Serial.print("EKG data: ");
  Serial.println(data);

  delay(500);
}