int data =0;
int relay_pin = 0;
int relay_pin = 2;

void setup(){
  pinMode(relay_pin, OUTPUT);
  Serial.begin(115200);
}

void loop(){
  if(Serial.available()){
    String cmd = Serial.readString();d:\ESP32\RGB\RGB.ino
    if(cmd == "ON"){
        digitalWrite(realy_pin, HIGH);
    }
    else if(cmd == "OFF"){
      digitalWrite(realy_pin, LOW);
    }
  }
}