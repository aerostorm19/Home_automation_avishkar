#include <dummy.h>


 /**********************************************************************************/
#define BLYNK_PRINT Serial

// Template ID, Device Name and Auth Token
#define BLYNK_TEMPLATE_ID "TMPL3Y7reHYvw"
#define BLYNK_TEMPLATE_NAME "Home automation avishkar"
#define BLYNK_AUTH_TOKEN "pCHzmcU2znubPeOI0GoFzw-jfE9ai2UP"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
// #include <RBDdimmer.h>

char auth[] = BLYNK_AUTH_TOKEN;

// WiFi credentials.

//char ssid[] = "moto g32_3862";
//char pass[] = "123brrrr";

char ssid[] = "Redmi Note 10 Pro";
char pass[] = "1234567ate910";
BlynkTimer timer;

// declaring pins to control the relays manually
#define button1_pin 7
#define button2_pin 8
#define button3_pin 9
#define button4_pin 10

// declaring pins to control the relay state
#define relay1_pin 1
#define relay2_pin 2
#define relay3_pin 3
#define relay4_pin 4

// Intensity control appliances
#define fan_dim_pin 11
#define zvc 13
#define led_dim_pin 12


int relay1_state = 0;
int relay2_state = 0;
int relay3_state = 0;
int relay4_state = 0;

int Slider_Value;
int dimming;
int x = 0;

//Change the virtual pins according the rooms
#define button1_vpin    V1
#define button2_vpin    V2
#define button3_vpin    V3 
#define button4_vpin    V4
#define fan_dim_vpin    V11
#define led_dim_vpin    V12


//------------------------------------------------------------------------------
// This function is called every time the device is connected to the Blynk.Cloud
// Request the latest state from the server
BLYNK_CONNECTED() {
  Blynk.syncVirtual(button1_vpin);
  Blynk.syncVirtual(button2_vpin);
  Blynk.syncVirtual(button3_vpin);
  Blynk.syncVirtual(button4_vpin);
  Blynk.syncVirtual(fan_dim_vpin);


}

//--------------------------------------------------------------------------
// This function is called every time the Virtual Pin state change
//i.e when web push switch from Blynk App or Web Dashboard
BLYNK_WRITE(button1_vpin) {
  relay1_state = param.asInt();
  digitalWrite(relay1_pin, relay1_state);
}
//--------------------------------------------------------------------------
BLYNK_WRITE(button2_vpin) {
  relay2_state = param.asInt();
  digitalWrite(relay2_pin, relay2_state);
}
//--------------------------------------------------------------------------
BLYNK_WRITE(button3_vpin) {
  relay3_state = param.asInt();
  digitalWrite(relay3_pin, relay3_state);
}
//--------------------------------------------------------------------------
BLYNK_WRITE(button4_vpin) {
  relay4_state = param.asInt();
  digitalWrite(relay4_pin, relay4_state);
}


BLYNK_WRITE(V11)
{
  Slider_Value = param.asInt(); // assign incoming value from pin V1 to a variable
}
//--------------------------------------------------------------------------


void setup()
{

  // Intensity control setup
    pinMode(zvc, INPUT_PULLUP);
  pinMode(fan_dim_pin, OUTPUT);
  Serial.begin(11520);
  //--------------------------------------------------------------------
  pinMode(button1_pin, INPUT_PULLUP);
  pinMode(button2_pin, INPUT_PULLUP);
  pinMode(button3_pin, INPUT_PULLUP);
  pinMode(button4_pin, INPUT_PULLUP);
  //--------------------------------------------------------------------
  pinMode(relay1_pin, OUTPUT);
  pinMode(relay2_pin, OUTPUT);
  pinMode(relay3_pin, OUTPUT);
  pinMode(relay4_pin, OUTPUT);
  //--------------------------------------------------------------------
  //During Starting all Relays should TURN OFF
  digitalWrite(relay1_pin, LOW);
  digitalWrite(relay2_pin, LOW);
  digitalWrite(relay3_pin, LOW);
  digitalWrite(relay4_pin, LOW);
  //--------------------------------------------------------------------
  Blynk.begin(auth, ssid, pass);

  attachInterrupt(digitalPinToInterrupt(zvc), acon, FALLING);
}

void loop()
{
  Blynk.run();
  timer.run();
  dimming = map(Slider_Value,0,100,7200,0);


  listen_push_buttons();
}



void acon()
{
  delayMicroseconds(dimming);
  digitalWrite(fan_dim_pin, HIGH);

  delayMicroseconds(50);
  digitalWrite(fan_dim_pin, LOW);
}
void listen_push_buttons(){
    //--------------------------------------------------------------------------
    if(digitalRead(button1_pin) == LOW){
      delay(200);
      control_relay(1);
      Blynk.virtualWrite(button1_vpin, relay1_state); //update button state
    }
    //--------------------------------------------------------------------------
    if (digitalRead(button2_pin) == LOW){
      delay(200);
      control_relay(2);
      Blynk.virtualWrite(button2_vpin, relay2_state); //update button state
    }
    //--------------------------------------------------------------------------
    if (digitalRead(button3_pin) == LOW){
      delay(200);
      control_relay(3);
      Blynk.virtualWrite(button3_vpin, relay3_state); //update button state
    }
    //--------------------------------------------------------------------------
    if (digitalRead(button4_pin) == LOW){
      delay(200);
      control_relay(4);
      Blynk.virtualWrite(button4_vpin, relay4_state); //update button state
    }
    //--------------------------------------------------------------------------
}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

void control_relay(int relay){
  //------------------------------------------------
  if(relay == 1){
    relay1_state = !relay1_state;
    digitalWrite(relay1_pin, relay1_state);
    Serial.print("Relay1 State = ");
    Serial.println(relay1_state);
    delay(50);
  }
  //------------------------------------------------
  else if(relay == 2){
    relay2_state = !relay2_state;
    digitalWrite(relay2_pin, relay2_state);
    Serial.print("Relay2 State = ");
    Serial.println(relay2_state);
    delay(50);
  }
  //------------------------------------------------
  else if(relay == 3){
    relay3_state = !relay3_state;
    digitalWrite(relay3_pin, relay3_state);
    Serial.print("Relay3 State = ");
    Serial.println(relay3_state);
    delay(50);
  }
  //------------------------------------------------
  else if (relay == 4){
    relay4_state = !relay4_state;
    digitalWrite(relay4_pin, relay4_state);
    Serial.print("Relay4 State = ");
    Serial.println(relay4_state);
    delay(50);
  }

}
