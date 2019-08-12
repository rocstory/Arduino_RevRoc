# Revealing Roc

## Story behind Revealing Roc
Roc is an individual who contains many secrets, however to unlock such secrets you must solve one of Roc’s several puzzles. 
One of her puzzle’s is called Revealing Roc. It requires you to find a Roc Bulb 3 times, however you only have 3 tries to do so. 

## Objective

The objective of the puzzle is to move through a 4x4 board to find the 
Roc Bulb 3 times.

## Controls


2-Axis Joystick
	Moves the player’s current position up, down, left, right; respectively in the direction in which they move the joystick

Switch button
	Pressing the button checks to see if the player’s current position is where the Roc Bulb is hidden.


## Hardware
The following hardware devices were used in creating Revealing Roc:

- 6x LEDs
- 3 Red (indicating the player’s lives)
- 3 Green (indicating the player’s lives)
- 1x 4x4 WS2812B LED Matrix
  The game board
- 1x Switch
  The button that submits the player’s guess.
- 1x 2-Axis Joystick
  Allows the player to move across the board
- 1x Seven-segment display
  Displays a set of characters after the player obtains 3 points.
- 1x 74HC595 shift bit register
  Used to display the secret message.
- 1x Arduino Nano
  Controls the behavior of the hardware being used

## Software

### RevRoc Library
The RevRoc library simulates the LED Matrix
Maintains the position of the target and player throughout the game. It also maintains the number of lives and points the player has throughout the puzzle.
Returns the values that indicates the position of the player and target.
Returns the values that indicate the lives and points throughout the game.
###RevRoc Sketch
Obtains the direction in which the player wants to move
Listens out for the user to press the guess button.
Displays the player’s current position throughout the game
Utilizes the LEDs to notify the player of their lives and points.
Displays the target’s position when the game comes to an end.


## Challenges

Throughout designing this project I ran into several challenges. One of the challenges that I faced was developing the library to manage both the mapping of the LED Matrix and the display of the current’s position. I faced this challenge by making the library focused solely on: the mapping of the LED Matrix, the position of the player and target, along with the amount of lives and points the player has.

