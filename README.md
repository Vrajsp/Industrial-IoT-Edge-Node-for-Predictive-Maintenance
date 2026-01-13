# Industrial-IoT-Edge-Node-for-Predictive-Maintenance

## IIoT Predictive Maintenance Node (ESP32)

## Project Overview
This repository hosts the firmware and hardware documentation for an **Industrial IoT Edge Node** designed for predictive maintenance of induction motors. The system utilizes an ESP32 microcontroller and MPU-6050 accelerometer to perform real-time vibration analysis and thermal monitoring. By detecting anomalies in vibration patterns (ISO 10816 compliance), the system predicts equipment failure before it occurs, facilitating data-driven maintenance strategies.

## Key Features
* **Edge Processing:** Local calculation of acceleration vectors to reduce cloud latency.
* **Real-time Telemetry:** MQTT-based transmission of health metrics (Vibration RMS, Temperature).
* **Anomaly Detection:** On-device thresholding for immediate local alerting.
* **Scalable Architecture:** Designed for integration with AWS IoT Core or Azure IoT Hub.

## Tech Stack
* **Hardware:** ESP32-WROOM-32, MPU-6050 IMU.
* **Firmware:** C++ (Arduino Framework).
* **Protocols:** I2C (Sensor Interface), MQTT (Network Layer), TCP/IP.
* **Tools:** VS Code (PlatformIO), Wireshark (Packet Analysis).

## Hardware Interface
### Pin Mapping
| ESP32 GPIO | Component Pin | Description |
| :--- | :--- | :--- |
| **21** | SDA | I2C Data Line |
| **22** | SCL | I2C Clock Line |
| **3V3** | VCC | 3.3V Logic Supply |
| **GND** | GND | Common Ground |

*Note: Schematic diagram available in the `/docs` directory.*

## 📊 Usage Guide
1.  **Hardware Setup:** Mount the MPU-6050 securely to the chassis of the motor or test equipment. Ensure rigid mechanical coupling for accurate vibration transfer.
2.  **Configuration:** Update `ssid`, `password`, and `mqtt_server` in `main.cpp`.
3.  **Deployment:** Flash the firmware using PlatformIO or Arduino IDE.
4.  **Monitoring:** Subscribe to the MQTT topic `factory/motor/1` to view the data stream.

## 📜 Future Roadmap
* Implementation of FFT (Fast Fourier Transform) for frequency domain analysis.
* Integration of Deep Sleep modes for battery-operated deployment.
* Development of a React.js dashboard for historical data visualization.

## ⚖️ License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
**Author:** Viraj  
*Electronics Engineering Undergraduate*
