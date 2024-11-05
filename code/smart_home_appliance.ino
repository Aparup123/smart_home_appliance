#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL321z1uwQW"
#define BLYNK_TEMPLATE_NAME "smart home appliance"
#define BLYNK_AUTH_TOKEN "G7AS2yJdX9vvFiEdj-4zrEmk66PhFD8c"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "wifi_ssid";
char pass[] = "wifi_password";

#define LED1 16 //D0
#define LED2 5 //D1
#define BOARD_LED LED_BUILTIN //D2
#define BUZZER 0 //D3
#define DPIN 4 //D4
#define DTYPE DHT11

//dht object init
DHT dht(DPIN, DTYPE);

void wifiSignal(){
  digitalWrite(BOARD_LED, HIGH);
  delay(300);
  digitalWrite(BOARD_LED, LOW);
  delay(300);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BOARD_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  dht.begin();

  digitalWrite(BOARD_LED, LOW);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Blynk setup successful");

  // blink board led after wifi is connected
  wifiSignal();
  wifiSignal();
  wifiSignal();
  wifiSignal();
}

// getting data from Blynk virtual pins and writing to the devices 
BLYNK_WRITE(V0){
  int data=param.asInt();
  digitalWrite(LED1, data);
}

BLYNK_WRITE(V1){
  int data=param.asInt();
  digitalWrite(LED2, data);
}

BLYNK_WRITE(V2){
  int data=param.asInt();
  digitalWrite(BUZZER, data);
}

BLYNK_WRITE(V3){
  int data=param.asInt();
  digitalWrite(BOARD_LED, !(data));
}


// function to send the dht sensor data to Blynk 
void sendDhtData() {  
  // Read from dht sensor in celsius 
  float temp=dht.readTemperature(false);
  float hum=dht.readHumidity();
  Serial.print("temp: ");
  Serial.println(temp);
  Serial.print("Hum: ");
  Serial.println(hum);
  Blynk.virtualWrite(V4, temp); // Send temperature to virtual pin V4
  Blynk.virtualWrite(V5, hum); // Send humidity to virtual pin V5
  delay(500); 
}

void loop()
{
  Blynk.run();
  sendDhtData();
}
