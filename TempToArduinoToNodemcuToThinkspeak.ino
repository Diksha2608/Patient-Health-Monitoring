// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = voltage * 100; // This conversion might not be accurate, depending on your sensor.

  // print out the value you read:
  Serial.println(temperature);

  // Send the temperature data to NodeMCU over serial
  Serial.println(temperature);

  delay(500);
}
