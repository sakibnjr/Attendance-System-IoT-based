#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Bhoot 👻"; // Replace with your Wi-Fi SSID
const char* password = "Triple2six4"; // Replace with your Wi-Fi password

const char* serverUrl = "http://192.168.0.109:3000/scan";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
}

void loop() {
  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("No networks found");
  } else {
    for (int i = 0; i < n; ++i) {
      String ssid = WiFi.SSID(i);
      String bssid = WiFi.BSSIDstr(i);
      Serial.print("Found network: ");
      Serial.print(ssid);
      Serial.print(" (MAC: ");
      Serial.print(bssid);
      Serial.println(")");
      sendMacAddress(bssid);
      delay(10);
    }
  }
  delay(10000); // Scan every 10 seconds
}

void sendMacAddress(String mac) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(client, serverUrl);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    String postData = "mac=" + mac;
    int httpResponseCode = http.POST(postData);
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
}