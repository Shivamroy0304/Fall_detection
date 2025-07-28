/*************************************************************
   Fall Detection with MPU6050 + Blynk Cloud Integration
   Device goes ONLINE and sends alert on fall detection
 *************************************************************/

#define BLYNK_TEMPLATE_ID           ""
#define BLYNK_TEMPLATE_NAME         ""
#define BLYNK_AUTH_TOKEN            ""

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <MPU6050_light.h>

// ==== WiFi credentials ====
char ssid[] = "";              // Your WiFi SSID
char pass[] = "";              // Your WiFi password

// ==== MPU6050 setup ====
#define SDA_PIN 4  // D2
#define SCL_PIN 5  // D1

MPU6050 mpu(Wire);

// ==== Fall detection variables ====
const float FALL_THRESHOLD = 2.5;  // adjust if needed
const int FALL_DURATION = 750;    // milliseconds

float prevTotalAcc = 1.0;
unsigned long fallStartTime = 0;
bool fallingDetected = false;

// ==== Blynk timer ====
BlynkTimer timer;

// ==== Setup ====
void setup() {
  Serial.begin(115200);

  Serial.println("Connecting to WiFi...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);

  Wire.begin(SDA_PIN, SCL_PIN);
  byte status = mpu.begin();

  Serial.print("MPU6050 status: ");
  Serial.println(status);
  while (status != 0) {
    Serial.println("Could not connect to MPU6050. Retrying...");
    delay(1000);
    status = mpu.begin();
  }

  Serial.println("Calibrating MPU6050...");
  delay(1000);
  mpu.calcOffsets();  // gyro and accel offsets
  Serial.println("MPU6050 Ready.");

  // You can also start periodic updates or use timer if needed
}

// ==== Loop ====
void loop() {
  Blynk.run();
  mpu.update();

  float accX = mpu.getAccX();
  float accY = mpu.getAccY();
  float accZ = mpu.getAccZ();

  float totalAcc = sqrt(accX * accX + accY * accY + accZ * accZ);

  if (abs(totalAcc - prevTotalAcc) > FALL_THRESHOLD) {
    if (!fallingDetected) {
      fallingDetected = true;
      fallStartTime = millis();
    }
  } else if (fallingDetected && (millis() - fallStartTime > FALL_DURATION)) {
    Serial.println("Fall detected!");
    sendFallNotification();
    fallingDetected = false;
  }

  prevTotalAcc = totalAcc;
  delay(10);  // for stability
}

// ==== Fall Alert ====
void sendFallNotification() {
  Blynk.logEvent("fall_detect", " Fall detected! Check immediately.");
}
