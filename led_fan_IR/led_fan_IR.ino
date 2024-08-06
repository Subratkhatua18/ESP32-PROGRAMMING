#define BLYNK_TEMPLATE_ID "TMPL3nLNbfK8_"
#define BLYNK_TEMPLATE_NAME "Home Automation2"
#define BLYNK_AUTH_TOKEN "RrVKLmPnk8WkVa9gyiicYnkNGsOJx0Cb"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "TITU 9 PRO";  
char pass[] = "TITU REALME";  

BlynkTimer timer;

#define PIR_SENSOR  15
#define relay3_pin 19
#define relay2_pin 23

int relay3_state = 0;
int relay2_state = 0;

#define button3_vpin V3
#define button2_vpin V2

#define DHTPIN 4
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

void notifyOnTheft()
{
  int isTheftAlert = digitalRead(PIR_SENSOR);
  Serial.println(isTheftAlert);
  if (isTheftAlert==0) {
    Serial.println("Theft Alert in Home");
    Blynk.logEvent("theft_alert","Theft Alert in Home");
//    flag=1;
  }
  else if (isTheftAlert==1)
  {
   // flag=0;
  }
}

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

     if(t > 26){
   // Blynk.email("subratkhatua462@gmail.com", "Alert", "Temperature over 26C!");
    Blynk.logEvent("temp_alert","Temp above 30 degree");
  }
}
void setup()
{   
  Serial.begin(115200);
  pinMode(relay3_pin, OUTPUT);
  pinMode(relay2_pin, OUTPUT);

  pinMode(PIR_SENSOR, INPUT);

  pinMode(18,OUTPUT);
  digitalWrite(18,HIGH);

  digitalWrite(relay3_pin, HIGH);
  digitalWrite(relay2_pin, HIGH);

  Blynk.begin(auth, ssid, pass);

  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(2500L, sendSensor);
  timer.setInterval(5000L, notifyOnTheft);
}
void loop()
{
  Blynk.run();
  timer.run();
  delay(1000);
 }