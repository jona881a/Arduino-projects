int greenButton;
int yellowButton;
int redButton;
int blueButton;

int tones[4] = {262,294,330,349};
int colorCombination[4] = {0, 1, 2, 2};
int inputtedAnswers[4];

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  int colorPick;

  //Initiel farve kombo
  /*
  for(int i = 0; i <= 3; i++) {
      colorCombination[i] = random(5);
  }
  */
  //Viser farvekomtinationen som første runde
  for(int i = 0; i <= 3; i++) {
    /*
    Serial.print("Color: ");
    Serial.println(colorCombination[i]);
    Serial.print("Frequenzy: ");
    Serial.println(tones[i]);
    */
    colorPick = colorCombination[i];
    Serial.print("Color: ");
    Serial.println(colorPick);
    //Serial.print("Frequenzy: ");
    //Serial.println(tones[colorPick]);

    if(colorPick == 0){
      //tone(8, colorPick);
      Serial.println("Reading Green");
      digitalWrite(13, HIGH);
      delay(200);
      digitalWrite(13, LOW);
      //noTone(8);
    } else if(colorPick == 1){
      //tone(8, colorPick);
      Serial.println("Reading Yellow");
      digitalWrite(12, HIGH);
      delay(200);
      digitalWrite(12, LOW);
      //noTone(8);
    } else if(colorPick == 2){
      //tone(8, colorPick);
      Serial.println("Reading Red");
      digitalWrite(7, HIGH);
      delay(200);
      digitalWrite(7, LOW);
      //noTone(8);
    /*} else if(colorPick == 3){
      tone(8, colorPick);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      noTone(8);
    }*/
    } else {
      //noTone(8);
    }
  }
  //noTone(8);
}

void loop() {
  greenButton = analogRead(A0);
  yellowButton = analogRead(A1);
  redButton = analogRead(A2);
  blueButton = analogRead(A3);

  Serial.print("Green: ");
  Serial.println(greenButton);

  Serial.print("Yelow: ");
  Serial.println(yellowButton);
  
  if(greenButton > 400) {
      Serial.print("Green: ");
      Serial.println(greenButton);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      inputtedAnswers[0] = 0; 
      //tone(8, tones[0]);

  } else if (yellowButton > 400) {
      Serial.print("Yelow: ");
      Serial.println(yellowButton);
      digitalWrite(12, HIGH);
      delay(500);
      digitalWrite(12, LOW);
      inputtedAnswers[1] = 1; 
      //tone(8, tones[1]);

  } else if (redButton > 400) {
      Serial.print("Red: ");
      Serial.println(redButton);
      //tone(8, tones[2]);
      digitalWrite(7, HIGH);
      delay(500);
      digitalWrite(7, LOW);
      inputtedAnswers[2] = 2; 

  } else if (blueButton > 400) {
      Serial.print("Blue: ");
      Serial.println(blueButton);
      //tone(8, tones[3]);
      /*digitalWrite(, HIGH);
      delay(500);
      digitalWrite(, LOW);*/
      //inputtedAnswers[3] += 1; 
  } else {
    //noTone(8);
  }
}
