#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// a vezeték nélküli hálózat adatai, amihez kapcsolódni szeretnénk
const char* ssid = "";  // a hálózat azonosítója
const char* password = "";  // a hálózat jelszava

// a blokkláncot futtató gép IP címe
const char* url = "";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected");
}

void loop() {
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      http.begin(client, url);
      Serial.print("url: ");
      Serial.println(url);
      Serial.println("Formatting JSON...");
      String js= "";

      // a küldeni kívánt adatokat először JSON formátumúra alakítjuk
      StaticJsonDocument<384> doc;
      
      doc["jsonrpc"] = "2.0";
      doc["method"] = "eth_call";
      
      JsonArray params = doc.createNestedArray("params");
      
      JsonObject params_0 = params.createNestedObject(); 
      params_0["from"] = "";  // az account, amiről a függvényt meghívjuk
      params_0["to"] = "";  // a szerződés címe
      params_0["data"] = "";  // a meghívni kívánt függvény Keccak-256 hash-ének első 8 karaktere + az átadni kívánt paraméter 0-kal 64 karakterre kiegészített hexadecimális alakja
      params.add("latest");
      doc['id'] = 420;
      
      serializeJson(doc, js);

      Serial.println("Posting...");
      http.addHeader("Content-Type", "application/json");
      Serial.println("Output:");
      Serial.println(js);
      
      int httpResponseCode = http.POST(js);  // POST kérés küldése a szerződésnek

      if(httpResponseCode){
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        Serial.println(http.getString());
        Serial.println("Response is above");
      http.end();
      }
      else {
      Serial.println("Cannot connect");
      }
      delay(60000);
  }
}
