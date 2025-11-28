const int MAX_ROUNDS = 5;
const int MAX_GUESSES = 10;

int gameRound = 1;
int neededGuesses = 4;  //Start runde med 4 gæt
int numGuess = 0;
bool correctComb = false;
int PZpin = 8; 

int LEDPins[4] = { 13, 12, 7, 4 };
int ButtonPins[4] = { A0, A1, A2, A3 };
int tones[4] = { 262, 294, 330, 349 };

int guesses[MAX_GUESSES];
int randomLEDCombination[MAX_GUESSES];
int selectedRandNums[MAX_GUESSES];

void setup() {

  Serial.begin(9600);

  //Sætter de analog pins til knapperne til PULLUP så de konstant giver 1 og 0 når der trykkes
  for (int i = 0; i < 4; i++) {
    pinMode(ButtonPins[i], INPUT_PULLUP);
  }

  //Sætter digitalpins som tænder LED'erne til OUTPUT da den pr. default opfatter dem som input og kan give nogle uhensigtsmæssigheder
  for (int i = 0; i < 4; i++) {
    pinMode(LEDPins[i], OUTPUT);
  }
}

void loop() {

  if (gameRound < MAX_ROUNDS) {
    createRound();  //Viser LED'er og spiller tonen så runden er sat

    while (numGuess != neededGuesses) {
      int GreenBtn = analogRead(A0);
      int YellowBtn = analogRead(A1);
      int RedBtn = analogRead(A2);
      int BlueBtn = analogRead(A3);

      if (GreenBtn > 1000) {
        guessBtn(0);  //Grøn LED
        numGuess++;

      } else if (YellowBtn > 1000) {
        guessBtn(1);  //Gul LED
        numGuess++;

      } else if (RedBtn > 1000) {
        guessBtn(2);  //Rød LED
        numGuess++;

      } else if (BlueBtn > 1000) {
        guessBtn(3);  //Blå LED
        numGuess++;
      }
    }

    checkCorrectCombination();

    if (correctComb == true) {
      Serial.println("You won!!");
      nextRound(); //Resetter arrays mm.
      //victoryFlash();
    }
  } else {
    Serial.println("GAME OVER");
    resetGuesses();
    numGuess = 0;
    Serial.println("Resetting round");
  }

}  //LOOP BLOCK END

void createRound() {
  //Genere tilfældig sammensætning af LED'er baseret på hvor mange gæt der skal til i runden (MAX_GUESSES)
  generateRandomSequence();

  //Her spilles toner og vises LED'er i den valgte rækkefølge for brugeren
  for (int i = 0; i < neededGuesses; i++) {
    int LEDnum = randomLEDCombination[i];
    int ToneNum = selectedRandNums[i];
    digitalWrite(LEDnum, HIGH);
    //tone(PZPin, tones[ToneNum]);
    delay(1000);
    digitalWrite(LEDnum, LOW);
    //noTone(PZPin);
  }
}
/*Nulstiller gæt og tilføjer et ekstra gæt til den kommende runde*/
void nextRound() {
  correctComb = false;
  gameRound++;
  neededGuesses++; //Antallet af gæt krævet stiger hver runde klaret
  numGuess = 0;
  resetGuesses(); //Resetter guesses arrayet så alle pladser er 0 igen
  Serial.print("Runde: ");
  Serial.println(gameRound);

  Serial.print("Guesses required: ");
  Serial.println(neededGuesses);
} //nextRound END

void resetGuesses() {
    for (int i = 0; i < MAX_GUESSES; i++) {
        guesses[i] = 0;
    }
} // resetGuesses END

void guessBtn(int LED) {
  printArray(guesses, MAX_GUESSES);
  guesses[numGuess] = LEDPins[LED];

  Serial.print("LED: ");
  Serial.println(LEDPins[LED]);

  Serial.print("Guess: ");
  Serial.println(guesses[numGuess]);

  digitalWrite(LEDPins[LED], HIGH);
  //tone(PZpin, tones[LED]);
  delay(1000);
  digitalWrite(LEDPins[LED], LOW);
  //noTone(PZpin);
}  //guessBtn END


void checkCorrectCombination() {
  int correctGuesses = 0;

  for (int i = 0; i < neededGuesses; i++) {
    Serial.print("Gæt: ");
    Serial.println(guesses[i]);
    Serial.println();
    if (guesses[i] == randomLEDCombination[i]) {
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

  if (correctGuesses == neededGuesses) {
    correctComb = true;
  }
}  // checkCorrectCombination END


void generateRandomSequence() {
  //Sørger for at random starter på et tilfældig sted efter reset
  randomSeed(analogRead(0));

  int randomNum;

  //Giver 4 tilfældige pins som der skal displayes og gemmes til verifikation
  for (int i = 0; i < neededGuesses; i++) {
    randomNum = random(0, 4);

    selectedRandNums[i] = randomNum;  //Til brug af toner
    randomLEDCombination[i] = LEDPins[randomNum]; //Henter LEDpin nummeret på gættets plads
  }

  Serial.println("Combination chosen: ");
  printArray(selectedRandNums, neededGuesses);
}  // generateRandomSequence END



//BRUGES KUN TIL DEBUGGING
void printArray(int arr[], int size) {
  Serial.print("[");
  for (int i = 0; i < size; i++) {
    Serial.print(arr[i]);
    if (i < size - 1) {
      Serial.print(", ");  // Komma mellem elementer
    }
  }
  Serial.println("]");
}  // printArray END
