
#  Home Automation System – Avishkar

This project enables smart control of home appliances using the **Blynk app**, **physical push buttons**, and **voice commands** (via Dialogflow). It uses an **ESP32** to interface with relays and a dimmer circuit for fan speed control.

---

##  Hardware Components

| Component      | GPIO Pin | Function                   |
|----------------|----------|----------------------------|
| Relay 1        | GPIO1    | Appliance control          |
| Relay 2        | GPIO2    | Appliance control          |
| Relay 3        | GPIO3    | Appliance control          |
| Relay 4        | GPIO4    | Appliance control          |
| Button 1       | GPIO7    | Manual toggle              |
| Button 2       | GPIO8    | Manual toggle              |
| Button 3       | GPIO9    | Manual toggle              |
| Button 4       | GPIO10   | Manual toggle              |
| Fan Dimmer     | GPIO11   | AC fan speed control       |
| Zero-Cross Det.| GPIO13   | AC waveform detection      |
| LED Dimmer     | GPIO12   | Reserved for future use    |

---

##  Blynk Virtual Pins Mapping

| Virtual Pin | Component   | Control Type |
|-------------|-------------|--------------|
| V1          | Relay 1     | Switch       |
| V2          | Relay 2     | Switch       |
| V3          | Relay 3     | Switch       |
| V4          | Relay 4     | Switch       |
| V11         | Fan Dimmer  | Slider       |
| V12         | LED Dimmer  | Slider       |

---

##  Key Features

### ✅ Multi-Control Interface:
- Blynk app (mobile & web dashboard)
- Physical push buttons
- Voice command via Dialogflow

### 🔄 Real-time Synchronization:
- Syncs relay/fan states on reconnect
- Updates to Blynk cloud immediately

### ⚡ Safe AC Dimming:
- Zero-cross detection
- Phase-angle dimming for fan

### 🗣️ Voice Control Integration:
- Dialogflow NLP processing
- Webhook requests to Blynk API

---

## Code Explanation

### 1. Configuration Section

```cpp
#define BLYNK_TEMPLATE_ID "TMPL3Y7reHYvw"
#define BLYNK_TEMPLATE_NAME "Home automation avishkar"
#define BLYNK_AUTH_TOKEN "pCHzmcU2znubPeOI0GoFzw-jfE9ai2UP"
```

*Blynk credentials for cloud communication.*

---

### 2. WiFi & Blynk Initialization

```cpp
char ssid[] = "Redmi Note 10 Pro";
char pass[] = "1234567ate910";
Blynk.begin(auth, ssid, pass);
```

*Establishes secure connection to WiFi and Blynk cloud.*

---

### 3. State Synchronization

```cpp
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V1, V2, V3, V4, V11);
}
```

*Synchronizes all device states with Blynk server.*

---

### 4. Relay Control Handlers

```cpp
BLYNK_WRITE(V1) {
  relay1_state = param.asInt();
  digitalWrite(relay1_pin, relay1_state);
}
```

*Updates relay state on virtual switch toggle.*

---

### 5. Fan Dimming Logic

```cpp
void acon() {
  delayMicroseconds(dimming);
  digitalWrite(fan_dim_pin, HIGH);
  delayMicroseconds(50);
  digitalWrite(fan_dim_pin, LOW);
}
```

- *Interrupt triggered on zero-cross detection*
- *`dimming` value mapped from slider (0–100% → 7200–0 μs)*

---

### 6. Physical Button Listening

```cpp
void listen_push_buttons(){
  if(digitalRead(button1_pin) == LOW){
    control_relay(1);
    Blynk.virtualWrite(V1, relay1_state);
  }
}
```

- *Debounced input for local toggle*
- *Updates Blynk to stay in sync*

---

### 7. Voice Control Integration (Conceptual)

```python
# Sample Python Voice Command Handler
import requests

def handle_voice_command(command):
    blynk_url = f"http://blynk-cloud.com/{AUTH_TOKEN}/update/"
    
    if "turn on light" in command:
        requests.get(blynk_url + "V1?value=1")
    elif "fan speed 50" in command:
        requests.get(blynk_url + "V11?value=50")
```

---

## 🎙️ Voice Control Setup

- Create **Dialogflow agent**
- Enable **webhook integration**
- Map intents to Blynk HTTP API:
  - `turn on [device]`
  - `set [device] to [value]%`
  - `toggle [room] light`

---


## 🛠️ Requirements

- ESP32 board
- Blynk App account
- Dialogflow Agent (optional for voice control)
- Relays + AC fan dimmer hardware

---

## 🚀 Getting Started

1. Flash code to ESP32
2. Set up Blynk template with correct Vpins
3. Connect hardware (relays, fan dimmer)
4. Power on and control via:
   - Blynk App
   - Push buttons
   - Voice via Dialogflow

---

## 📢 Disclaimer

> 💡 Always take **proper safety precautions** when working with **AC voltage**. Use opto-isolated relays and AC dimmer modules rated for your appliances.

---

## 👨‍💻 Author

**Abhijit Rai**  
For project documentation, contributions, or issues, feel free to reach out or open a PR/issue on GitHub.
