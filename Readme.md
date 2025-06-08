# ESP32 Home Automation System with Blynk and Voice Control

## Overview
This project creates a smart home system using ESP32 for:
- Remote control via Blynk app/web dashboard
- Physical switch integration
- Voice commands via Dialogflow
- AC fan dimming with zero-cross detection
- 4-channel relay control

```mermaid
graph TD
    A[User Interface] -->|Commands| B(Blynk Cloud)
    B --> C(ESP32 Microcontroller)
    C --> D1[Relay 1]
    C --> D2[Relay 2]
    C --> D3[Relay 3]
    C --> D4[Relay 4]
    C --> E[Fan Dimmer]
    F[Voice Assistant] -->|HTTP Requests| B
    G[Physical Buttons] --> C

    ### Hardware Components

| Component      | GPIO Pin | Function                  |
|----------------|----------|---------------------------|
| Relay 1        | GPIO1    | Appliance control         |
| Relay 2        | GPIO2    | Appliance control         |
| Relay 3        | GPIO3    | Appliance control         |
| Relay 4        | GPIO4    | Appliance control         |
| Button 1       | GPIO7    | Manual toggle             |
| Button 2       | GPIO8    | Manual toggle             |
| Button 3       | GPIO9    | Manual toggle             |
| Button 4       | GPIO10   | Manual toggle             |
| Fan Dimmer     | GPIO11   | AC fan speed control      |
| Zero-Cross Det.| GPIO13   | AC waveform detection     |
| LED Dimmer     | GPIO12   | (Reserved for future)     |


### Blynk Virtual Pins

| Virtual Pin | Component   | Control Type |
|-------------|-------------|--------------|
| V1          | Relay 1     | Switch       |
| V2          | Relay 2     | Switch       |
| V3          | Relay 3     | Switch       |
| V4          | Relay 4     | Switch       |
| V11         | Fan         | Slider       |
| V12         | LED Dimmer  | Slider       |

### Key Features

#### Multi-Control Interface
- Blynk app/web dashboard  
- Physical push buttons  
- Voice commands  

#### Real-time Synchronization
- State sync on Blynk connection  
- Instant cloud updates  

#### Safe AC Dimming
- Zero-cross detection  
- Phase-angle control  

#### Voice Control Integration
- Dialogflow NLP processing  
- HTTP webhook to Blynk  


---

# Setup Instructions

---

## Hardware Assembly

- Connect **relays** to appliances  
- Install **zero-cross detector** circuit  
- Wire **buttons** with **pull-up resistors**

---

## 📱 Blynk Configuration
graph LR
    A[Create Blynk Template] --> B[Add 4 Switch Widgets]
    B --> C[Add 2 Slider Widgets]
    C --> D[Bind to V1-V4/V11-V12]

### 💻 Code
```cpp
char ssid[] = "Your_SSID";
char pass[] = "Your_PASSWORD";
Blynk.begin(auth, ssid, pass);
// Establishes secure connection to WiFi and Blynk cloud
