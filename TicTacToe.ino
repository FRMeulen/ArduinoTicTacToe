//Fields
char gameState[9] = { '0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' };  //Fields to be taken
int gameWon = 0;  //0 means game is in progress, 1 means game is won, -1 means game ended as draw
int activePlayer = 1; //Tracks active player - always 1 or 2
int userInput = 9;  //Temporarily stores user input, default 9 is not a field

//Methods
void setup() {
  Serial.begin(9600);
}

void loop() {
  if(gameWon == 0){
    printBoard();
    askInput();
    delay(10);
    if(validateInput() == 1){
      commitMove();
      if(checkProgress() == 1){
        printBoard();
        Serial.print("Congratulations! Player ");
        Serial.print(activePlayer);
        Serial.println(" has won!");
        gameWon = 1;
      }
      else if(checkProgress() == -1){
        printBoard();
        Serial.println("Game ended as a draw! No winner!");
        gameWon = -1;
      }
      else{
        switchPlayer();
      }
    }
    delay(10);
    Serial.println(" ");
    delay(1000);
  }
}

//Prints the current state of the board to the serial monitor
void printBoard(){
  Serial.println("     |     |     ");
  Serial.print("  ");
  Serial.print(gameState[0]);
  Serial.print("  |  ");
  Serial.print(gameState[1]);
  Serial.print("  |  ");
  Serial.print(gameState[2]);
  Serial.println("  ");
  Serial.println("_____|_____|_____");
  Serial.println("     |     |     ");
  Serial.print("  ");
  Serial.print(gameState[3]);
  Serial.print("  |  ");
  Serial.print(gameState[4]);
  Serial.print("  |  ");
  Serial.print(gameState[5]);
  Serial.println("  ");
  Serial.println("_____|_____|_____");
  Serial.println("     |     |     ");
  Serial.print("  ");
  Serial.print(gameState[6]);
  Serial.print("  |  ");
  Serial.print(gameState[7]);
  Serial.print("  |  ");
  Serial.print(gameState[8]);
  Serial.println("  ");
  Serial.println("     |     |     ");
}

//Asks which field to take and returns its number
void askInput(){
  int tempInput;
  Serial.print("Player ");
  Serial.print(activePlayer);
  Serial.println(" which field will you take?");
  Serial.println("Enter the number...");

  while(Serial.available()==0){}
  tempInput = Serial.parseInt();

  //Restart serial to refresh stored char
  Serial.end();
  delay(100);
  Serial.begin(9600);

  userInput = tempInput;
}

//Validates user input
int validateInput(){
  if(userInput >= 0 && userInput <= 8){
    if(gameState[userInput] != 'X' && gameState[userInput] != 'O'){
      return 1; //Valid
    }
    else{
      Serial.println("Field already taken! Try again!");
    }
  }

  else{
    Serial.println("Field does not exist! Try again!");
  }
  return 0; //Invalid
}

//Checks if the game has ended
int checkProgress(){
  if(gameState[0] == gameState[1] && gameState[1] == gameState[2]){
    return 1;
  }
  else if(gameState[3] == gameState[4] && gameState[4] == gameState[5]){
    return 1;
  }
  else if(gameState[6] == gameState[7] && gameState[7] == gameState[8]){
    return 1;
  }
  else if(gameState[0] == gameState[3] && gameState[3] == gameState[6]){
    return 1;
  }
  else if(gameState[1] == gameState[4] && gameState[4] == gameState[7]){
    return 1;
  }
  else if(gameState[2] == gameState[5] && gameState[5] == gameState[8]){
    return 1;
  }
  else if(gameState[0] == gameState[4] && gameState[4] == gameState[8]){
    return 1;
  }
  else if(gameState[2] == gameState[4] && gameState[4] == gameState[6]){
    return 1;
  }

  else if(checkEmptyFields() == 0){
    Serial.println("Game ended as draw!");
    return -1;
  }

  else{
    return 0;
  }
}

//Commits player move
void commitMove(){
  if(activePlayer == 1){
    gameState[userInput] = 'X';
  }
  else if(activePlayer == 2){
    gameState[userInput] = 'O';
  }
  else{
    Serial.println("Player unknown!");
  }
}

//Switches active player
void switchPlayer(){
  if(activePlayer == 1){
    activePlayer++;
  }
  else if(activePlayer == 2){
    activePlayer--;
  }
  else{
    Serial.println("Player unknown!");
  }
}

//Checks for empty fields
int checkEmptyFields(){
  int emptyLeft = 0;
  for(int i=0;i<sizeof(gameState);i++){
    if(gameState[i] != 'X' && gameState[i] != 'O'){
      return 1;
    }
  }
  return 0;
}

