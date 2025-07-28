# Fall Detection System

This is a **simple fall detection system** using an **MPU 6050 accelerometer/gyroscope** and **NodeMCU**. The system detects falls based on acceleration data and sends real-time notifications to the **Blynk App**. 

---

## Features

- **Fall Detection**: Monitors acceleration changes to detect potential falls.
- **Blynk Integration**: Sends instant notifications to the Blynk app when a fall is detected.
- **Customizable Thresholds**: Adjustable fall sensitivity for different scenarios.
- **Compact and Portable**: Can be easily implemented in wearable devices.

---

## Components Used

1. **NodeMCU**: Microcontroller for processing data and WiFi connectivity.
2. **MPU 6050**: Accelerometer and gyroscope module for measuring motion and orientation.
3. **Blynk App**: Cloud platform for IoT projects to receive notifications.

---

## Circuit Diagram

### Connections:
- **MPU 6050**:
  - **VCC** → 3.3V (NodeMCU)
  - **GND** → GND (NodeMCU)
  - **SDA** → D2 (GPIO 4 on NodeMCU)
  - **SCL** → D1 (GPIO 5 on NodeMCU)

---

## Installation and Setup

### 1. **Hardware Setup**
- Connect the **MPU 6050** module to the **NodeMCU** using the connections listed above.
- Ensure all wires are secure to prevent connection issues.

### 2. **Software Requirements**
- Install the following software:
  - **Arduino IDE**: [Download Here](https://www.arduino.cc/en/software)
  - Blynk library (`Blynk` and `BlynkSimpleEsp8266`): Install from the Arduino IDE Library Manager.
  - MPU6050 library (`MPU6050_light`): Install from the Arduino IDE Library Manager.

### 3. **Create a Blynk Project**
- Download the **Blynk App** on your smartphone (iOS or Android).
- Create a new project in the app:
  - **Project Name**: Fall Detection
  - **Device**: ESP8266
  - **Connection Type**: WiFi
- Add an **Event Notification Widget** to your project:
  1. Tap the "+" button in the app to add a widget.
  2. Select "Event Notification".
  3. Configure the event as:
     - **Event Code**: `fall_detect`
     - **Message**: Fall detected! Check the person immediately.
  4. Save and return to the main dashboard.
- Copy the **Blynk Auth Token** from the app and replace it in the `#define BLYNK_AUTH_TOKEN` section of the code.

### 4. **Configure the Code**
- Open the provided code in **Arduino IDE**.
- Replace the placeholders in the code:
  - Replace `BLYNK_AUTH_TOKEN` with your Blynk Auth Token.
  - Replace `ssid` with your WiFi network name.
  - Replace `pass` with your WiFi password.

### 5. **Upload the Code**
- Connect the **NodeMCU** to your computer via USB.
- Select the correct board and port in **Arduino IDE**:
  - Board: `NodeMCU 1.0 (ESP-12E Module)`
  - Port: Select the appropriate COM port.
- Click **Upload** to upload the code to the NodeMCU.

### 6. **Test the System**
- Power on the NodeMCU and wait for it to connect to WiFi.
- Open the **Serial Monitor** in Arduino IDE to view real-time logs.
- Simulate a fall (e.g., by jerking the MPU 6050 module). If a fall is detected, you will:
  1. See a "Fall detected!" message in the Serial Monitor.
  2. Receive a notification on the Blynk app.

---

## Adjusting the Sensitivity

You can modify the following variables in the code to adjust the sensitivity:
- `FALL_THRESHOLD`: The minimum acceleration change required to trigger a fall. Lower values make the system more sensitive.
- `FALL_DURATION`: The minimum duration (in milliseconds) of acceleration change to register a fall.

---

## Troubleshooting

1. **No WiFi Connection**:
   - Ensure the SSID and password in the code are correct.
   - Verify the WiFi network is active and supports 2.4 GHz (NodeMCU doesn’t support 5 GHz).
2. **MPU 6050 Not Detected**:
   - Check the wiring and connections between the MPU 6050 and NodeMCU.
   - Ensure the SDA and SCL pins are correctly connected to D2 and D1 on the NodeMCU.
3. **No Notifications**:
   - Verify the Blynk Auth Token matches your project token.
   - Ensure the event code in the Blynk app is set to `fall_detect`.
