
/**
 * Malik Roc
 * CS298 Embedded Systems
 * 11/09/18
 * Final Project : Hide and Seek
 * Testing products
 * 
 */

//RevRoc roc;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  /*
   * Reading the analog stick
   */
   int xC{analogRead(A3)};
   int yC{analogRead(A2)};
   Serial.print("X: "); Serial.print(xC); Serial.print("\n");
   Serial.print("Y: "); Serial.print(yC); Serial.print("\n");

  /*
   * Move player up
   */
  if (yC < 510)
  {
    //roc.movePlayer(1);
    Serial.println("Movng up!");
  }
  /*
   * Move player right
   */
  else if (xC > 530)
  {
    //roc.movePlayer(2);
    Serial.println("Movng right!");
  }
  /*
   * Move player down
   */
  else if (yC > 530)
  {
    //roc.movePlayer(3);
    Serial.println("Movng down!");
  }
  /*
   * Move player left
   */
  else if  (xC < 510)
  {
    //roc.movePlayer(4)
    Serial.println("Movng left!");
  }
  

}
