int numbGuess = 0;
int neededGuesses = 4; //Start runde med 4 gæt

int LEDPins[4] = {13,12,7,4};
int ButtonPins[4] = {A0,A1,A2,A3};
int tones[4] = {262,294,330,349};
int guesses[neededGuesses];
int randomLEDCombination[neededGuesses];
int selectedRandNums[neededGuesses];
bool correctComb = false;

void setup() {

  Serial.begin(9600);
  
  //Sørger for at random starter på et tilfældig sted efter reset
  randomSeed(analogRead(0));

  //Sætter de analog pins til knapperne til PULLUP så de konstant giver 1 og 0 når der trykkes
  for(int i = 0; i < 4; i++) {
    pinMode(ButtonPins[i], INPUT_PULLUP);
  }

  //Genere den første sekvens til LED´erne
  generateRandomSequence();

  //initiering af første runde
  for(int i = 0; i < neededGuesses; i++){
    int LEDnum = randomLEDCombination[i];
    int ToneNum = selectedRandNums[i];
    /*
    Serial.print("LED pin: ");
    Serial.println(LEDnum);
    Serial.print("Tone: ");
    Serial.println(tones[ToneNum]);
    */
    digitalWrite(LEDnum, HIGH);
    //tone(8, tones[ToneNum]);
    delay(1000);
    digitalWrite(LEDnum, LOW);
    //noTone(8);
    
  }
}

void loop() {
  int buttonValue;

  while(neededGuesses != 0) {
    int GreenBtn = analogRead(A0);
    int YellowBtn = analogRead(A1);
    int RedBtn = analogRead(A2);
    int BlueBtn = analogRead(A3);

    if(GreenBtn > 1000) {
      guessBtn(0); //Grøn LED
      neededGuesses--;

    } else if(YellowBtn > 1000) {
      guessBtn(1);; //Gul LED
      neededGuesses--;

    } else if(RedBtn > 1000) {
      guessBtn(2); //Rød LED
      neededGuesses--;

    } else if(BlueBtn > 1000) {
      guessBtn(3); //Blå LED
      neededGuesses--;

    }
  }

  printArray(guesses, neededGuesses);

  checkCorrectCombination();
  
  if(correctComb == true) {
    Serial.println("You won!!");
    //victoryFlash();
  }

} //LOOP BLOCK END


void guessBtn(int LED) {
  printArray(guesses, neededGuesses);
  guesses[numbGuess] = LEDPins[LED];

  Serial.print("Selected LED: ");
  Serial.println(LEDPins[LED]);

  Serial.print("Guess: ");
  Serial.println(guesses[numbGuess]);

  digitalWrite(LEDPins[LED], HIGH);
  //tone(8, tones[LED]);
  delay(1000);
  digitalWrite(LEDPins[LED], LOW);
  //noTone(8);
  numbGuess++;
} //guessBtn END


void checkCorrectCombination() {
  int correctGuesses = 0;
  
  for(int i = 0; i < neededGuesses; i++) {
    Serial.print("Gæt: ");
    Serial.println(guesses[i]);
    Serial.println();
    if(guesses[i] == randomLEDCombination[i]) {
      correctGuesses++;
      Serial.print("Correct guess!: ");
      Serial.println(guesses[i]);
      Serial.print("Correct LED: ");
      Serial.println(randomLEDCombination[i]);
    } else {
      Serial.print("Wrong guess!: ");
      Serial.println(guesses[i]);
      Serial.print("Correct LED: ");
      Serial.println(randomLEDCombination[i]);
    }
  }

  if(correctGuesses == neededGuesses) {
    correctComb = true;
  }
} // checkCorrectCombination END


void generateRandomSequence () {
  int randomNum;

  //Giver 4 tilfældige pins som der skal displayes og gemmes til verifikation
  for(int i = 0; i < neededGuesses; i++) {
    randomNum = random(0,neededGuesses);

    Serial.print("Number chosen: ");
    Serial.println(randomNum);

    selectedRandNums[i] = randomNum; //Til brug af toner
    randomLEDCombination[i] = LEDPins[randomNum];
    
  }
} // generateRandomSequence END

void printArray(int arr[], int size) {
  Serial.print("[");
  for (int i = 0; i < size; i++) {
    Serial.print(arr[i]);
    if (i < size - 1) {
      Serial.print(", ");  // Komma mellem elementer
    }
  }
  Serial.println("]");
} // printArray END
