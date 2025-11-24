const int sensorPin = A0;
const float baselineTemp = 22.0;

void setup() {
  Serial.begin(9600); //Åbner en forbindelse til arduino med 9600 bit pr sekund

  for(int pinNumber = 2; pinNumber < 5; pinNumber++) { //Skifter mellem 2 - 4 i digital portene 
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  } 
}

void loop() {
  int sensorVal = analogRead(sensorPin);
  Serial.println("Sensor Value: ");  
  Serial.print(sensorVal);

  float voltage = (sensorVal/1024.0) * 5.0;
  Serial.println(", Volts: ");
  Serial.print(voltage);
  Serial.println(", degrees C: ");
  //Formlen for at converete de volt der kommer ind til temperatur
  float temperature = (voltage - .5) * 100;
  Serial.print(temperature);

  if(temperature < baselineTemp+2){
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if(temperature >= baselineTemp+2 && temperature < baselineTemp+4){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } else if(temperature >= baselineTemp+6){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  delay(1);
 }
