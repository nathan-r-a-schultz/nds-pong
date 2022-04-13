#include <nds.h>
#include <gl2d.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// This code is a bit of a mess, especially with variables
// I'm still learning C++ and this is more of an experiment than a legitimate game
// My goal is start with the basics and then learn more complex things
// Any feedback or tips would be appreciated

// TODO:
// add sprites
// add music
// add GUI

void credAndChanges()
{
	iprintf("\x1b[0;0H                                      \n");
	iprintf("   \x1b[32m\x1b[1;0HProgram written by Natsch\n");
	iprintf("   \x1b[30;2m\x1b[2;0HPrototype v1.3\n");
	iprintf("   \x1b[30;2m\x1b[3;0HLatest changes:\n");
	iprintf("   \x1b[30;2m\x1b[4;0HAdded pause functionality\n");
	iprintf("   \x1b[30;2m\x1b[5;0HDecreased ball size\n");
	iprintf("   \x1b[30;2m\x1b[5;0HAdded restarting game upon loss\n");
}

void clearPrint()
{
	iprintf("\x1b[8;0H                                      \n");

	for (int i = 0; i < 9; i++)
	{
		iprintf("                                      \n");
	}
}

int main(void)
{

	// these variables are pretty self explanatory
	float xBoxLoc = 0;
	float yBoxLoc = 0;
	int boxLength = 10;
	int boxWidth = 10;
	float xBoxSpeed = 1.0;
	float yBoxSpeed = 1.0;
	int paddleLength = 50;
	int paddleWidth = 10;
	int xPaddleLoc = 128 - paddleLength / 2;
	int yPaddleLoc = 157;
	float paddleSpeed = 10;
	int speedTracker = 0;
	bool gameOver = false;
	bool pause = false;

	int debugMode = 1;

	// init console
	consoleDemoInit();

	// init the screen
	videoSetMode(MODE_5_3D);
	glScreen2D();

	while (1)
	{

		glBegin2D();

		glBoxFilled(xBoxLoc, yBoxLoc, xBoxLoc + boxLength, yBoxLoc + boxWidth, RGB15(255, 255, 0));
		glBoxFilled(xPaddleLoc, yPaddleLoc, xPaddleLoc + paddleLength, yPaddleLoc + paddleWidth, RGB15(255, 255, 255));

		if (pause == false) 
		{
			xBoxLoc += xBoxSpeed; // goes forward once every frame according to boxSpeed
			yBoxLoc += yBoxSpeed; // goes down once every frame according to boxSpeed
		}

		if (xBoxLoc < xPaddleLoc + paddleLength && xBoxLoc + boxLength > xPaddleLoc && yBoxLoc + boxWidth >= yPaddleLoc && yBoxLoc <= yBoxLoc + paddleWidth) // checks if the box and paddle collide
		{
			speedTracker++;
			if (speedTracker % 5 == 0 && speedTracker > 0) {
				// these if statements seem redundant but it fixes some bugs
				if (xBoxSpeed > 0) {
					xBoxSpeed = xBoxSpeed * 1.1; // increase speed
				}
				else if (xBoxSpeed < 0) {
					xBoxSpeed = xBoxSpeed * 1.1; // increase speed
				}
				if (yBoxSpeed > 0) {
					yBoxSpeed = yBoxSpeed * 1.1; // increase speed
				}
				else if (yBoxSpeed < 0) {
					yBoxSpeed = yBoxSpeed * 1.1; // increase speed
				}
			}
			yBoxSpeed *= -1;

		}

		if (xBoxLoc <= 0 || xBoxLoc + boxLength > 256) // handles bouncing for left and right
		{
			xBoxSpeed = xBoxSpeed * -1.0;
		}
		if (yBoxLoc <= 0) // handles bouncing for top and bottom
		{
			yBoxSpeed = yBoxSpeed * -1.0;
		}
		if (yBoxLoc + boxWidth > 191)
		{
			gameOver = true;
			xBoxSpeed = 0;
			yBoxSpeed = 0;
		}

		

		if (xPaddleLoc < 0) // prevents the paddle from going too far left
		{
			xPaddleLoc = 0;
		}

		if (xPaddleLoc > 255 - paddleLength) // prevents the paddle from going too far right
		{
			xPaddleLoc = 255 - paddleLength;
		}

		scanKeys();
		
		if (gameOver == false && pause == false) {
			// changes location of the paddle based on which key is pressed
			if (keysHeld() & KEY_LEFT && xPaddleLoc > 0)
			{
				xPaddleLoc -= paddleSpeed;
			}
			if (keysHeld() & KEY_RIGHT && xPaddleLoc < 255 - paddleLength)
			{
				xPaddleLoc += paddleSpeed;
			}
		}

		// pause is false then enable debug mode upon keypress
		if (pause == false && keysUp() & KEY_X)
		{
				if (debugMode == 0)
				{
					debugMode = 1;
				}
				else if (debugMode == 1)
				{
					debugMode = 0;
				}
		}
		
		// pause game when the start key is pressed
		if (keysUp() & KEY_START)
		{
			if (pause == false)
			{
				pause = true;
			}
			else if (pause == true)
			{
				pause = false;
			}
		}

		// restarts game if select key is pressed when the game is over
		if (keysUp() & KEY_SELECT && gameOver == true)
		{

				gameOver = false;
				xBoxLoc = 0;
				yBoxLoc = 0;
				xBoxSpeed = 1;
				yBoxSpeed = 1;
				speedTracker = 0;

		}


		if (debugMode == 1 && gameOver == false) 
		{

			credAndChanges();
			iprintf("\x1b[32m\x1b[10;0HDebug:\n");
			iprintf("xBoxLoc: %03f\n", xBoxLoc);
			iprintf("yBoxLoc: %03f\n", yBoxLoc);
			iprintf("xBoxSpeed: %03f\n", xBoxSpeed);
			iprintf("yBoxSpeed: %03f\n", yBoxSpeed);
			iprintf("xPaddleLoc: %03i\n", xPaddleLoc);
			iprintf("yPaddleLoc: %03i\n", yPaddleLoc);
			iprintf("speedTracker: %03i\n", speedTracker);
			iprintf("   \x1b[8;0H                      \n");

		}
		else if (debugMode == 0 && gameOver == false)
		{
			clearPrint();
			credAndChanges();
			iprintf("   \x1b[8;0H                      \n");

		}
		if (gameOver == true)
		{
			iprintf("   \x1b[30;2m\x1b[8;0HPress SELECT to retry\n");
		}

		glEnd2D();
		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}