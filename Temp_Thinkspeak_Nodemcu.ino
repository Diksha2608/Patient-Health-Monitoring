#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;

const char* ssid = "Galaxy M02s4322";   // Network SSID
const char* password = "diksha@2002";       // Network Password

int val;
int pin = A0; // LM35 Pin Connected at A0 Pin

WiFiClient client;

unsigned long myChannelNumber = 2501136; //Channel Number 
const char * myWriteAPIKey = "ZKUR3L3LSYOKFC8L"; //Write API Key

void setup()
{
  Serial.begin(9600);
  delay(10);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
}

void loop()
{
  val = analogRead(pin)*0.322265; // Read Analog values and Store in val variable
  Serial.print("Temperature: ");
  Serial.print(val);                 // Print on Serial Monitor
  Serial.println("*C");
  delay(1000);
  ThingSpeak.writeField(myChannelNumber, 1,val, myWriteAPIKey); //Update in ThingSpeak
  delay(100);
}
