// Az MQ-5 gázérzékelő szenzor tesztelésére létrehozott kódsor

#define SENSOR 34  // a P34-es egy analóg bemeneti pin az ESP-n

int sensorData = 0;  // ebben a változóban a szenzortól kapott aktuális értéket tárolom

void setup() {
  Serial.begin(115200);
  Serial.println("Sensor start");
}

void loop() {
  delay(500);

  sensorData = analogRead(SENSOR);
  Serial.print("Value: ");
  Serial.println(sensorData);
  
  delay(500);
}
