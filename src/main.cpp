#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

const int pin14 = 14;
const int led = 2;
int det = 0; //si detecta envia un uno

typedef struct struct_message{
  char a[32];
  int b;
} struct_message;

struct_message myData;

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len){
  memcpy(&myData, incomingData, sizeof(myData));
}

void setup(){
  Serial.begin(9200);

  pinMode(led, OUTPUT);
  pinMode(pin14, OUTPUT);
  digitalWrite(led,LOW);
  digitalWrite(pin14,LOW);

  WiFi.mode(WIFI_STA);
  if(esp_now_init() != ESP_OK){
    Serial.println("Error iniciando ESP_NOW");
    return;
  }
}

void loop(){
  
  esp_now_register_recv_cb(OnDataRecv);
  det = myData.b;
  if (det == 0){
    digitalWrite(pin14, LOW);
    digitalWrite(led, LOW);
  
  }else if (det == 1){
    digitalWrite(pin14, HIGH);
    digitalWrite(led, HIGH);
   delay(900000);
  }
  delay(2000);
}
