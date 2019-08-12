/**
 * Malik Roc
 * CS298 Embedded Systems
 * Final Project - RevRoc Game
 * RevRoc Library - v2
 * RevRoc.cpp
 */

#include "RevRoc.h"

bool Marker::operator==(Marker& mkr)
{
	if (this->pixelNum == mkr.pixelNum)
	{
		if (this->above == mkr.above)
		{
			if (this->right == mkr.right)
			{
				if (this->below == mkr.below)
				{
					if (this->left == mkr.left)
					{
						return true;
					} // if left
				} // if below
			} // if right
		} // if above
	} // if pixel num
	
	return false;
} // ==

bool Marker::operator==(int& mkr)
{
	if (this->pixelNum == mkr)
		return true;
	else
		return false;
}

void Marker::setMarker(int pNum, int abv, int blw, int lft, int rht)
{
	this->pixelNum = pNum;
	this->above    = abv;
	this->right	   = rht;
	this->below	   = blw;
	this->left	   = lft;
}


/*
 RevRoc
 */
RevRoc::RevRoc()
{
	
}

void RevRoc::begin()
{
	populateTable();			// creates a table that maps the rgb led array
	resetRevRoc();				// resets the values of the score and player
	changePositionOfPlayer(0);	// changes the position of the player back to 0
	
	// pick a random postion from 0-16 and place it on the board - 
	// randomSeed(2);
	// int pos = 6; //random[16];
	// changePositionOfTarget(pos); // set the position of the target to the random position
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
			break;
		case 2:
			// Move the marker right
			if (player.right != -1)
			{
				changePositionOfPlayer(player.right);
			}
			break;
		case 3:
			// Move the marker down
			if (player.below != -1)
			{
				changePositionOfPlayer(player.below);
			}
			break;
		case 4:
			// Move the marker left
			if (player.left != -1)
			{
				changePositionOfPlayer(player.left);
			}
			break;
	}
}

void RevRoc::verifyGuess(int guess)
{
	
	// gaining a point
	if (target == guess)
		points += 1;
	
	// losing a life
	else
		lives -= 1;
}


int RevRoc::getPlayersPosition()
{
	return player.pixelNum;
}

int RevRoc::getTargetsPosition()
{
	return target.pixelNum;
}

int RevRoc::getPoints()
{
	return points;
}

int RevRoc::getLives()
{
	return lives;
}

void RevRoc::populateTable()
{
	
	int mkrMap[16][5] =
	{
		//respective to the setMarker function
		{0 , 1,-1,-1, 7},		// 0
		{1 , 2, 0,-1, 6},		// 1
		{2 , 3, 1,-1, 5},		// 2
		{3 ,-1, 2,-1, 4},		// 3
		
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
	{		mkrTable[i].setMarker( mkrMap[i][0], mkrMap[i][1],
							  mkrMap[i][2], mkrMap[i][3],
							  mkrMap[i][4]
							  );
	} // for
	
} // populate table


// sets the position of the player to the given 'pos'
void RevRoc::changePositionOfPlayer(int pos)
{
	// looking for the matching pixel on the table
	for (int i = 0; i < 16; i++)
	{
		if (mkrTable[i] == pos)
		{
			player = mkrTable[i];
		}
	}
}

// sets the position of the player to the given 'pos'
void RevRoc::changePositionOfTarget(int pos)
{
	// looking for the matching pixel on the table
	for (int i = 0; i < 16; i++)
	{
		if (mkrTable[i] == pos)
			target = mkrTable[i];
	}
}

void RevRoc::resetRevRoc()
{
	lives  = 3;
	points = 0;
}


