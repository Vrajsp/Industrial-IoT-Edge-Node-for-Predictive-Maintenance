### 1. Power & Common Rails
| Source | Destination | Note |
| :--- | :--- | :--- |
| **USB / Vin** | **ESP32 5V/Vin** | Main power input |
| **ESP32 GND** | **Breadboard Power Rail (-)** | Common Ground |
| **ESP32 3V3** | **Breadboard Power Rail (+)** | 3.3V Logic Supply for sensors |

### 2. MPU-6050 (IMU) Connections
| MPU-6050 Pin | ESP32 Pin | Function |
| :--- | :--- | :--- |
| **VCC** | 3V3 | Power (3.3V) |
| **GND** | GND | Ground |
| **SCL** | GPIO 22 | I2C Clock |
| **SDA** | GPIO 21 | I2C Data |
| **INT** | GPIO 19 | Interrupt (Optional) |

### 3. Status LED (Output)
| LED Component | ESP32 Pin | Note |
| :--- | :--- | :--- |
| **Anode (+)** | GPIO 2 | Long leg of LED |
| **Cathode (-)** | GND | Short leg (via 220Ω Resistor) |
