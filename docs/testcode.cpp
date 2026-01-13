/*
 * Project: IIoT Predictive Maintenance Node
 * Author: Viraj [Last Name]
 * Platform: ESP32
 * Description: Vibration analysis and MQTT telemetry for industrial motor health.
 */

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <PubSubClient.h>

// ------------------- Configuration ------------------- //
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "broker.hivemq.com"; // Public broker for testing

// Pin Definitions
#define STATUS_LED 2

// Thresholds (ISO 10816 Standard approximation)
const float VIBRATION_THRESHOLD = 5.0; // m/s^2

// Objects
Adafruit_MPU6050 mpu;
WiFiClient espClient;
PubSubClient client(espClient);

// Global Variables
unsigned long lastMsg = 0;
#define MSG_INTERVAL 2000 // Send data every 2 seconds

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming messages (e.g., remote reset or config change)
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("factory/status", "Node Online");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(STATUS_LED, OUTPUT);

  // Initialize I2C
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  
  // Configure MPU6050
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > MSG_INTERVAL) {
    lastMsg = now;

    // 1. Data Acquisition
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // 2. Signal Processing (Calculate Total Acceleration Vector)
    // We remove gravity (approx 9.8) to find dynamic vibration
    float totalAccel = sqrt(pow(a.acceleration.x, 2) + 
                            pow(a.acceleration.y, 2) + 
                            pow(a.acceleration.z, 2));
    
    float vibrationMetric = abs(totalAccel - 9.81);

    // 3. Logic Control
    if (vibrationMetric > VIBRATION_THRESHOLD) {
      digitalWrite(STATUS_LED, HIGH); // Alarm
    } else {
      digitalWrite(STATUS_LED, LOW); // Normal
    }

    // 4. Telemetry Formatting (JSON structure)
    char msg[100];
    snprintf(msg, 75, "{\"vib\": %.2f, \"temp\": %.2f, \"status\": \"%s\"}", 
             vibrationMetric, 
             temp.temperature, 
             (vibrationMetric > VIBRATION_THRESHOLD ? "CRITICAL" : "OK"));

    Serial.print("Publishing message: ");
    Serial.println(msg);
    
    // 5. Transmission
    client.publish("factory/motor/1", msg);
  }
}
