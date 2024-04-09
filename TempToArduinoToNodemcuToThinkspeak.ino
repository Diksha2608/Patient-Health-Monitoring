void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = voltage * 100; 
  Serial.println(temperature);

  // Send the temperature data to NodeMCU over serial
  Serial.println(temperature);
  delay(500);
}
