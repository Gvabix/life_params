#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <DFRobot_BloodOxygen_S.h>   // MAX30102
#include <C:\Users\Gabrysia\Documents\PlatformIO\Projects\ard-life-params\lib\Adafruit_MLX90614\Adafruit-MLX90614-Library-master\Adafruit_MLX90614.h> //mlx90614

#define I2C_ADDRESS 0x57

// MAX30102
DFRobot_BloodOxygen_S_I2C MAX30102(&Wire ,I2C_ADDRESS);


// === GSR Grove Sensor ===
const int gsrPin = A7;  

// ECG 3 Click CS pin
const int ECG_CS = 10;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Starting sensors...");

  Wire.begin();

  // MAX30102 init
  if (!MAX30102.begin()) {
    Serial.println("MAX30102 init failed!");
    while (1);
  }
  MAX30102.sensorStartCollect();
  Serial.println("MAX30102 ready");


  // SPI init for ECG
  SPI.begin();
  pinMode(ECG_CS, OUTPUT);
  digitalWrite(ECG_CS, HIGH);

  Serial.println("All sensors initialized.\n");
}

void loop() {
  Serial.println("===== SENSOR READINGS =====");

  // MAX30102
  MAX30102.getHeartbeatSPO2();
  Serial.print("SpO2: ");
  Serial.print(MAX30102._sHeartbeatSPO2.SPO2);
  Serial.print("% | HR: ");
  Serial.print(MAX30102._sHeartbeatSPO2.Heartbeat);
  Serial.print(" bpm | Temp: ");
  Serial.print(MAX30102.getTemperature_C());
  Serial.println(" °C");

  // GSR
  int gsrValue = analogRead(gsrPin);
  Serial.print("GSR : ");
  Serial.println(gsrValue);

  // ECG SPI read
  digitalWrite(ECG_CS, LOW);
  delayMicroseconds(2);
  byte ecgData = SPI.transfer(0x00);
  digitalWrite(ECG_CS, HIGH);
  Serial.print("ECG SPI Raw: ");
  Serial.println(ecgData);

  Serial.println();
  delay(4000); 
}