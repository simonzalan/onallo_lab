#include <WiFi.h>

#define SENSOR 34

int sensorValue = 0;

// a vezeték nélküli hálózat adatai, amire kapcsolódni szeretnénk
const char* ssid = "";  // a hálózat azonosítója
const char* password =  "";  // a hálózat jelszava

// az adatfelodolgozó központot futtató eszköz ugyanezen hálózathoz csatlakozik
const uint16_t port = 8090;
const char * host = "";  // a kozpont.py fájlt futtató eszköz IPv4 címe
 
void setup()
{
  Serial.println("Sensor start");
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}
 
void loop()
{
  delay(2500);
  sensorValue = analogRead(SENSOR);  // kilvasom a szenzor által mért értékét
  Serial.print("Value: "); 
  Serial.println(sensorValue);
  
  Serial.println("Connecting...");
  WiFiClient client;
  
    if (!client.connect(host, port)) {
        Serial.println("Connection failed");
        delay(1000);
        return;
    }
    
    Serial.println("Connected established");
    client.print(sensorValue);  // elküldöm az adatot a socket-en keresztül
    Serial.println("Disconnecting...");
    client.stop();
    delay(2500);  // a loop elején és végén is 2.5 mp késleltetést iktatok be, így küldöm az adatokat 5 mp-enként
}
