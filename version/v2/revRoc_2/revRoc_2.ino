#include <RGB.h>

#include <RevRoc.h>

/**
 * Malik Roc
 * CS298 Embedded Systems
 * Final Project - RevRoc Game
 * RevRoc Library - v2
 * RevRoc sketch
 */

 /*
  * Set up the pins to be used
  */

  // guess button
  #define button 2
  volatile int guess = -1;

  // lives pin
  #define lifeA 3
  #define lifeB 4
  #define lifeC 5

  // points pin
  #define pointA 6
  #define pointB 7
  #define pointC 8
  
  //grb array
  #define grbPin 9
  #define numOfPixels 16

  //grb display
  int bgColor[3]  = {  4, 25, 96};        // background Color
  int winColor[3] = {255,  0,  0};        // winning screen 
  int goColor[3]  = {  0,255,  0};        // game over screen
  int plColor[3]  = {   0,  0,255};        // player's led color
  int trgColor[3] = {255,255,  0};        // target color


RevRoc roc;
RGB grb (grbPin, numOfPixels);
 
void setup() {
  Serial.begin(9600);
  // Setup the pins
  pinMode (button, INPUT_PULLUP);
  
  pinMode (lifeA, OUTPUT);
  pinMode (lifeB, OUTPUT);
  pinMode (lifeC, OUTPUT);

  pinMode (pointA, OUTPUT);
  pinMode (pointB, OUTPUT);
  pinMode (pointC, OUTPUT);
  attachInterrupt(0, makeGuess_ISR, CHANGE);

  digitalWrite(lifeA, HIGH);
  digitalWrite(lifeB, HIGH);
  digitalWrite(lifeC, HIGH);

  beginGame();
  randomSeed[2];
  int pos = random(16); 
  roc.changePositionOfTarget(pos);
  
}

void loop() {

  /*
   * Get the direction of where the player wants to move
   */
   int xC = analogRead(A5);
   int yC = analogRead(A4);
   Serial.print("("); Serial.print(xC); Serial.print(","); Serial.print(yC); Serial.print(")");
   Serial.print("Target @ "); Serial.println(roc.getTargetsPosition()); 
   
   // move player up
   if(yC < 450)
   {
    changePlayerPosition(1);
   }
   //move player down
   else if (yC > 730)
   {
    changePlayerPosition(3);
   }
   // move player right
   else if (xC > 730)
  {
    changePlayerPosition(2);
  }
  // Move player left
  else if  (xC < 400)
  {
    changePlayerPosition(4);
  }

  /*
   * A guess has been made
   */
   if (guess != -1)
   {
      Serial.println("Making a guess");     
      // check to see if target is found
      roc.verifyGuess(guess);               // Check to see if the player made the correct guess
      updatePlayer();                       // update player's life and points
      guess = -1;                           // set the guess back to -1
      // move the target in a random position
      int num = random(16);
      roc.changePositionOfTarget(num);
   }
   delay(250);                              // Give the player some time
} // loop

void beginGame()
{
  roc.begin();                              // set up the game
  emptyBoard();                             // set all the leds to the background color
  int playerPos = roc.getPlayersPosition(); // get player's position
  int targetPos = roc.getTargetsPosition(); // get target's position

  // flashing player's location
  for (int i = 0; i < 10; i++)
  {
    grb.setColor(playerPos, plColor[0], plColor[1], plColor[2]); // set and show player's position
    grb.show();
    delay(100);
    grb.setColor(playerPos, bgColor[0], bgColor[1], bgColor[2]); // set and show 'that' pixel to the background 
    grb.show();
    delay(100);
  }
  //setting player's position
  grb.setColor(playerPos, plColor[0], plColor[1], plColor[2]); // show player's position
  grb.show();
  
  //updatePlayer();
}
void updatePlayer()
{
  int lives  = roc.getLives();
  int points = roc.getPoints();
  Serial.println("Updating the score board\n");
  Serial.print("Lives: "); Serial.print(lives); Serial.print(" Points: "); Serial.print(points); Serial.print(" Target @:");
  Serial.println(roc.getTargetsPosition());


  // setting the points
  switch (points)
  {
    case 1 :
      digitalWrite(pointA, HIGH);
      digitalWrite(pointB, LOW);
      digitalWrite(pointC, LOW);
      Serial.println("Setting one 'point' LEDs to high"); 
      break;
    case 2:
      digitalWrite(pointA, HIGH);
      digitalWrite(pointB, HIGH);
      digitalWrite(pointC, LOW);
      Serial.println("Setting two 'point' LEDs to high");
      break;
    case 3:
      digitalWrite(pointA, HIGH);
      digitalWrite(pointB, HIGH);
      digitalWrite(pointC, HIGH);
      Serial.print("Setting three 'point' LEDs to high! "); Serial.println("! Congratulations, you won!");
      signalGameWon();
      break;
    default:
      Serial.println("No points obtained");
  }

  // setting the lives
  switch (lives)
  {
    case 0 :
      digitalWrite(lifeA, LOW);
      digitalWrite(lifeB, LOW);
      digitalWrite(lifeC, LOW);
      Serial.println("Setting  'life' LEDs to LOW! Game Over!");
      signalGameOver();
      break;
    case 1:
      digitalWrite(lifeA, HIGH);
      digitalWrite(lifeB, LOW);
      digitalWrite(lifeC, LOW);
      Serial.print("Setting one 'life' LEDs to HIGH"); // Serial.print(lives); Serial.println(" left!");
      break;
    case 2:
      digitalWrite(lifeA, HIGH);
      digitalWrite(lifeB, HIGH);
      digitalWrite(lifeC, LOW);
      Serial.print("Setting two 'life' LEDs to HIGH "); // Serial.print(lives); Serial.println(" left!");
      break;
    default:
      Serial.print("No lives lost. All 'life' LEDs are HIGH ");
  }
  delay(500); // give player time to unpress the button
}

void changePlayerPosition(byte pos)
{
  int oldPos = roc.getPlayersPosition();
  grb.setColor(oldPos, bgColor[0], bgColor[1], bgColor[2]); // set to background color
  grb.show();
  roc.movePlayer(pos);
  int newPos = roc.getPlayersPosition(); // get the player's new position
  // show it on the grb display
  grb.setColor(newPos, plColor[0], plColor[1], plColor[2]);
  grb.show();
  Serial.print("Moving player! Player is at position: "); Serial.println(roc.getPlayersPosition());
  //delay(100);

}

// set all pixels to be the background color
void emptyBoard()
{
  //set the board to the background color
  for (int i = 0; i < 16; i++)
  {
    grb.setColor(i, bgColor[0], bgColor[1], bgColor[2]); 
    grb.show();
    Serial.print("Setting pixel: "); Serial.println(i);
  }
}

void signalGameOver()
{
  int player = roc.getPlayersPosition();
  int target = roc.getTargetsPosition();
  
  // Set all LEDS to the winning color except for the player and target LED
  for (int i = 0; i < 16; i++)
  {
    if (!( (player == i) || (target == i) ))
    {
      // set the pixel to the background color
      grb.setColor(i,goColor[0], goColor[1], goColor[2]);
      grb.show();
      delay(100);
    } // if
  } // for 

  //blink the player and target LED
  for (int i = 0; i < 20; i++)
  {
    // blink the player led
    if (i % 2 == 0)
    {
      grb.setColor(roc.getPlayersPosition(), 0, 0, 0);
      grb.show();
      delay(10);
      grb.setColor(roc.getPlayersPosition(), plColor[0], plColor[1], plColor[2]);
      grb.show();
      delay(10);
    } // if
    
    // blink the target LED
    else
    {
      grb.setColor(roc.getTargetsPosition(), 0, 0, 0);
      grb.show();
      delay(10);
      grb.setColor(roc.getTargetsPosition(), trgColor[0], trgColor[1], trgColor[2]);
      grb.show();
      delay(10);
    }// else
  } // for

  // blink life LEDs
   for (int k = 0; k < 40; k++)
   {
    if (k % 2 == 0)
    {
      digitalWrite(lifeA, HIGH);
      digitalWrite(lifeB, HIGH);
      digitalWrite(lifeC, HIGH);
      delay(100);
    }
    else
    {
      digitalWrite(lifeA, LOW);
      digitalWrite(lifeB, LOW);
      digitalWrite(lifeC, LOW);
      delay(100);
    }
   }// for

   delay(30000);
   beginGame();
}

void signalGameWon()
{
  int player = roc.getPlayersPosition();
  int target = roc.getTargetsPosition();
  // Set all LEDS to the winning color except for the player and target LED
  for (int i = 0; i < 16; i++)
  {
    if (!( (player == i) || (target == i) ))
    {
      // set the pixel to the background color
      grb.setColor(i,winColor[0], winColor[1], winColor[2]); // should be orange or some other color???
      grb.show();
      delay(100);
    } // if
  } // for 

  //blink the player and target LED
  for (int i = 0; i < 20; i++)
  {
    // blink the player led
    if (i % 2 == 0)
    {
      grb.setColor(roc.getPlayersPosition(), 0, 0, 0);
      grb.show();
      delay(10);
      grb.setColor(roc.getPlayersPosition(), plColor[0], plColor[1], plColor[2]);
      grb.show();
      delay(10);
    } // if
    // blink the target LED
    else
    {
      grb.setColor(roc.getTargetsPosition(), 0, 0, 0);
      grb.show();
      delay(10);
      grb.setColor(roc.getTargetsPosition(), trgColor[0], trgColor[1], trgColor[2]);
      grb.show();
      delay(10);
    }// else
  } // for

  // blink life LEDs
   for (int k = 0; k < 40; k++)
   {
    if (k % 2 == 0)
    {
      digitalWrite(lifeA, HIGH);
      digitalWrite(lifeB, HIGH);
      digitalWrite(lifeC, HIGH);
      delay(100);
    }
    else
    {
      digitalWrite(lifeA, LOW);
      digitalWrite(lifeB, LOW);
      digitalWrite(lifeC, LOW);
      delay(100);
    }
   }// for

   delay(30000);
   beginGame();
} // game won

void makeGuess_ISR()
{
  guess = roc.getPlayersPosition();
}
