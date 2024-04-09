#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Galaxy M02s4322";
const char* password = "diksha@2002";
const char* apiKey = "LBOYL4EWSOLTFK9A";
const char* server = "api.thingspeak.com";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(100);

  WiFi.begin(ssid, password);
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  ThingSpeak.begin(client);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    float temperature = data.toFloat();

    Serial.print("Temperature: ");
    Serial.println(temperature);

    ThingSpeak.setField(1, temperature);
    int status = ThingSpeak.writeFields(2501539, apiKey);
    if (status == 200) {
      Serial.println("Data sent successfully");
    } else {
      Serial.println("Problem sending data to ThingSpeak");
    }
  }

  delay(15000);
}
