/**
 * Malik Roc
 * CS298 Embedded Systems
 * Final Project - RevRoc Game
 * RevRoc Library - v1
 * RevRoc.h
 */
 
 #ifndef __REVROC_H__
 #define __REVROC_H__
 
 #include <Arduino.h>
 #include <RGB.h>
 
 struct Marker
{
	int pixelNum = -1;
	int above = -1;
	int below = -1;
	int left  = -1;
	int right = -1;
	bool operator==(Marker& mkr);
	bool operator==(int& mkr);
	/*
	 set method
	 */
	void setMarker(int pNum, int abv, int blw, int lft, int rht);
	/*
	 get functions - my not need
	 */
	int getPixelNum();
	int getAbovePos();
	int getBelowPos();
	int getLeftPos();
	int getRightPos();
};

class RevRoc
{
public:
	RevRoc();
	RevRoc(int pin);
	
	void begin();
	void movePlayer(int dir);
	void moveTarget(int dir);
	void verifyGuess(int guess);
	int	 getPlayersPosition();
	
private:
	int RGBpin = 4; 		// default pin is 4
	int numOfPixels = 16;
	RGB rgb(RGBpin, numOfPixels);
	int rgbBGColor[3] = {255, 0, 0};    // background color of rgb
	int plyrColor[3]  = {0, 0, 255};    // player color of rgb
	int trgColor[3]   = {255, 255, 0};  // target color of rgb
	Marker mkrTable[16];	// marker table
	Marker player;			// player
	Marker target;			// target
	
	int points = 0;			// player's points
	int lives  = 3; 		// amount of chances the player has before game over
	
	
	/*
	 	Populate table with values that represent their positon on the RGB LED array
	 */
	void populateTable();
	/*
	 	Change the position of the player within the game
	 */
	void changePositionOfPlayer(int pos);
	/*
	 Change the position of the target within the game
	 */
	void changePositionOfTarget(int pos);
	
	/*
	 	Clears the game board with a given color background
	 */
	void emptyBoard();
	
	/*
	 	Update the player's lives and points if necessary
	 */
	void updatePlayersLife();
	
	/*
	 Update the player's points if necessary
	 */
	void updatePlayersPoints();
	
	/*
	 Signal game over when lives reach 0;
	 */
	void signalGameOver();
	void signalGameWon();
	
	/*
	 	Reset the game
	 */
	void resetRevRoc();
	
	
	/*
	 	Pins on the arduino
	 */
	 
	const int lifeA = 5;
	const int lifeB = 6;
	const int lifeC = 7;
	
	const int pointA = 8;
	const int pointB = 9;
	const int pointC = 10;
	
	
};

#endif