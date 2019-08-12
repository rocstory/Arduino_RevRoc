#include <RevRoc.h>

/**
 * Malik Roc
 * CS298 Embedded Systems
 * 11/09/18
 * Final Project : Hide and Seek
 * Testing products
 * 
 */


RevRoc roc;

#define button 2

volatile int guess = -1;

byte colorA = 20;
byte colorB = 20;
byte colorC = 20; 

void setup() 
{
  Serial.begin(9600);
  roc.begin();
  attachInterrupt(0, makeGuess_ISR, CHANGE);
   
}

void loop() {
  
  /*
   * Reading the analog stick
   */
   int xC = analogRead(A3);
   int yC = analogRead(A2);

  /*
   * Move player up
   */
  if (yC < 510)
  {
    
    roc.movePlayer(1);
    Serial.println("Moving up!");
    delay(100);
    
  }
  /*
   * Move player down
   */
  else if (yC > 530)
  {
    
    roc.movePlayer(3);
    Serial.println("Moving down!");
    
    delay(100);
  }
  /*
   * Move player right
   */
  else if (xC > 530)
  {
    roc.movePlayer(2);
    Serial.println("Moving right!");
    delay(100);
  }
  /*
   * Move player left
   */
  else if  (xC < 510)
  {
    roc.movePlayer(4);
    Serial.println("Moving left!");
    delay(100);
  }
  
  /*
   * button
   */ 
   if (guess != -1)
   {
    // a guess has been made
    roc.verifyGuess(guess);
    Serial.println("Making a guess");
    guess = -1;
   } 
    
  delay(100);
}

void makeGuess_ISR()
{
  guess = roc.getPlayersPosition();
}
