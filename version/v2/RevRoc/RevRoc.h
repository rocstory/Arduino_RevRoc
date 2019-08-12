/**
 * Malik Roc
 * CS298 Embedded Systems
 * Final Project - RevRoc Game
 * RevRoc Library - v2
 * RevRoc.h
 */

#ifndef __REVROC_H__
#define __REVROC_H__


#include <Arduino.h>

struct Marker
{
	int pixelNum = -1;
	int above    = -1;
	int below	 = -1;
	int left	 = -1;
	int right 	 = -1;
	bool operator==(Marker& mkr);
	bool operator==(int& mkr);
	
	/*
	 Creates a marker with the given param
	 */
	void setMarker(int pNum, int abv, int blw, int lft, int rht);
};

class RevRoc
{
public:
	RevRoc();
	void begin();
	void movePlayer(int dir);
	void changePositionOfTarget(int pos);
	void verifyGuess(int guess);
	
	int getPlayersPosition();
	int getTargetsPosition();
	int getLives();
	int getPoints();
private:
	Marker mkrTable[16];
	Marker player;
	Marker target;
	
	int points = 0;		// player's points
	int lives = 3;		// amount of chances the player has before reaching game over
	
	void populateTable();
	void changePositionOfPlayer(int pos);

	
	void resetRevRoc();
	
};

#endif
