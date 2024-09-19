#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <nds.h>
#include <gl2d.h>

// TODO:
// add sprites
// add music
// add GUI
// fix clipping bug with paddle and box

void menu(int mode, int selection, int points, int xBoxLoc, int yBoxLoc, int xPaddleLoc, int yPaddleLoc, float xBoxSpeed, float yBoxSpeed)
{

	// this code is part of a workaround to print floats
	int xBoxSpeedInt = (int)(xBoxSpeed * 1000000);
	int yBoxSpeedInt = (int)(yBoxSpeed * 1000000);

	switch (mode)
	{
	case 0: // default menu
		iprintf("   \x1b[30;2m\x1b[0;0HMain menu:\n");
		iprintf("   \x1b[30;2m\x1b[1;0H( )Controls\n");
		iprintf("   \x1b[30;2m\x1b[2;0H( )Credits\n");
		iprintf("   \x1b[30;2m\x1b[3;0H( )Version info\n");
		iprintf("   \x1b[30;2m\x1b[4;0H( )Debug\n");
		break;
	case 1: // control info
		iprintf("   \x1b[30;2m\x1b[1;0HControls:\n");
		iprintf("   \x1b[30;2m\x1b[3;0HD-PAD LEFT to move the paddle\n");
		iprintf("   \x1b[30;2m\x1b[4;0Hleft.                        \n");
		iprintf("   \x1b[30;2m\x1b[5;0H\n");
		iprintf("   \x1b[30;2m\x1b[6;0HD-PAD RIGHT to move the paddle\n");
		iprintf("   \x1b[30;2m\x1b[7;0Hright.                        \n");
		iprintf("   \x1b[30;2m\x1b[8;0H\n");
		iprintf("   \x1b[30;2m\x1b[9;0HSELECT to restart the game when\n");
		iprintf("   \x1b[30;2m\x1b[10;0Hyou lose.                \n");
		iprintf("   \x1b[30;2m\x1b[11;0H\n");
		iprintf("   \x1b[30;2m\x1b[12;0HSTART to pause the game.\n");
		iprintf("   \x1b[30;2m\x1b[13;0H\n");
		iprintf("   \x1b[30;2m\x1b[14;0HB to back out of submenus.\n");
		iprintf("   \x1b[30;2m\x1b[15;0H\n");
		iprintf("   \x1b[30;2m\x1b[16;0HA to enter a submenu.          \n");
		iprintf("   \x1b[30;2m\x1b[17;0H\n");
		iprintf("   \x1b[30;2m\x1b[18;0HD-PAD UP to navigate up menus.\n");
		iprintf("   \x1b[30;2m\x1b[19;0HD-PAD DOWN to navigate down\n");
		iprintf("   \x1b[30;2m\x1b[20;0Hmenus.\n");
		iprintf("   \x1b[32m\x1b[22;0HPress B to exit submenu\n");

		break;

	case 2: // credits info
		iprintf("   \x1b[30;2m\x1b[1;0HCredits:\n");
		iprintf("   \x1b[30;2m\x1b[2;0HCreated by Nathan Schultz\n");
		iprintf("   \x1b[32m\x1b[22;0HPress B to exit submenu\n");
		break;
	case 3: // changes info
		iprintf("   \x1b[30;2m\x1b[1;0HVersion info:\n");
		iprintf("   \x1b[30;2m\x1b[2;0HPrototype v0.0.6\n");
		iprintf("   \x1b[30;2m\x1b[4;0HLatest changes:\n");
		iprintf("   \x1b[30;2m\x1b[5;0HPopulated debug mode\n");
		iprintf("   \x1b[30;2m\x1b[6;0HCleaned up the main menu\n");
		iprintf("   \x1b[32m\x1b[22;0HPress B to exit submenu\n");
		break;
	case 4:
		iprintf("   \x1b[32;2m\x1b[1;0HPoints: %d\n", points);
		iprintf("   \x1b[32;2m\x1b[2;0HxBoxLoc: %d\n", xBoxLoc);
		iprintf("   \x1b[32;2m\x1b[3;0HyBoxLoc: %d\n", yBoxLoc);
		iprintf("   \x1b[32;2m\x1b[4;0HxPaddleLoc: %d\n", xPaddleLoc);
		iprintf("   \x1b[32;2m\x1b[5;0HyPaddleLoc: %d\n", yPaddleLoc);

		// the following code is a workout to print floats
		iprintf("   \x1b[32;2m\x1b[6;0HxBoxSpeed: %d.%06d\n", xBoxSpeedInt / 1000000, abs(xBoxSpeedInt % 1000000));
		iprintf("   \x1b[32;2m\x1b[7;0HyBoxSpeed: %d.%06d\n", yBoxSpeedInt / 1000000, abs(yBoxSpeedInt % 1000000));

		iprintf("   \x1b[32m\x1b[22;0HPress B to exit submenu\n");
		break;
	default: // menu to handle errors in case of an invalid mode
		iprintf("   \x1b[30;2m\x1b[1;0HError 0000");
		break;
	}

	if (mode == 0)
	{
		switch (selection)
		{
		case 0:
			// note that without the "\x1b[32m\x1b[15;0H" at the end of printf, this statement will print three blank characters
			// these blank characters override previously printed characters
			// we avoid overriding existing text by shoving the blank characters off screen (row 33, column 0)
			// this applies for all cases
			iprintf("\x1b[32m\x1b[1;1H>\x1b[32m\x1b[33;0H");
			break;
		case 1:
			iprintf("\x1b[32m\x1b[2;1H>\x1b[32m\x1b[33;0H");
			break;
		case 2:
			iprintf("\x1b[32m\x1b[3;1H>\x1b[32m\x1b[33;0H");
			break;
		case 3:
			iprintf("\x1b[32m\x1b[4;1H>\x1b[32m\x1b[33;0H");
			break;
		}
	}

	//render the rest of the menu after selector has been moved
	if (mode == 0) {
		iprintf("   \x1b[32;2m\x1b[18;0HPoints: %d\n", points);
		iprintf("   \x1b[32;2m\x1b[20;0HTo navigate menus, use D-PAD UP\n");
		iprintf("   \x1b[32;2m\x1b[21;0Hand DOWN. Press A to enter a\n");
		iprintf("   \x1b[32;2m\x1b[22;0Hmenu and B to exit the menu.\n");
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
	int points = 0;
	bool gameOver = false;
	bool pause = false;
	int menuMode = 0;
	int menuSelection = 0;

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
			points++;
			if (points % 5 == 0 && points > 0) {
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

		// pause game when the start key is pressed
		if (keysUp() & KEY_START)
		{
			switch (pause)
			{
			case false:
				pause = true;
				break;
			case true:
				pause = false;
				break;
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
			points = 0;

		}

		if (keysUp() & KEY_B)
		{
			menuMode = 0;
		}

		if (keysUp() & KEY_A && menuMode == 0)
		{
			if (menuSelection == 0)
			{
				menuMode = 1;
			}
			else if (menuSelection == 1)
			{
				menuMode = 2;
			}
			else if (menuSelection == 2)
			{
				menuMode = 3;
			}
			else if (menuSelection == 3)
			{
				menuMode = 4;
			}

		}
		
		if (menuMode == 0)
		{
			if (keysUp() & KEY_DOWN)
			{
				if (menuSelection >= 0 && menuSelection < 3)
				{
					menuSelection++;
				}
			}
	
			if (keysUp() & KEY_UP)
			{
				if (menuSelection > 0 && menuSelection <= 3)
				{
					menuSelection--;
				}
			}
		}

		if (menuSelection < 0)
		{
			menuSelection = 0;
		}
		else if (menuSelection > 4)
		{
			menuSelection = 4;
		}

		consoleClear();
		menu(menuMode, menuSelection, points, xBoxLoc, yBoxLoc, xPaddleLoc, yPaddleLoc, xBoxSpeed, yBoxSpeed);
		glEnd2D();
		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}
