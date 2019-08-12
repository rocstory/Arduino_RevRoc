#include <RGB.h>
/**
 * Malik Roc
 * CS298 Embedded Systems
 * 11/09/18
 * Final Project : Hide and Seek
 * Testing products
 * 
 */

//RevRoc roc;
#define button 2
int rgbPin =  9;

RGB rgb(rgbPin, 16);
volatile int guess = -1;

byte colorA = 20;
byte colorB = 20;
byte colorC = 20; 


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(0, makeGuess_ISR, CHANGE);  // <-- this doesnt work? why?
  rgb.clear();

  randomSeed[2];
}

void loop() {
  int  num = random(16);
  Serial.print("Random num: "); Serial.println(num); 
  //attachInterrupt(0, makeGuess_ISR, CHANGE); // but this does... why?
  /*
   * Reading the analog stick
   */
   int xC = analogRead(A5);
   int yC = analogRead(A4);
   //Serial.print("X: "); Serial.print(xC); Serial.print("\n");
   //Serial.print("Y: "); Serial.print(yC); Serial.print("\n");

  /*
   * Move player up
   */
  if (yC < 510)
  {
    
    //roc.movePlayer(1);
    Serial.println("Moving up!");
    if (colorB >= 255)
    {
      colorB = 20;
    }
    else if (colorB <= 0)
    {
      colorB = 20;
    }
    else
    {
      colorB += 20;
    }
    rgb.setColor(5, colorB, 0, 0);
    rgb.show();
    delay(100);
    
  }
  /*
   * Move player down
   */
  else if (yC > 530)
  {
    
    //roc.movePlayer(3);
    Serial.println("Moving down!");
    
    if (colorB >= 255)
    {
      colorB = 20;
    }
    else if (colorB <= 0)
    {
      colorB = 20;
    }
    else
    {
      colorB += 20;
    }
    rgb.setColor(7, colorB, 0, 0);
    rgb.show();
    delay(100);
  }
  /*
   * Move player right
   */
  else if (xC > 530)
  {
    //roc.movePlayer(2);
    Serial.println("Moving right!");
    if (colorA >= 255)
    {
      colorA = 20;
    }
    else if (colorA <= 0)
    {
      colorA = 20;
    }
    else
    {
      colorA += 20;
    }
    rgb.setColor(9, 0, 0, colorA);
    rgb.show();
    delay(100);
  }
  /*
   * Move player left
   */
  else if  (xC < 510)
  {
    //roc.movePlayer(4)
    Serial.println("Moving left!");
    if (colorA >= 255)
    {
      colorA = 20;
    }
    else if (colorA <= 0)
    {
      colorA = 20;
    }
    else
    {
      colorA += 20;
    }
    rgb.setColor(1, 0, 0, colorA);
    rgb.show();
    delay(100);
  }
  
  /*
   * button
   */ 
   
   if (guess == 999)
   {
    Serial.println("HIIIIIIT!");
    rgb.setColor(6, 50, 50, 50);
    rgb.show();
    delay(500);
    rgb.setColor(6, 0, 0, 0);
    rgb.show();  
   }
  
  //set guess to -1
  if (guess != -1)
  {
    guess = -1;
    rgb.setColor(6, 0, 0, 0);
    rgb.show();  
  }
  delay(100);
  
}

void makeGuess_ISR()
{
  guess = 999;
}
