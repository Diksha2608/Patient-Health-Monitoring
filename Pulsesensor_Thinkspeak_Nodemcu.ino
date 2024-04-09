#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

const char* ssid = "Galaxy M02s4322";   // Network SSID
const char* password = "diksha@2002";   //  Network Password

WiFiClient client;

// ThingSpeak Configuration
unsigned long myChannelNumber = 2501041; // Channel Number (Without Brackets)
const char * myWriteAPIKey = "D5GDH438FDY0PRN7"; // Write API Key

const int PulseSensorHRWire = A0;
const int LED_D1 = D1;
int Threshold = 600;

unsigned long previousMillisGetHR = 0;
unsigned long previousMillisHR = 0;
const long intervalGetHR = 10;
const long intervalHR = 10000;
int cntHB = 0;
boolean ThresholdStat = true;
int BPMval = 0;

void handleHeartRate() {
  digitalWrite(LED_D1, LOW);
  String BPMvalSend = String(constrain(BPMval, 50, 120)); 
  Serial.print("BPM : ");
  Serial.println(BPMval);
  digitalWrite(LED_D1, HIGH);
  ThingSpeak.writeField(myChannelNumber, 1, BPMval, myWriteAPIKey); // Update BPM value in ThingSpeak
}

void GetHeartRate() {
  unsigned long currentMillisGetHR = millis();

  if (currentMillisGetHR - previousMillisGetHR >= intervalGetHR) {
    previousMillisGetHR = currentMillisGetHR;

    int PulseSensorHRVal = analogRead(PulseSensorHRWire);

    if (PulseSensorHRVal > Threshold && ThresholdStat == true) {
      cntHB++;
      ThresholdStat = false;
      digitalWrite(LED_D1, HIGH);
    }

    if (PulseSensorHRVal < Threshold) {
      ThresholdStat = true;
      digitalWrite(LED_D1, LOW);
    }
  }

  unsigned long currentMillisHR = millis();

  if (currentMillisHR - previousMillisHR >= intervalHR) {
    previousMillisHR = currentMillisHR;

    BPMval = constrain(cntHB * 6, 50, 120); 
    cntHB = 0;
    handleHeartRate(); // Call function to send BPM to ThingSpeak
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(LED_D1, OUTPUT);
  digitalWrite(LED_D1, HIGH); // Initially turn off LED
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client); // Initialize ThingSpeak
}

void loop() {
  GetHeartRate();
}
