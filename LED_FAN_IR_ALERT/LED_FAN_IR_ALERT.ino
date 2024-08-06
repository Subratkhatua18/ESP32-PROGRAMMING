#define BLYNK_TEMPLATE_ID "TMPL3nLNbfK8_"
#define BLYNK_TEMPLATE_NAME "Home Automation2"
#define BLYNK_AUTH_TOKEN "RrVKLmPnk8WkVa9gyiicYnkNGsOJx0Cb"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "realme Narzo 10";  
char pass[] = "tapas234";  

BlynkTimer timer;

#define relay3_pin 19
#define relay2_pin 23

int relay3_state = 0;
int relay2_state = 0;

#define button3_vpin V3
#define button2_vpin V2

#define DHTPIN 4
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

BLYNK_CONNECTED() {
  Blynk.syncVirtual(button3_vpin);
  Blynk.syncVirtual(button2_vpin);
}

BLYNK_WRITE(button3_vpin) {
  relay3_state = param.asInt();
  digitalWrite(relay3_pin, relay3_state);
}

BLYNK_WRITE(button2_vpin) {
  relay2_state = param.asInt();
  digitalWrite(relay2_pin, relay2_state);
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("    Humidity : ");
    Serial.println(h);

     if(t >= 27){
    Blynk.logEvent("Alert!!","Temperature above 29 degree");
  }
}
void setup()
{   
  Serial.begin(115200);
  pinMode(relay3_pin, OUTPUT);
  pinMode(relay2_pin, OUTPUT);

  pinMode(18,OUTPUT);
  digitalWrite(18,HIGH);
   pinMode(21,OUTPUT);
  digitalWrite(21,HIGH);

  digitalWrite(relay3_pin, HIGH);
  digi talWrite(relay2_pin, HIGH);

  Blynk.begin(auth, ssid, pass);

  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(2500L, sendSensor);
}
void loop()
{
  Blynk.run();
  timer.run();
  delay(1000);
 }