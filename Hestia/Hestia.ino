#define BLYNK_PRINT Serial

#include <OneWire.h> 
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define ONE_WIRE_BUS 2 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

char auth[] = "YourAuthToken";

char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

void sendSensor()
{
  sensors.requestTemperatures();
  float c = sensors.getTempCByIndex(0)
  float f = sensors.getTempFByIndex(0)
 
  Blynk.virtualWrite(V5, c);
  Blynk.virtualWrite(V6, f);
}

void ecg() {
  Blynk.virtualWrite(V0, digitalRead(10));
  Blynk.virtualWrite(V1, digitalRead(11));
  if((digitalRead(10)==1)||(digitalRead(11)==1)){
      Serial.println("Gagal");
      Blynk.virtualWrite(V2, 0);

  }
  else{
    Blynk.virtualWrite(V2, analogRead(A1));
      Serial.println(analogRead(A1));
  }


void setup()
{
  Serial.begin(9600);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  sensors.begin();
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);
  timer.setInterval(200L, ecg);

}

void loop()
{
  Blynk.run();
  timer.run();
}
