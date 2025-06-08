# 🔌 Home Automation with ESP32 and Blynk

A smart home automation system using ESP32 and Blynk IoT platform, allowing you to control electrical devices via mobile app and physical switches, with dimmer support for fan control.

---

## 🧰 Features

- Control 4 relays via:
  - Blynk App (Android/iOS)
  - Physical push buttons
- Fan speed control using AC dimmer with zero-crossing detection
- Real-time relay status sync between hardware and app
- Modular, beginner-friendly code
- Internet-based wireless control with ESP32

---

## 📦 Hardware Required

| Component                    | Quantity  |
|------------------------------|-----------|
| ESP32 Dev Board              | 1         |
| 4-Channel Relay Module       | 1         |
| AC Dimmer with ZVC support   | 1         |
| Push Buttons                 | 4         |
| Wires, Breadboard, etc.      | As needed |
| Power Source (5V for ESP32)  | 1         |

---

## 🔌 Pin Configuration

| Function             | ESP32 GPIO |
|----------------------|------------|
| Relay 1 Control      | 1          |
| Relay 2 Control      | 2          |
| Relay 3 Control      | 3          |
| Relay 4 Control      | 4          |
| Button 1             | 7          |
| Button 2             | 8          |
| Button 3             | 9          |
| Button 4             | 10         |
| Fan Dimmer Output    | 11         |
| LED Dimmer Output    | 12         |
| ZVC Input            | 13         |

> **Note**: Use appropriate GPIOs for your ESP32 board; not all boards map GPIO numbers the same way.

---

## 📲 Blynk Configuration

1. Go to [Blynk IoT Console](https://blynk.cloud/)
2. Create a new Template with:
   - **Template ID**: `TMPL3Y7reHYvw`
   - **Device Name**: `Home automation avishkar`
3. Create virtual pins on the dashboard:
   - V1 → Relay 1 Switch
   - V2 → Relay 2 Switch
   - V3 → Relay 3 Switch
   - V4 → Relay 4 Switch
   - V11 → Fan Dimmer Slider
   - V12 → *(reserved for LED dimmer)*

---

## 🔧 Setup Instructions

1. Replace the following credentials in code:
   ```cpp
   #define BLYNK_TEMPLATE_ID "Your_Template_ID"
   #define BLYNK_TEMPLATE_NAME "Your_Template_Name"
   #define BLYNK_AUTH_TOKEN "Your_Auth_Token"

   char ssid[] = "Your_WiFi_Name";
   char pass[] = "Your_WiFi_Password";
