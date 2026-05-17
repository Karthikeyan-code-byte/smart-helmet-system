# smart-helmet-system
Developed an IoT-based Smart Helmet Safety System using ESP32 and sensors to improve road safety through accident detection, emergency alert messaging, and alcohol-based ignition control.

Workflow of Our Project:
  When a crash is detected using the MPU6050, the ESP32 sends a signal to our mobile app via Bluetooth. The app then automatically sends an SMS to the registered emergency contacts, including the GPS location of the accident. Additionally, for safety, when the rider's alcohol level exceeds a predefined threshold, the MQ3 sensor detects it and sends a signal to the ESP32, which turns off the relay. For demonstration, we used an LED to represent the engine-when alcohol levels are high, the LED turns off, indicating that the engine would be disabled.

Novelty of Our Project: The automatic engine cut-off based on alcohol detection enhances rider safety and helps prevent accidents caused by drunk driving.
