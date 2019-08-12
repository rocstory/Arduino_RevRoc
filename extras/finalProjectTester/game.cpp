//
//  game.cpp
//  fall2018Assignments
//
//  Created by Malik Roc on 11/29/18.
//  Copyright © 2018 Malik Roc. All rights reserved.
//

#include "game.hpp"
// #include <iostream>
//using namespace std;

bool Marker::operator==(Marker& mkr)
{
	if (this->pixelNum == mkr.pixelNum)
		if (this->above == mkr.above)
			if (this->below == mkr.below)
				if (this->left == mkr.left)
					if (this->right == mkr.right)
						return true;
	return false;
}

bool Marker::operator==(int& num)
{
	if (this->pixelNum == num)
		return true;
	else return false;
}

void Marker::setMarker(int pNum, int abv, int blw, int lft, int rght)
{
	this->pixelNum = pNum;
	this->above = abv;
	this->below = blw;
	this->left  = lft;
	this->right = rght;
}

int Marker::getAbovePos()
{
	return this->above;
}

int Marker::getBelowPos()
{
	return this->below;
}

int Marker::getLeftPos()
{
	return this->left;
}

int Marker::getRightPos()
{
	return this->right;
}

/*
 			Game class
 */

RevRoc::RevRoc()
{
	
}

RevRoc::RevRoc(int pin)
{
	RGBpin = pin;
}

void RevRoc::begin()
{
	//rgb.clear();
	populateTable();	//populate the table
	resetRevRoc();		// reset the game score
	//set the player's makrer to be at position 0
	changePositionOfPlayer(0);
	// set the target's position to a random place on the board
	//randomSeed[2];
	//int pos = random(16);
	changePositionOfTarget(9);
	//set all the LEDs to the same color
	emptyBoard();
}

void RevRoc::populateTable()
{
	
	int mkrMap[16][5] =
	{
		//respective to the setMarker function
		{0 , 1,-1,-1, 7},		// 0
		{1 , 2, 0,-1, 6},		// 1
		{2 , 3, 1,-1, 5},		// 2
		{3 ,-1, 2,-1, 3},		// 3
		
		{4 ,-1, 5, 3,11},		// 4
		{5 , 4, 6, 2,10},		// 5
		{6 , 5, 7, 1, 9},		// 6
		{7 , 6,-1, 0, 8},		// 7
		
		{8 , 9,-1, 7,15},		// 8
		{9 ,10, 8, 6,14},		// 9
		{10,11, 9, 5,13},		// 10
		{11,-1,10, 5,13},    	// 11
		
		{12,-1,13,11,-1},		// 12
		{13,12,14,10,-1},		// 13
		{14,13,15, 9,-1},		// 14
		{15,14,-1, 8,-1}		// 15
	};
	
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; i < 5; i++)
		{
			mkrTable[i].setMarker( mkrMap[i][j+0], mkrMap[i][j+1],
								   mkrMap[i][j+2], mkrMap[i][j+3],
								   mkrMap[i][j+4]
								  );
		}
	} // for
} // populate table

void RevRoc::changePositionOfPlayer(int pos)
{
	// Set the previous pixel to the background before moving
	// rgb.setColor(player.pixelNum, rgbBGColor[0], rgbBGColor[1], rgbBGColor[2]);
	// rgb.show();
	
	// looking for the matching pixel on the board
	for (int i = 0; i < 16; i++)
	{
		if (mkrTable[i] == pos)
			player = mkrTable[i];
	}
	
	// set it to the player color
	//rgb.setColor(player.pixelNum, plyrColor[0], plyrColor[1], plyrColor[2]);
	//rgb.show();
	//Serial.print("Pixel #: "); Serial.println(player.pixelNum);
}

void RevRoc::changePositionOfTarget(int pos)
{
	// Set the previous pixel to the background before moving
	// rgb.setColor(target.pixelNum, rgbBGColor[0], rgbBGColor[1], rgbBGColor[2]);
	// rgb.show();
	
	// looking for the matching pixel on the board
	for (int i = 0; i < 16; i++)
	{
		if (mkrTable[i] == pos)
			target = mkrTable[i];
	}
	
	// set it to the target color
	//rgb.setColor(target.pixelNum, trgColor[0], trgColor[1], trgColor[2]);
	//rgb.show();
	//Serial.print("Pixel #: "); Serial.println(target.pixelNum);
}

void RevRoc::emptyBoard()
{
	// set all pixels on the board to the same color
	for (int i = 0; i < 16; i++)
	{
		// rgb.setColor(i, rgbBGColor[0], rgbBGColor[1], rgbBGColor[2]);
		// rgb.show();
		// Serial.print("Setting pixel: "); Serial.println(i);
	} // for
} // clearBoard()


void RevRoc::verifyGuess( int guess)
{
	
	// gaining a point
	if (target == guess)
	{
		//Serial.println("Target hit!");
		points += 1;
		//Serial.println("Gained a point!");
		updatePlayersPoints();
	}
	
	// losing a life
	else
	{
		//Serial.println("Target missed!");
		lives -= 1;
		//Serial.println("Lost a life!");
		updatePlayersLife();
	}
}

void RevRoc::updatePlayersLife()
{
	switch (lives)
	{
		case 0 :
			//digitalWrite(lifeA, LOW);
			//digitalWrite(lifeB, LOW);
			//digitalWrite(lifeC, LOW);
			//Serial.print("Lives: "); Serial.print(lives); Serial.println("Game Over!");
			signalGameOver();
			break;
		case 1:
			//digitalWrite(lifeA, HIGH);
			//digitalWrite(lifeB, LOW);
			//digitalWrite(lifeC, LOW);
			//Serial.print("Lives: "); Serial.print(lives); Serial.println(" left!");
			break;
		case 2:
			//digitalWrite(lifeA, HIGH);
			//digitalWrite(lifeB, HIGH);
			//digitalWrite(lifeC, LOW);
			//Serial.print("Lives: "); Serial.print(lives); Serial.println(" left!");
		default:
			//Serial.print("No lives lost - "); Serial.print(lives); Serial.println(" lives!");
	}
	
}

void RevRoc::updatePlayersPoints()
{
	switch (points)
	{
		case 1 :
			//digitalWrite(pointA, HIGH);
			//digitalWrite(pointB, LOW);
			//digitalWrite(pointC, LOW);
			//Serial.print("Points: "); Serial.print(points); Serial.println("!");
			break;
		case 2:
			//digitalWrite(lifeA, HIGH);
			//digitalWrite(lifeB, HIGH);
			//digitalWrite(lifeC, LOW);
			//Serial.print("Points: "); Serial.print(points); Serial.println("!");
			break;
		case 3:
			//digitalWrite(lifeA, HIGH);
			//digitalWrite(lifeB, HIGH);
			//digitalWrite(lifeC, HIGH);
			//Serial.print("Points: "); Serial.print(points); Serial.println("! Congratulations, you won!");
			signalGameWon();
		default:
			//Serial.print("Points: "); Serial.println(points);
	}
}

void RevRoc::signalGameOver()
{
	// SET ALL LEDS to RED except the player and target's position
	for (int i = 0; i < 16; i++)
	{
		if (!(player == i) || !(target == i))
		{
			// set the pixel to the background color
			// rgb.setColor(i, 0, 0, 255);
			// rgb.show();
			// delay(100);
		} // if
	} // for
	
	//blink the player and the target LED
	for (int i = 0; i < 20; i++)
	{
		// blink the player
		if (i % 2 == 0)
		{
			
			// rgb.setColor(i, rgbBGColor[0], rgbBGColor[1], rgbBGColor[2]); 			// set to background
			// rgb.setColor(player.pixelNum, plyrColor[0], plyrColor[1], plyrColor[2]);	// set to player color
			// delay(100);
		}
		else
		{
			// rgb.setColor(i, rgbBGColor[0], rgbBGColor[1], rgbBGColor[2]); 			// set to background
			// rgb.setColor(target.pixelNum, trgColor[0], trgColor[1], trgColor[2]);	// set to target color
			// delay(100);
		}
	}
	
	// blink the lives LEDs several times
	
	for (int k = 0; k < 40; k++)
	{
		if (k % 2 == 0)
		{
			//digitalWrite(lifeA, HIGH);
			//digitalWrite(lifeB, HIGH);
			//digitalWrite(lifeC, HIGH);
			//delay(100);
		}
		else
		{
			//digitalWrite(lifeA, LOW);
			//digitalWrite(lifeB, LOW);
			//digitalWrite(lifeC, LOW);
			//delay(100);
		}
	}
	//delay(30000); // delay for 30 seconds before starting new game
	begin();
} // Signal game over

void RevRoc::resetRevRoc()
{
	points = 0;
	lives = 3;
}

void RevRoc::signalGameWon()
{
	// SET ALL LEDS to ORANGE except the player and target's position
	for (int i = 0; i < 16; i++)
	{
		if (!(player == i) || !(target == i))
		{
			// set the pixel to the background color
			// rgb.setColor(i, 255, 69, 0); // orange
			// rgb.show();
			// delay(100);
		} // if
	} // for
	
	//blink the player and the target LED
	for (int i = 0; i < 20; i++)
	{
		// blink the player
		if (i % 2 == 0)
		{
			// rgb.setColor(player.pixelNum, plyrColor[0], plyrColor[1], plyrColor[2]);	// set to player color
			// rgb.show();
			// delay(100);
		}
		else
		{
			// rgb.setColor(target.pixelNum, trgColor[0], trgColor[1], trgColor[2]);	// set to target color
			// rgb.show();
			// delay(100);
		}
	}
	
	// blink the lives LEDs several times
	
	for (int k = 0; k < 40; k++)
	{
		if (k % 2 == 0)
		{
			//digitalWrite(lifeA, HIGH);
			//digitalWrite(lifeB, HIGH);
			//digitalWrite(lifeC, HIGH);
			//delay(100);
		}
		else
		{
			//digitalWrite(lifeA, LOW);
			//digitalWrite(lifeB, LOW);
			//digitalWrite(lifeC, LOW);
			//delay(100);
		}
	}
}

void RevRoc::movePlayer(int dir)
{
	// check if the player can be moved in such a direction
	switch (dir)
	{
		case 1 :
			// Move the marker upward
			if (player.above != -1)
			{
				changePositionOfPlayer(player.above);
			}
		case 2:
			// Move the marker right
			if (player.right != -1)
			{
				changePositionOfPlayer(player.right);
			}
		case 3:
			// Move the marker down
			if (player.below != -1)
			{
				changePositionOfPlayer(player.below);
			}
		case 4:
			// Move the marker left
			if (player.below != -1)
			{
				changePositionOfPlayer(player.left);
			}
	}
}

/*
 	May not need
 */

void RevRoc::moveTarget(int dir)
{
	// check if the target can be moved in such a direction
	switch (dir)
	{
		case 1 :
			// Move the marker upward
			if (target.above != -1)
			{
				changePositionOfTarget(target.above);
			}
		case 2:
			// Move the marker right
			if (target.right != -1)
			{
				changePositionOfTarget(target.right);
			}
		case 3:
			// Move the marker down
			if (target.below != -1)
			{
				changePositionOfTarget(target.below);
			}
		case 4:
			// Move the marker left
			if (target.below != -1)
			{
				changePositionOfTarget(target.left);
			}
	}
}




