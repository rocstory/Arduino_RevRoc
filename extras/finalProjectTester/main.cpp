//
//  main.cpp
//  fall2018Assignments
//
//  Created by Malik Roc on 11/29/18.
//  Copyright © 2018 Malik Roc. All rights reserved.
//

#include "RevRoc.h"
#include <iostream>
using namespace std;

RevRoc roc;
int main()
{
	int quitNum = 0;
	//int dir = 0;
	
	roc.begin();
	while (quitNum != 999)
	{
		// testing directionality - works
		cout << "Player is at " << roc.getPlayersPosition() << " Score: " << roc.getPoints() << endl;
		cout << "Target is at " << roc.getTargetsPosition() << " Lives: " << roc.getLives()  << endl;
		cout << "Move player in direction ";
		cin >>  quitNum;
		roc.movePlayer(quitNum); // works
		cout << "Guess position " << roc.getPlayersPosition() << "? (press 9)";
		int guess = 0;
		cin >> guess;
		if (guess == 9)
		{
			roc.verifyGuess(roc.getPlayersPosition());
		}
	}
	cout << "Done!" << endl;
	
	return 0;
}

