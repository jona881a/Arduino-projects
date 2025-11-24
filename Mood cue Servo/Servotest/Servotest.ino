#include <Servo.h>

//global variables
Servo myServo;

int const potentioPin = A0;
int potentioVal;
int angle;

void setup() {
  myServo.attach(9); //servo objektet tilknytter sig port digital port 9

  Serial.begin(9600);
}

void loop() {
  potentioVal = analogRead(potentioPin);

  Serial.print("potentioVal: ");
  Serial.print(potentioVal);

  //Funktionen tager og skalere 0-1023 (analog input) værdier til 0-179 (graderne i en servo)
  //De fem argumenter: 
  //1: Tallet til at skalere
  //2: minimumsvædien for inputtet
  //3: maksimumsværdien for inputtet
  //4: minimumsvædien for outputtet
  //5: maksimumsværdien for outputtet
  angle = map(potentioVal, 0, 1023, 0 , 179); 
  Serial.print(" , angle: ");
  Serial.println(angle);

  myServo.write(angle); //Fortæller hvlke grad servoen skal dreje til
  delay(1000); //Delayer koden så servoen har tid til at dreje
}
