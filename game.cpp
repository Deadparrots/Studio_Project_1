// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>// This is the main file for the game logic and function
//// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
SGameChar	g_enemy1;
SGameChar	g_enemy2;
SGameChar	g_enemy3;
SGameChar	g_enemy4;
SGameChar	g_enemy5;
SGameChar	g_enemy6;
SGameChar	g_weapon;
SGameChar	g_door;
size_t		deathsound = 0;
size_t		shootsound = 0;
size_t		reloadsound = 0;
size_t		shootfailsound = 0;
int g_shootdist = 0;
int g_shootmaxdist = 10; // Shooting distance of weapon. Can be changed.
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
EWEAPONSTATES g_eWeaponState = Hold;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
int Lives = 3; // Number of lives the player has left (Base Value is 3)
int currentWeapon = 0;
WeaponParameters Weapons[4];
// Console object
Console g_Console(80, 24, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init(void)
{
	generate();
	weapdata();
	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;

	// sets the initial state for the game
	g_eGameState = S_SPLASHSCREEN;
	int enemyX, enemyY;
	fstream myfile("map.txt");
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
			break;
	}
	g_sChar.m_cLocation.X = enemyX;
	g_sChar.m_cLocation.Y = enemyY;
	g_sChar.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy1.m_cLocation.X = enemyX;
	g_enemy1.m_cLocation.Y = enemyY;
	g_enemy1.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy2.m_cLocation.X = enemyX;
	g_enemy2.m_cLocation.Y = enemyY;
	g_enemy2.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy3.m_cLocation.X = enemyX;
	g_enemy3.m_cLocation.Y = enemyY;
	g_enemy3.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy4.m_cLocation.X = enemyX;
	g_enemy4.m_cLocation.Y = enemyY;
	g_enemy4.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy5.m_cLocation.X = enemyX;
	g_enemy5.m_cLocation.Y = enemyY;
	g_enemy5.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy6.m_cLocation.X = enemyX;
	g_enemy6.m_cLocation.Y = enemyY;
	g_enemy6.m_bActive = true;
	g_weapon.m_cLocation.X = 10;
	g_weapon.m_cLocation.Y = 2;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
			break;
	}
	g_door.m_cLocation.X = enemyX;
	g_door.m_cLocation.Y = enemyY;
	g_door.m_bActive = false;
	g_weapon.m_cLocation.X = 10;
	g_weapon.m_cLocation.Y = 2;
	myfile.close();
	// sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(0, 16, L"Consolas");
	reload();
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown(void)
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput(void)
{
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_W] = isKeyPressed(87);
	g_abKeyPressed[K_A] = isKeyPressed(65);
	g_abKeyPressed[K_S] = isKeyPressed(83);
	g_abKeyPressed[K_D] = isKeyPressed(68);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
	// get the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;

	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;
	case S_GAME: gameplay(); // gameplay logic when we are in the game
		break;
	}
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
	clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: renderSplashScreen();
		break;
	case S_GAME: renderGame();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_abKeyPressed[K_SPACE]) // wait for 0.5 seconds to switch to game mode, else do nothing
		g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacter();    // moves the character, collision detection, physics, etc
	sound();			// sound can be played here too.
}

void moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	fstream myfile("map.txt");
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if ((g_abKeyPressed[K_UP] || g_abKeyPressed[K_DOWN] || g_abKeyPressed[K_LEFT] || g_abKeyPressed[K_RIGHT]) && (g_eWeaponState != Hold || Weapons[currentWeapon].Clip == 0))
	{
		shootfailsound = 1;
		bSomethingHappened = true;
	}
	if (Weapons[currentWeapon].Clip > 0)
	{
		if (g_abKeyPressed[K_UP] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireUp;
			if (g_abKeyPressed[K_W])
				g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
			else
				g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_DOWN] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireDown;
			if (g_abKeyPressed[K_S])
				g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y + 1;
			else
				g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_LEFT] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireLeft;
			if (g_abKeyPressed[K_A])
				g_weapon.m_cLocation.X = g_sChar.m_cLocation.X - 1;
			else
				g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_RIGHT] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireRight;
			if (g_abKeyPressed[K_D])
				g_weapon.m_cLocation.X = g_sChar.m_cLocation.X + 1;
			else
				g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
	}
	char * buffer2 = new char[0];
	if (g_eWeaponState == FireUp)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.Y--;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireDown)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.Y++;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireLeft)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.X--;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireRight)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.X++;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}


	if (g_shootdist >= g_shootmaxdist)
	{
		g_eWeaponState = Hold;
		g_weapon.m_cLocation.X = 10;
		g_weapon.m_cLocation.Y = 2;
		g_shootdist = 0;
	}

	if (g_abKeyPressed[K_W] && g_sChar.m_cLocation.Y > 0)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 - 82);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_A] && g_sChar.m_cLocation.X > 0)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 - 1);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_S] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 + 82);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_D] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 + 1);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
	}
	if (
		(g_sChar.m_cLocation.X == g_enemy1.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy1.m_cLocation.Y && g_enemy1.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy2.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y && g_enemy2.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y && g_enemy3.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y && g_enemy4.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y && g_enemy5.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y && g_enemy6.m_bActive == false)
		)
	{
		reload();
		reloadsound += 2;
	}
	if (
		(g_sChar.m_cLocation.X == g_enemy1.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy1.m_cLocation.Y && g_enemy1.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy2.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y && g_enemy2.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y && g_enemy3.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y && g_enemy4.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y && g_enemy5.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y && g_enemy6.m_bActive == true)
		)
	{
		g_sChar.m_bActive = false;
		bSomethingHappened = true;
	}
	if (g_sChar.m_cLocation.X == g_enemy1.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy1.m_cLocation.Y)
	{
		g_enemy1.m_bActive = false;
		g_enemy1.m_cLocation.X = 0;
		g_enemy1.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy2.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y)
	{
		g_enemy2.m_bActive = false;
		g_enemy2.m_cLocation.X = 0;
		g_enemy2.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y)
	{
		g_enemy3.m_bActive = false;
		g_enemy3.m_cLocation.X = 0;
		g_enemy3.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y)
	{
		g_enemy4.m_bActive = false;
		g_enemy4.m_cLocation.X = 0;
		g_enemy4.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y)
	{
		g_enemy5.m_bActive = false;
		g_enemy5.m_cLocation.X = 0;
		g_enemy5.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y)
	{
		g_enemy6.m_bActive = false;
		g_enemy6.m_cLocation.X = 0;
		g_enemy6.m_cLocation.Y = 0;
	}

	switch (rand() % 64)
	{
	case 0:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.X++;
		break;
	case 1:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.Y++;
		break;
	case 2:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.X--;
		break;
	case 3:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.Y--;
		break;
	case 4:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.X++;
		break;
	case 5:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.Y++;
		break;
	case 6:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.X--;
		break;
	case 7:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.Y--;
		break;
	case 8:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.X++;
		break;
	case 9:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.Y++;
		break;
	case 10:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.X--;
		break;
	case 11:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.Y--;
		break;
	case 12:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.X++;
		break;
	case 13:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.Y++;
		break;
	case 14:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.X--;
		break;
	case 15:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.Y--;
		break;
	case 16:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.X++;
		break;
	case 17:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.Y++;
		break;
	case 18:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.X--;
		break;
	case 19:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.Y--;
		break;
	case 20:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.X++;
		break;
	case 21:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.Y++;
		break;
	case 22:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.X--;
		break;
	case 23:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.Y--;
		break;
	}

	myfile.close();


	if (g_abKeyPressed[K_SPACE])
	{
		g_sChar.m_bActive = true;
		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.07; // 125ms should be enough
	}
}
void processUserInput()
{
	// quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
		g_bQuitGame = true;
	if (g_sChar.m_bActive == false) // Took damage
	{
		g_sChar.m_bActive = true;
		Lives--;
		deathsound = 5;
	}
	if (g_enemy1.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy1.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy1.m_bActive == true)
	{
		g_enemy1.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy2.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy2.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy2.m_bActive == true)
	{
		g_enemy2.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy3.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy3.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy3.m_bActive == true)
	{
		g_enemy3.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy4.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy4.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy4.m_bActive == true)
	{
		g_enemy4.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy5.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy5.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy5.m_bActive == true)
	{
		g_enemy5.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy6.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy6.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy6.m_bActive == true)
	{
		g_enemy6.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy1.m_bActive == false &&
		g_enemy2.m_bActive == false &&
		g_enemy3.m_bActive == false &&
		g_enemy4.m_bActive == false &&
		g_enemy5.m_bActive == false &&
		g_enemy6.m_bActive == false)
		g_door.m_bActive = true;
	if (g_door.m_bActive == true && g_sChar.m_cLocation.X == g_door.m_cLocation.X && g_sChar.m_cLocation.Y == g_door.m_cLocation.Y)
	{
		init();
		g_eGameState = S_GAME;
	}
}

void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x1F);
}

void renderSplashScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 9;
	g_Console.writeToBuffer(c, "Use <WASD> to move", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "Use Arrow Keys to attack", 0x09);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 11;
	g_Console.writeToBuffer(c, "Press 'Space' to start", 0x0E);
}

void renderGame()
{
	renderMap();        // renders the map to the buffer first
	renderDoor();
	renderWeapon();
	renderCharacter();  // renders the character into the buffer
	renderEnemy1();
	renderEnemy2();
	renderEnemy3();
	renderEnemy4();
	renderEnemy5();
	renderEnemy6();
	renderUI();
}

void renderMap()
{
	// Set up sample colours, and output shadings
	//const WORD colors[] = {
	//    0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	//    0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	//};

	//COORD c;
	for (int i = 0; i < 12; ++i)
	{
		fstream myfile("map.txt");
		string sLine;
		for (short i = 0; i < 24 * 80; i++)
		{
			if (i % 80 == 0)
				//{
				getline(myfile, sLine);
			//for (size_t i = 0; i < 24; i++)
			//	for (size_t j = 0; j < 80; j++)
			//	{
			//						if (sLine[j] == '#')
			//							sLine[j] = 219;
			//					}
			//			}
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, sLine[i % 80], 0x0F);
		}
		//c.X = 0;
		//c.Y = 0;
		//colour(colors[i]);
		//g_Console.writeToBuffer(c, " °±²Û", colors[i]);
	}
}
void renderUI()
{
	COORD UIBG;
	COORD UI;
	for (int i = 0; g_Console.getConsoleSize().X > i; i++) // For every value of x
	{
		UIBG.X = i;
		for (int j = 0; 3 > j; j++) // Sets UI Height to 3
		{
			UIBG.Y = j;
			g_Console.writeToBuffer(UIBG, " ", 0x00);
		}
	}
	UI.Y = 1; // Sets Height of UI text
	UI.X = g_Console.getConsoleSize().X / 3 - 8; // Start of UI text
	g_Console.writeToBuffer(UI, "Lives : ", 0x08);
	UI.X = g_Console.getConsoleSize().X / 3;
	std::string display = to_string(Lives);
	g_Console.writeToBuffer(UI, display, 0x08); // Displays the number of lives
	UI.X = g_Console.getConsoleSize().X / 3 + 2;
	g_Console.writeToBuffer(UI, "Weapon : ", 0x08);
	UI.X = UI.X + 9;
	g_Console.writeToBuffer(UI, Weapons[currentWeapon].Name, 0x08); // Display Equipped Weapon
	UI.X = UI.X + Weapons[currentWeapon].Name.length() + 1; // Increases UI.X by text length of weapon 1's name
	g_Console.writeToBuffer(UI, "Ammo : ", 0x08);
	UI.X = UI.X + 7;
	display = to_string(Weapons[currentWeapon].Clip);
	g_Console.writeToBuffer(UI, display, 0x07); // Display Current Clip
	UI.X = UI.X + display.length();
	g_Console.writeToBuffer(UI, "/", 0x08);
	UI.X = UI.X + 1;
	display = to_string(Weapons[currentWeapon].AmmoTotal);
	g_Console.writeToBuffer(UI, display, 0x08); // Total Ammo not in clip
}
void renderCharacter()
{
	// Draw the location of the character
	WORD charColor = 0x05;
	if (g_sChar.m_bActive)
	{
		charColor = 0x0A;
	}
	g_Console.writeToBuffer(g_sChar.m_cLocation, (char)'P', charColor);
}
void renderEnemy1()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy1.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy1.m_cLocation, character, charColor);
}
void renderEnemy2()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy2.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy2.m_cLocation, character, charColor);
}
void renderEnemy3()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy3.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy3.m_cLocation, character, charColor);
}
void renderEnemy4()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy4.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy4.m_cLocation, character, charColor);
}
void renderEnemy5()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy5.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy5.m_cLocation, character, charColor);
}
void renderEnemy6()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy6.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy6.m_cLocation, character, charColor);
}
void renderDoor()
{
	// Draw the location of the character
	WORD charColor = 0x00;
	if (g_door.m_bActive == true)
		charColor = 0x0B;
	g_Console.writeToBuffer(g_door.m_cLocation, (char)'D', charColor);
}
void renderWeapon()
{
	// Draw the location of the character
	WORD charColor = 0x0E;
	g_Console.writeToBuffer(g_weapon.m_cLocation, (char)254, charColor);
}


void renderFramerate()
{
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / g_dDeltaTime << "fps";
	c.X = g_Console.getConsoleSize().X - 9;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());

	// displays the elapsed time
	ss.str("");
	ss << g_dElapsedTime << "secs";
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
	// Writes the buffer to the console, hence you will see what you have written
	g_Console.flushBufferToConsole();
}

void sound()
{
	if (deathsound > 0)
	{
		Beep(deathsound * 150, 15);
		deathsound--;
	}
	if (shootsound > 0)
	{
		Beep(shootsound * 1000, 15);
		shootsound--;
	}
	if (reloadsound > 0)
	{
		Beep((3 - reloadsound) * 450, 15);
		reloadsound--;
	}
	if (shootfailsound > 0)
	{
		Beep(400, 15);
		shootfailsound--;
	}
}

void generate()
{
	int random, point1, point2, point3, point4, point5;
	srand(time(NULL));
	fstream myfile("map.txt");
	for (size_t i = 0; i < 24; i++)
	{
		if (rand() % 3 && i > 7 && i < 17)
		{
			int random1 = rand() % 20 + 15;
			int random2 = rand() % 20 + 15;
			for (size_t i = 0; i < random1; i++)
				myfile.write("`", 1);
			for (size_t i = 0; i < 80 - random1 - random2; i++)
				myfile.write(" ", 1);
			for (size_t i = 0; i < random2; i++)
				myfile.write("`", 1);
		}
		else
			for (size_t i = 0; i < 80; i++)
				myfile.write("`", 1);
		myfile.write("\n", 1);
	}
	random = rand() % 5 + 37;
	for (size_t i = 0; i < 10; i++)
	{
		myfile.seekp(random + 82 * (i + 7));
		myfile.write(" ", 1);
		myfile.write(" ", 1);
	}
	point1 = (rand() % 10 + 5) + ((rand() % 2) + 13) * 82;
	myfile.seekp(point1);
	random = rand() % 10 + 20;
	point2 = point1 + random;
	for (size_t i = 0; i < random; i++)
		myfile.write(" ", 1);
	random = rand() % 4 + 8;
	for (size_t f = 0; f < random; f++)
	{
		myfile.seekp(point1 + (4 - f) * 82);
		if (f > 3)
			for (size_t i = 0; i < random + 5 - f; i++)
				myfile.write(" ", 1);
		else
			for (size_t i = 0; i < random + 5 + f; i++)
				myfile.write(" ", 1);
	}
	random = rand() % 5 + 3;
	if (rand() % 2)
	{
		for (size_t f = 0; f < random; f++)
		{
			myfile.seekp(point2 + f * 82 - f);
			for (size_t i = 0; i < random + 5 + f; i++)
				myfile.write(" ", 1);
		}
	}
	else
	{
		for (size_t f = 0; f < random; f++)
		{
			myfile.seekp(point2 - f * 82 + f);
			for (size_t i = 0; i < random + 8 - f; i++)
				myfile.write(" ", 1);
		}
	}
	point3 = myfile.tellp();
	random = rand() % 3 + 2;
	for (size_t f = 0; f < random; f++)
	{
		myfile.seekp(point3 - (82 * f) + 2 * f);
		for (size_t i = 0; i < (random * 2) - f; i++)
			myfile.write(" ", 1);
	}
	random = rand() % 3 + 2;
	if (rand() % 2)
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point1 - 1 + i * 82);
			myfile.write(" ", 1);
		}
	else
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point1 - 1 - i * 82 + 82);
			myfile.write(" ", 1);
		}
	point4 = myfile.tellp();
	random = rand() % 3;
	if (point4 < myfile.end / 2)
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point4 + 82 * i);
			for (size_t i = 0; i < (random); i++)
				myfile.write(" ", 1);
		}
	else
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point4 - (82 * i));
			for (size_t i = 0; i < (random); i++)
				myfile.write(" ", 1);
		}
	point5 = myfile.tellp();
	random = rand() % 20 + 8;
	for (size_t f = 0; f < random; f++)
	{
		myfile.seekp(point5 + (rand() % 3 + 1) * 82);
		for (size_t i = 0; i < random; i++)
			myfile.write(" ", 1);
	}
	for (size_t i = 0; i < 82 * 24; i++)
	{
		myfile.seekg(i);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == '`' && i > 82 && i < 23 * 82)
		{
			myfile.seekg(i - 82);
			char * buffer = new char[0];
			myfile.read(buffer, 1);
			if (buffer[0] == ' ')
			{
				myfile.seekp(i);
				myfile.write("\228", 1);
			}
			else
			{
				myfile.seekg(i + 82);
				char * buffer = new char[0];
				myfile.read(buffer, 1);
				if (buffer[0] == ' ')
				{
					myfile.seekp(i);
					myfile.write("\228", 1);
				}
				else
				{
					myfile.seekg(i + 1);
					char * buffer = new char[0];
					myfile.read(buffer, 1);
					if (buffer[0] == ' ')
					{
						myfile.seekp(i);
						myfile.write("\228", 1);
					}
					else
					{
						myfile.seekg(i - 1);
						char * buffer = new char[0];
						myfile.read(buffer, 1);
						if (buffer[0] == ' ')
						{
							myfile.seekp(i);
							myfile.write("\228", 1);
						}
					}
				}
			}
		}
	}

	myfile.close();
}

void weapdata()
{
	std::string in;
	ifstream weapondata("weapons.txt");
	for (int i = 0; 4 > i; i++)
	{
		getline(weapondata, Weapons[i].Name); // Gets name of Weapon
		weapondata >> Weapons[i].ClipMax;
		weapondata >> Weapons[i].Reload;
		weapondata >> Weapons[i].Range;
	}
	weapondata.close();
}

void reload()
{
	Weapons[currentWeapon].AmmoTotal += Weapons[currentWeapon].Clip;	// Adds ammo left in clip to total
	Weapons[currentWeapon].AmmoTotal = 6;
	if (Weapons[currentWeapon].ClipMax >= Weapons[currentWeapon].AmmoTotal)	// if cap is higher or equal to remaining
	{
		Weapons[currentWeapon].Clip = Weapons[currentWeapon].AmmoTotal; // Clip is filled to remaining
		Weapons[currentWeapon].AmmoTotal = 0; // Deducted to 0
	}
	else // if more ammo than clip cap
	{
		Weapons[currentWeapon].Clip = Weapons[currentWeapon].ClipMax;
		Weapons[currentWeapon].AmmoTotal = Weapons[currentWeapon].AmmoTotal - Weapons[currentWeapon].ClipMax;
	}
}
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
SGameChar	g_enemy1;
SGameChar	g_enemy2;
SGameChar	g_enemy3;
SGameChar	g_enemy4;
SGameChar	g_enemy5;
SGameChar	g_enemy6;
SGameChar	g_weapon;
SGameChar	g_door;
size_t		deathsound = 0;
size_t		shootsound = 0;
size_t		reloadsound = 0;
int g_shootdist = 0;
int g_shootmaxdist = 10; // Shooting distance of weapon. Can be changed.
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
EWEAPONSTATES g_eWeaponState = Hold;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
int Lives = 3; // Number of lives the player has left (Base Value is 3)
int currentWeapon = 0;
WeaponParameters Weapons[4];
// Console object
Console g_Console(80, 24, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init(void)
{
	generate();
	weapdata();
	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;

	// sets the initial state for the game
	g_eGameState = S_SPLASHSCREEN;
	int enemyX, enemyY;
	fstream myfile("map.txt");
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
			break;
	}
	g_sChar.m_cLocation.X = enemyX;
	g_sChar.m_cLocation.Y = enemyY;
	g_sChar.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy1.m_cLocation.X = enemyX;
	g_enemy1.m_cLocation.Y = enemyY;
	g_enemy1.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy2.m_cLocation.X = enemyX;
	g_enemy2.m_cLocation.Y = enemyY;
	g_enemy2.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy3.m_cLocation.X = enemyX;
	g_enemy3.m_cLocation.Y = enemyY;
	g_enemy3.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy4.m_cLocation.X = enemyX;
	g_enemy4.m_cLocation.Y = enemyY;
	g_enemy4.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy5.m_cLocation.X = enemyX;
	g_enemy5.m_cLocation.Y = enemyY;
	g_enemy5.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy6.m_cLocation.X = enemyX;
	g_enemy6.m_cLocation.Y = enemyY;
	g_enemy6.m_bActive = true;
	g_weapon.m_cLocation.X = 10;
	g_weapon.m_cLocation.Y = 2;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
			break;
	}
	g_door.m_cLocation.X = enemyX;
	g_door.m_cLocation.Y = enemyY;
	g_door.m_bActive = false;
	g_weapon.m_cLocation.X = 10;
	g_weapon.m_cLocation.Y = 2;
	myfile.close();
	// sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(0, 16, L"Consolas");
	reload();
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown(void)
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput(void)
{
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_W] = isKeyPressed(87);
	g_abKeyPressed[K_A] = isKeyPressed(65);
	g_abKeyPressed[K_S] = isKeyPressed(83);
	g_abKeyPressed[K_D] = isKeyPressed(68);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
	// get the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;

	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;
	case S_GAME: gameplay(); // gameplay logic when we are in the game
		break;
	}
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
	clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: renderSplashScreen();
		break;
	case S_GAME: renderGame();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_abKeyPressed[K_SPACE]) // wait for 0.5 seconds to switch to game mode, else do nothing
		g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacter();    // moves the character, collision detection, physics, etc
	sound();			// sound can be played here too.
}

void moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	fstream myfile("map.txt");
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (Weapons[currentWeapon].Clip > 0)
	{
		if (g_abKeyPressed[K_UP] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireUp;
			if (g_abKeyPressed[K_W])
				g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
			else
				g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_DOWN] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireDown;
			if (g_abKeyPressed[K_S])
				g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y + 1;
			else
				g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_LEFT] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireLeft;
			if (g_abKeyPressed[K_A])
				g_weapon.m_cLocation.X = g_sChar.m_cLocation.X - 1;
			else
				g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_RIGHT] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireRight;
			if (g_abKeyPressed[K_D])
				g_weapon.m_cLocation.X = g_sChar.m_cLocation.X + 1;
			else
				g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
	}
	char * buffer2 = new char[0];
	if (g_eWeaponState == FireUp)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.Y--;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireDown)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.Y++;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireLeft)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.X--;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireRight)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.X++;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}


	if (g_shootdist >= g_shootmaxdist)
	{
		g_eWeaponState = Hold;
		g_weapon.m_cLocation.X = 10;
		g_weapon.m_cLocation.Y = 2;
		g_shootdist = 0;
	}

	if (g_abKeyPressed[K_W] && g_sChar.m_cLocation.Y > 0)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 - 82);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_A] && g_sChar.m_cLocation.X > 0)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 - 1);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_S] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 + 82);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_D] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 + 1);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
	}
	if (
		(g_sChar.m_cLocation.X == g_enemy1.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy1.m_cLocation.Y && g_enemy1.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy2.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y && g_enemy2.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y && g_enemy3.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y && g_enemy4.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y && g_enemy5.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y && g_enemy6.m_bActive == false)
		)
	{
		reload();
		reloadsound += 2;
	}
	if (
		(g_sChar.m_cLocation.X == g_enemy1.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy1.m_cLocation.Y && g_enemy1.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy2.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y && g_enemy2.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y && g_enemy3.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y && g_enemy4.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y && g_enemy5.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y && g_enemy6.m_bActive == true)
		)
	{
		g_sChar.m_bActive = false;
		bSomethingHappened = true;
	}
	if (g_sChar.m_cLocation.X == g_enemy1.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy1.m_cLocation.Y)
	{
		g_enemy1.m_bActive = false;
		g_enemy1.m_cLocation.X = 0;
		g_enemy1.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy2.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y)
	{
		g_enemy2.m_bActive = false;
		g_enemy2.m_cLocation.X = 0;
		g_enemy2.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y)
	{
		g_enemy3.m_bActive = false;
		g_enemy3.m_cLocation.X = 0;
		g_enemy3.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y)
	{
		g_enemy4.m_bActive = false;
		g_enemy4.m_cLocation.X = 0;
		g_enemy4.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y)
	{
		g_enemy5.m_bActive = false;
		g_enemy5.m_cLocation.X = 0;
		g_enemy5.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y)
	{
		g_enemy6.m_bActive = false;
		g_enemy6.m_cLocation.X = 0;
		g_enemy6.m_cLocation.Y = 0;
	}

	switch (rand() % 64)
	{
	case 0:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.X++;
		break;
	case 1:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.Y++;
		break;
	case 2:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.X--;
		break;
	case 3:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.Y--;
		break;
	case 4:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.X++;
		break;
	case 5:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.Y++;
		break;
	case 6:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.X--;
		break;
	case 7:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.Y--;
		break;
	case 8:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.X++;
		break;
	case 9:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.Y++;
		break;
	case 10:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.X--;
		break;
	case 11:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.Y--;
		break;
	case 12:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.X++;
		break;
	case 13:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.Y++;
		break;
	case 14:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.X--;
		break;
	case 15:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.Y--;
		break;
	case 16:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.X++;
		break;
	case 17:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.Y++;
		break;
	case 18:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.X--;
		break;
	case 19:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.Y--;
		break;
	case 20:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.X++;
		break;
	case 21:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.Y++;
		break;
	case 22:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.X--;
		break;
	case 23:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.Y--;
		break;
	}

	myfile.close();


	if (g_abKeyPressed[K_SPACE])
	{
		g_sChar.m_bActive = true;
		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.07; // 125ms should be enough
	}
}
void processUserInput()
{
	// quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
		g_bQuitGame = true;
	if (g_sChar.m_bActive == false) // Took damage
	{
		g_sChar.m_bActive = true;
		Lives--;
		deathsound = 5;
	}
	if (g_enemy1.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy1.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy1.m_bActive == true)
	{
		g_enemy1.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy2.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy2.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy2.m_bActive == true)
	{
		g_enemy2.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy3.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy3.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy3.m_bActive == true)
	{
		g_enemy3.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy4.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy4.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy4.m_bActive == true)
	{
		g_enemy4.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy5.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy5.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy5.m_bActive == true)
	{
		g_enemy5.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy6.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy6.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy6.m_bActive == true)
	{
		g_enemy6.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy1.m_bActive == false &&
		g_enemy2.m_bActive == false &&
		g_enemy3.m_bActive == false &&
		g_enemy4.m_bActive == false &&
		g_enemy5.m_bActive == false &&
		g_enemy6.m_bActive == false)
		g_door.m_bActive = true;
	if (g_door.m_bActive == true && g_sChar.m_cLocation.X == g_door.m_cLocation.X && g_sChar.m_cLocation.Y == g_door.m_cLocation.Y)
	{
		init();
		g_eGameState = S_GAME;
	}
}

void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x1F);
}

void renderSplashScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 9;
	g_Console.writeToBuffer(c, "Use <WASD> to move", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "Use Arrow Keys to attack", 0x09);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 11;
	g_Console.writeToBuffer(c, "Press 'Space' to start", 0x0E);
}

void renderGame()
{
	renderMap();        // renders the map to the buffer first
	renderDoor();
	renderWeapon();
	renderCharacter();  // renders the character into the buffer
	renderEnemy1();
	renderEnemy2();
	renderEnemy3();
	renderEnemy4();
	renderEnemy5();
	renderEnemy6();
	renderUI();
}

void renderMap()
{
	// Set up sample colours, and output shadings
	//const WORD colors[] = {
	//    0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	//    0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	//};

	//COORD c;
	for (int i = 0; i < 12; ++i)
	{
		fstream myfile("map.txt");
		string sLine;
		for (short i = 0; i < 24 * 80; i++)
		{
			if (i % 80 == 0)
				//{
				getline(myfile, sLine);
			//for (size_t i = 0; i < 24; i++)
			//	for (size_t j = 0; j < 80; j++)
			//	{
			//						if (sLine[j] == '#')
			//							sLine[j] = 219;
			//					}
			//			}
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, sLine[i % 80], 0x0F);
		}
		//c.X = 0;
		//c.Y = 0;
		//colour(colors[i]);
		//g_Console.writeToBuffer(c, " °±²Û", colors[i]);
	}
}
void renderUI()
{
	COORD UIBG;
	COORD UI;
	for (int i = 0; g_Console.getConsoleSize().X > i; i++) // For every value of x
	{
		UIBG.X = i;
		for (int j = 0; 3 > j; j++) // Sets UI Height to 3
		{
			UIBG.Y = j;
			g_Console.writeToBuffer(UIBG, " ", 0x00);
		}
	}
	UI.Y = 1; // Sets Height of UI text
	UI.X = g_Console.getConsoleSize().X / 3 - 8; // Start of UI text
	g_Console.writeToBuffer(UI, "Lives : ", 0x08);
	UI.X = g_Console.getConsoleSize().X / 3;
	std::string display = to_string(Lives);
	g_Console.writeToBuffer(UI, display, 0x08); // Displays the number of lives
	UI.X = g_Console.getConsoleSize().X / 3 + 2;
	g_Console.writeToBuffer(UI, "Weapon : ", 0x08);
	UI.X = UI.X + 9;
	g_Console.writeToBuffer(UI, Weapons[currentWeapon].Name, 0x08); // Display Equipped Weapon
	UI.X = UI.X + Weapons[currentWeapon].Name.length() + 1; // Increases UI.X by text length of weapon 1's name
	g_Console.writeToBuffer(UI, "Ammo : ", 0x08);
	UI.X = UI.X + 7;
	display = to_string(Weapons[currentWeapon].Clip);
	g_Console.writeToBuffer(UI, display, 0x07); // Display Current Clip
	UI.X = UI.X + display.length();
	g_Console.writeToBuffer(UI, "/", 0x08);
	UI.X = UI.X + 1;
	display = to_string(Weapons[currentWeapon].AmmoTotal);
	g_Console.writeToBuffer(UI, display, 0x08); // Total Ammo not in clip
}
void renderCharacter()
{
	// Draw the location of the character
	WORD charColor = 0x05;
	if (g_sChar.m_bActive)
	{
		charColor = 0x0A;
	}
	g_Console.writeToBuffer(g_sChar.m_cLocation, (char)'P', charColor);
}
void renderEnemy1()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy1.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy1.m_cLocation, character, charColor);
}
void renderEnemy2()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy2.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy2.m_cLocation, character, charColor);
}
void renderEnemy3()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy3.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy3.m_cLocation, character, charColor);
}
void renderEnemy4()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy4.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy4.m_cLocation, character, charColor);
}
void renderEnemy5()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy5.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy5.m_cLocation, character, charColor);
}
void renderEnemy6()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy6.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy6.m_cLocation, character, charColor);
}
void renderDoor()
{
	// Draw the location of the character
	WORD charColor = 0x00;
	if (g_door.m_bActive == true)
		charColor = 0x0B;
	g_Console.writeToBuffer(g_door.m_cLocation, (char)'D', charColor);
}
void renderWeapon()
{
	// Draw the location of the character
	WORD charColor = 0x0E;
	g_Console.writeToBuffer(g_weapon.m_cLocation, (char)254, charColor);
}


void renderFramerate()
{
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / g_dDeltaTime << "fps";
	c.X = g_Console.getConsoleSize().X - 9;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());

	// displays the elapsed time
	ss.str("");
	ss << g_dElapsedTime << "secs";
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
	// Writes the buffer to the console, hence you will see what you have written
	g_Console.flushBufferToConsole();
}

void sound()
{
	if (deathsound > 0)
	{
		Beep(deathsound * 150, 15);
		deathsound--;
	}
	if (shootsound > 0)
	{
		Beep(shootsound * 1000, 15);
		shootsound--;
	}
	if (reloadsound > 0)
	{
		Beep((3 - reloadsound) * 450, 15);
		reloadsound--;
	}
}

void generate()
{
	int random, point1, point2, point3, point4, point5;
	srand(time(NULL));
	fstream myfile("map.txt");
	for (size_t i = 0; i < 24; i++)
	{
		if (rand() % 3 && i > 7 && i < 17)
		{
			int random1 = rand() % 20 + 15;
			int random2 = rand() % 20 + 15;
			for (size_t i = 0; i < random1; i++)
				myfile.write("`", 1);
			for (size_t i = 0; i < 80 - random1 - random2; i++)
				myfile.write(" ", 1);
			for (size_t i = 0; i < random2; i++)
				myfile.write("`", 1);
		}
		else
			for (size_t i = 0; i < 80; i++)
				myfile.write("`", 1);
		myfile.write("\n", 1);
	}
	random = rand() % 5 + 37;
	for (size_t i = 0; i < 10; i++)
	{
		myfile.seekp(random + 82 * (i + 7));
		myfile.write(" ", 1);
		myfile.write(" ", 1);
	}
	point1 = (rand() % 10 + 5) + ((rand() % 2) + 13) * 82;
	myfile.seekp(point1);
	random = rand() % 10 + 20;
	point2 = point1 + random;
	for (size_t i = 0; i < random; i++)
		myfile.write(" ", 1);
	random = rand() % 4 + 8;
	for (size_t f = 0; f < random; f++)
	{
		myfile.seekp(point1 + (4 - f) * 82);
		if (f > 3)
			for (size_t i = 0; i < random + 5 - f; i++)
				myfile.write(" ", 1);
		else
			for (size_t i = 0; i < random + 5 + f; i++)
				myfile.write(" ", 1);
	}
	random = rand() % 5 + 3;
	if (rand() % 2)
	{
		for (size_t f = 0; f < random; f++)
		{
			myfile.seekp(point2 + f * 82 - f);
			for (size_t i = 0; i < random + 5 + f; i++)
				myfile.write(" ", 1);
		}
	}
	else
	{
		for (size_t f = 0; f < random; f++)
		{
			myfile.seekp(point2 - f * 82 + f);
			for (size_t i = 0; i < random + 8 - f; i++)
				myfile.write(" ", 1);
		}
	}
	point3 = myfile.tellp();
	random = rand() % 3 + 2;
	for (size_t f = 0; f < random; f++)
	{
		myfile.seekp(point3 - (82 * f) + 2 * f);
		for (size_t i = 0; i < (random * 2) - f; i++)
			myfile.write(" ", 1);
	}
	random = rand() % 3 + 2;
	if (rand() % 2)
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point1 - 1 + i * 82);
			myfile.write(" ", 1);
		}
	else
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point1 - 1 - i * 82 + 82);
			myfile.write(" ", 1);
		}
	point4 = myfile.tellp();
	random = rand() % 3;
	if (point4 < myfile.end / 2)
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point4 + 82 * i);
			for (size_t i = 0; i < (random); i++)
				myfile.write(" ", 1);
		}
	else
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point4 - (82 * i));
			for (size_t i = 0; i < (random); i++)
				myfile.write(" ", 1);
		}
	point5 = myfile.tellp();
	random = rand() % 20 + 8;
	for (size_t f = 0; f < random; f++)
	{
		myfile.seekp(point5 + (rand() % 4 + 1) * 82);
		for (size_t i = 0; i < random; i++)
			myfile.write(" ", 1);
	}
	for (size_t i = 0; i < 82 * 24; i++)
	{
		myfile.seekg(i);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == '`' && i > 82 && i < 23 * 82)
		{
			myfile.seekg(i - 82);
			char * buffer = new char[0];
			myfile.read(buffer, 1);
			if (buffer[0] == ' ')
			{
				myfile.seekp(i);
				myfile.write("\228", 1);
			}
			else
			{
				myfile.seekg(i + 82);
				char * buffer = new char[0];
				myfile.read(buffer, 1);
				if (buffer[0] == ' ')
				{
					myfile.seekp(i);
					myfile.write("\228", 1);
				}
				else
				{
					myfile.seekg(i + 1);
					char * buffer = new char[0];
					myfile.read(buffer, 1);
					if (buffer[0] == ' ')
					{
						myfile.seekp(i);
						myfile.write("\228", 1);
					}
					else
					{
						myfile.seekg(i - 1);
						char * buffer = new char[0];
						myfile.read(buffer, 1);
						if (buffer[0] == ' ')
						{
							myfile.seekp(i);
							myfile.write("\228", 1);
						}
					}
				}
			}
		}
	}

	myfile.close();
}

void weapdata()
{
	std::string in;
	ifstream weapondata("weapons.txt");
	for (int i = 0; 4 > i; i++)
	{
		getline(weapondata, Weapons[i].Name); // Gets name of Weapon
		weapondata >> Weapons[i].ClipMax;
		weapondata >> Weapons[i].Reload;
		weapondata >> Weapons[i].Range;
	}
	weapondata.close();
}

void reload()
{
	Weapons[currentWeapon].AmmoTotal += Weapons[currentWeapon].Clip;	// Adds ammo left in clip to total
	Weapons[currentWeapon].AmmoTotal = 6;
	if (Weapons[currentWeapon].ClipMax >= Weapons[currentWeapon].AmmoTotal)	// if cap is higher or equal to remaining
	{
		Weapons[currentWeapon].Clip = Weapons[currentWeapon].AmmoTotal; // Clip is filled to remaining
		Weapons[currentWeapon].AmmoTotal = 0; // Deducted to 0
	}
	else // if more ammo than clip cap
	{
		Weapons[currentWeapon].Clip = Weapons[currentWeapon].ClipMax;
		Weapons[currentWeapon].AmmoTotal = Weapons[currentWeapon].AmmoTotal - Weapons[currentWeapon].ClipMax;
	}
}
#include <string>
using namespace std;// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
SGameChar	g_enemy1;
SGameChar	g_enemy2;
SGameChar	g_enemy3;
SGameChar	g_enemy4;
SGameChar	g_enemy5;
SGameChar	g_enemy6;
SGameChar	g_weapon;
SGameChar	g_door;
size_t		deathsound = 0;
size_t		shootsound = 0;
size_t		reloadsound = 0;
int g_shootdist = 0;
int g_shootmaxdist = 10; // Shooting distance of weapon. Can be changed.
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
EWEAPONSTATES g_eWeaponState = Hold;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
int Lives = 3; // Number of lives the player has left (Base Value is 3)
int currentWeapon = 0;
WeaponParameters Weapons[4];
// Console object
Console g_Console(80, 25, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init(void)
{
	generate();
	weapdata();
	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;

	// sets the initial state for the game
	g_eGameState = S_SPLASHSCREEN;
	int enemyX, enemyY;
	fstream myfile("map.txt");
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
			break;
	}
	g_sChar.m_cLocation.X = enemyX;
	g_sChar.m_cLocation.Y = enemyY;
	g_sChar.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy1.m_cLocation.X = enemyX;
	g_enemy1.m_cLocation.Y = enemyY;
	g_enemy1.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy2.m_cLocation.X = enemyX;
	g_enemy2.m_cLocation.Y = enemyY;
	g_enemy2.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy3.m_cLocation.X = enemyX;
	g_enemy3.m_cLocation.Y = enemyY;
	g_enemy3.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy4.m_cLocation.X = enemyX;
	g_enemy4.m_cLocation.Y = enemyY;
	g_enemy4.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy5.m_cLocation.X = enemyX;
	g_enemy5.m_cLocation.Y = enemyY;
	g_enemy5.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy6.m_cLocation.X = enemyX;
	g_enemy6.m_cLocation.Y = enemyY;
	g_enemy6.m_bActive = true;
	g_weapon.m_cLocation.X = 10;
	g_weapon.m_cLocation.Y = 2;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
			break;
	}
	g_door.m_cLocation.X = enemyX;
	g_door.m_cLocation.Y = enemyY;
	g_door.m_bActive = false;
	g_weapon.m_cLocation.X = 10;
	g_weapon.m_cLocation.Y = 2;
	myfile.close();
	// sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(0, 16, L"Consolas");
	reload();
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown(void)
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput(void)
{
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_W] = isKeyPressed(87);
	g_abKeyPressed[K_A] = isKeyPressed(65);
	g_abKeyPressed[K_S] = isKeyPressed(83);
	g_abKeyPressed[K_D] = isKeyPressed(68);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
	// get the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;

	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;
	case S_GAME: gameplay(); // gameplay logic when we are in the game
		break;
	}
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
	clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: renderSplashScreen();
		break;
	case S_GAME: renderGame();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_abKeyPressed[K_SPACE]) // wait for 0.5 seconds to switch to game mode, else do nothing
		g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacter();    // moves the character, collision detection, physics, etc
	sound();			// sound can be played here too.
}

void moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	fstream myfile("map.txt");
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (Weapons[currentWeapon].Clip > 0)
	{
		if (g_abKeyPressed[K_UP] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireUp;
			if (g_abKeyPressed[K_W])
				g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
			else
				g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_DOWN] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireDown;
			if (g_abKeyPressed[K_S])
				g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y + 1;
			else
				g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_LEFT] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireLeft;
			if (g_abKeyPressed[K_A])
				g_weapon.m_cLocation.X = g_sChar.m_cLocation.X - 1;
			else
				g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_RIGHT] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireRight;
			if (g_abKeyPressed[K_D])
				g_weapon.m_cLocation.X = g_sChar.m_cLocation.X + 1;
			else
				g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
	}
	char * buffer2 = new char[0];
	if (g_eWeaponState == FireUp)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.Y--;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireDown)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.Y++;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireLeft)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.X--;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireRight)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.X++;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}


	if (g_shootdist >= g_shootmaxdist)
	{
		g_eWeaponState = Hold;
		g_weapon.m_cLocation.X = 10;
		g_weapon.m_cLocation.Y = 2;
		g_shootdist = 0;
	}

	if (g_abKeyPressed[K_W] && g_sChar.m_cLocation.Y > 0)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 - 82);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_A] && g_sChar.m_cLocation.X > 0)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 - 1);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_S] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 + 82);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_D] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 + 1);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
	}
	if (
		(g_sChar.m_cLocation.X == g_enemy1.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy1.m_cLocation.Y && g_enemy1.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy2.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y && g_enemy2.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y && g_enemy3.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y && g_enemy4.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y && g_enemy5.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y && g_enemy6.m_bActive == false)
		)
	{
		reload();
		reloadsound += 2;
	}
	if (
		(g_sChar.m_cLocation.X == g_enemy1.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy1.m_cLocation.Y && g_enemy1.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy2.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y && g_enemy2.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y && g_enemy3.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y && g_enemy4.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y && g_enemy5.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y && g_enemy6.m_bActive == true)
		)
	{
		g_sChar.m_bActive = false;
		bSomethingHappened = true;
	}
	if (g_sChar.m_cLocation.X == g_enemy1.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy1.m_cLocation.Y)
	{
		g_enemy1.m_bActive = false;
		g_enemy1.m_cLocation.X = 0;
		g_enemy1.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy2.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y)
	{
		g_enemy2.m_bActive = false;
		g_enemy2.m_cLocation.X = 0;
		g_enemy2.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y)
	{
		g_enemy3.m_bActive = false;
		g_enemy3.m_cLocation.X = 0;
		g_enemy3.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y)
	{
		g_enemy4.m_bActive = false;
		g_enemy4.m_cLocation.X = 0;
		g_enemy4.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y)
	{
		g_enemy5.m_bActive = false;
		g_enemy5.m_cLocation.X = 0;
		g_enemy5.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y)
	{
		g_enemy6.m_bActive = false;
		g_enemy6.m_cLocation.X = 0;
		g_enemy6.m_cLocation.Y = 0;
	}

	switch (rand() % 64)
	{
	case 0:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.X++;
		break;
	case 1:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.Y++;
		break;
	case 2:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.X--;
		break;
	case 3:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.Y--;
		break;
	case 4:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.X++;
		break;
	case 5:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.Y++;
		break;
	case 6:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.X--;
		break;
	case 7:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.Y--;
		break;
	case 8:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.X++;
		break;
	case 9:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.Y++;
		break;
	case 10:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.X--;
		break;
	case 11:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.Y--;
		break;
	case 12:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.X++;
		break;
	case 13:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.Y++;
		break;
	case 14:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.X--;
		break;
	case 15:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.Y--;
		break;
	case 16:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.X++;
		break;
	case 17:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.Y++;
		break;
	case 18:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.X--;
		break;
	case 19:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.Y--;
		break;
	case 20:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.X++;
		break;
	case 21:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.Y++;
		break;
	case 22:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.X--;
		break;
	case 23:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.Y--;
		break;
	}

	myfile.close();


	if (g_abKeyPressed[K_SPACE])
	{
		g_sChar.m_bActive = true;
		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.07; // 125ms should be enough
	}
}
void processUserInput()
{
	// quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
		g_bQuitGame = true;
	if (g_sChar.m_bActive == false) // Took damage
	{
		g_sChar.m_bActive = true;
		Lives--;
		deathsound = 5;
	}
	if (g_enemy1.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy1.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy1.m_bActive == true)
	{
		g_enemy1.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy2.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy2.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy2.m_bActive == true)
	{
		g_enemy2.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy3.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy3.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy3.m_bActive == true)
	{
		g_enemy3.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy4.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy4.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy4.m_bActive == true)
	{
		g_enemy4.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy5.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy5.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy5.m_bActive == true)
	{
		g_enemy5.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy6.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy6.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy6.m_bActive == true)
	{
		g_enemy6.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy1.m_bActive == false &&
		g_enemy2.m_bActive == false &&
		g_enemy3.m_bActive == false &&
		g_enemy4.m_bActive == false &&
		g_enemy5.m_bActive == false &&
		g_enemy6.m_bActive == false)
		g_door.m_bActive = true;
	if (g_door.m_bActive == true && g_sChar.m_cLocation.X == g_door.m_cLocation.X && g_sChar.m_cLocation.Y == g_door.m_cLocation.Y)
	{
		init();
		g_eGameState = S_GAME;
	}
}

void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x1F);
}

void renderSplashScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 9;
	g_Console.writeToBuffer(c, "Use <WASD> to move", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "Use Arrow Keys to attack", 0x09);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 11;
	g_Console.writeToBuffer(c, "Press 'Space' to start", 0x0E);
}

void renderGame()
{
	renderMap();        // renders the map to the buffer first
	renderDoor();
	renderWeapon();
	renderCharacter();  // renders the character into the buffer
	renderEnemy1();
	renderEnemy2();
	renderEnemy3();
	renderEnemy4();
	renderEnemy5();
	renderEnemy6();
	renderUI();
}

void renderMap()
{
	// Set up sample colours, and output shadings
	//const WORD colors[] = {
	//    0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	//    0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	//};

	//COORD c;
	for (int i = 0; i < 12; ++i)
	{
		fstream myfile("map.txt");
		string sLine;
		for (short i = 0; i < 24 * 80; i++)
		{
			if (i % 80 == 0)
				//{
				getline(myfile, sLine);
			//for (size_t i = 0; i < 24; i++)
			//	for (size_t j = 0; j < 80; j++)
			//	{
			//						if (sLine[j] == '#')
			//							sLine[j] = 219;
			//					}
			//			}
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, sLine[i % 80], 0x0F);
		}
		//c.X = 0;
		//c.Y = 0;
		//colour(colors[i]);
		//g_Console.writeToBuffer(c, " °±²Û", colors[i]);
	}
}
void renderUI()
{
	COORD UIBG;
	COORD UI;
	for (int i = 0; g_Console.getConsoleSize().X > i; i++) // For every value of x
	{
		UIBG.X = i;
		for (int j = 0; 3 > j; j++) // Sets UI Height to 3
		{
			UIBG.Y = j;
			g_Console.writeToBuffer(UIBG, " ", 0x00);
		}
	}
	UI.Y = 1; // Sets Height of UI text
	UI.X = g_Console.getConsoleSize().X / 3 - 8; // Start of UI text
	g_Console.writeToBuffer(UI, "Lives : ", 0x08);
	UI.X = g_Console.getConsoleSize().X / 3;
	std::string display = to_string(Lives);
	g_Console.writeToBuffer(UI, display, 0x08); // Displays the number of lives
	UI.X = g_Console.getConsoleSize().X / 3 + 2;
	g_Console.writeToBuffer(UI, "Weapon : ", 0x08);
	UI.X = UI.X + 9;
	g_Console.writeToBuffer(UI, Weapons[currentWeapon].Name, 0x08); // Display Equipped Weapon
	UI.X = UI.X + Weapons[currentWeapon].Name.length() + 1; // Increases UI.X by text length of weapon 1's name
	g_Console.writeToBuffer(UI, "Ammo : ", 0x08);
	UI.X = UI.X + 7;
	display = to_string(Weapons[currentWeapon].Clip);
	g_Console.writeToBuffer(UI, display, 0x07); // Display Current Clip
	UI.X = UI.X + display.length();
	g_Console.writeToBuffer(UI, "/", 0x08);
	UI.X = UI.X + 1;
	display = to_string(Weapons[currentWeapon].AmmoTotal);
	g_Console.writeToBuffer(UI, display, 0x08); // Total Ammo not in clip
}
void renderCharacter()
{
	// Draw the location of the character
	WORD charColor = 0x05;
	if (g_sChar.m_bActive)
	{
		charColor = 0x0A;
	}
	g_Console.writeToBuffer(g_sChar.m_cLocation, (char)'P', charColor);
}
void renderEnemy1()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy1.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy1.m_cLocation, character, charColor);
}
void renderEnemy2()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy2.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy2.m_cLocation, character, charColor);
}
void renderEnemy3()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy3.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy3.m_cLocation, character, charColor);
}
void renderEnemy4()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy4.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy4.m_cLocation, character, charColor);
}
void renderEnemy5()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy5.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy5.m_cLocation, character, charColor);
}
void renderEnemy6()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy6.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy6.m_cLocation, character, charColor);
}
void renderDoor()
{
	// Draw the location of the character
	WORD charColor = 0x00;
	if (g_door.m_bActive == true)
		charColor = 0x0B;
	g_Console.writeToBuffer(g_door.m_cLocation, (char)'D', charColor);
}
void renderWeapon()
{
	// Draw the location of the character
	WORD charColor = 0x0E;
	g_Console.writeToBuffer(g_weapon.m_cLocation, (char)254, charColor);
}


void renderFramerate()
{
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / g_dDeltaTime << "fps";
	c.X = g_Console.getConsoleSize().X - 9;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());

	// displays the elapsed time
	ss.str("");
	ss << g_dElapsedTime << "secs";
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
	// Writes the buffer to the console, hence you will see what you have written
	g_Console.flushBufferToConsole();
}

void sound()
{
	if (deathsound > 0)
	{
		Beep(deathsound * 150, 15);
		deathsound--;
	}
	if (shootsound > 0)
	{
		Beep(shootsound * 1000, 15);
		shootsound--;
	}
	if (reloadsound > 0)
	{
		Beep((3 - reloadsound) * 450, 15);
		reloadsound--;
	}
}

void generate()
{
	int random, point1, point2, point3, point4, point5;
	srand(time(NULL));
	fstream myfile("map.txt");
	for (size_t i = 0; i < 24; i++)
	{
		if (rand() % 3 && i > 7 && i < 17)
		{
			int random1 = rand() % 20 + 15;
			int random2 = rand() % 20 + 15;
			for (size_t i = 0; i < random1; i++)
				myfile.write("`", 1);
			for (size_t i = 0; i < 80 - random1 - random2; i++)
				myfile.write(" ", 1);
			for (size_t i = 0; i < random2; i++)
				myfile.write("`", 1);
		}
		else
			for (size_t i = 0; i < 80; i++)
				myfile.write("`", 1);
		myfile.write("\n", 1);
	}
	random = rand() % 5 + 37;
	for (size_t i = 0; i < 10; i++)
	{
		myfile.seekp(random + 82 * (i + 7));
		myfile.write(" ", 1);
		myfile.write(" ", 1);
	}
	point1 = (rand() % 10 + 5) + ((rand() % 2) + 13) * 82;
	myfile.seekp(point1);
	random = rand() % 10 + 20;
	point2 = point1 + random;
	for (size_t i = 0; i < random; i++)
		myfile.write(" ", 1);
	random = rand() % 4 + 8;
	for (size_t f = 0; f < random; f++)
	{
		myfile.seekp(point1 + (4 - f) * 82);
		if (f > 3)
			for (size_t i = 0; i < random + 5 - f; i++)
				myfile.write(" ", 1);
		else
			for (size_t i = 0; i < random + 5 + f; i++)
				myfile.write(" ", 1);
	}
	random = rand() % 5 + 3;
	if (rand() % 2)
	{
		for (size_t f = 0; f < random; f++)
		{
			myfile.seekp(point2 + f * 82 - f);
			for (size_t i = 0; i < random + 5 + f; i++)
				myfile.write(" ", 1);
		}
	}
	else
	{
		for (size_t f = 0; f < random; f++)
		{
			myfile.seekp(point2 - f * 82 + f);
			for (size_t i = 0; i < random + 8 - f; i++)
				myfile.write(" ", 1);
		}
	}
	point3 = myfile.tellp();
	random = rand() % 3 + 2;
	for (size_t f = 0; f < random; f++)
	{
		myfile.seekp(point3 - (82 * f) + 2 * f);
		for (size_t i = 0; i < (random * 2) - f; i++)
			myfile.write(" ", 1);
	}
	random = rand() % 3 + 2;
	if (rand() % 2)
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point1 - 1 + i * 82);
			myfile.write(" ", 1);
		}
	else
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point1 - 1 - i * 82 + 82);
			myfile.write(" ", 1);
		}
	point4 = myfile.tellp();
	random = rand() % 3;
	if (point4 < myfile.end / 2)
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point4 + 82 * i);
			for (size_t i = 0; i < (random); i++)
				myfile.write(" ", 1);
		}
	else
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point4 - (82 * i));
			for (size_t i = 0; i < (random); i++)
				myfile.write(" ", 1);
		}
	point5 = myfile.tellp();
	random = rand() % 20 + 8;
	for (size_t f = 0; f < random; f++)
	{
		myfile.seekp(point5 + (rand() % 4 + 1) * 82);
		for (size_t i = 0; i < random; i++)
			myfile.write(" ", 1);
	}
	for (size_t i = 0; i < 82 * 24; i++)
	{
		myfile.seekg(i);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == '`' && i > 82 && i < 23 * 82)
		{
			myfile.seekg(i - 82);
			char * buffer = new char[0];
			myfile.read(buffer, 1);
			if (buffer[0] == ' ')
			{
				myfile.seekp(i);
				myfile.write("\228", 1);
			}
			else
			{
				myfile.seekg(i + 82);
				char * buffer = new char[0];
				myfile.read(buffer, 1);
				if (buffer[0] == ' ')
				{
					myfile.seekp(i);
					myfile.write("\228", 1);
				}
				else
				{
					myfile.seekg(i + 1);
					char * buffer = new char[0];
					myfile.read(buffer, 1);
					if (buffer[0] == ' ')
					{
						myfile.seekp(i);
						myfile.write("\228", 1);
					}
					else
					{
						myfile.seekg(i - 1);
						char * buffer = new char[0];
						myfile.read(buffer, 1);
						if (buffer[0] == ' ')
						{
							myfile.seekp(i);
							myfile.write("\228", 1);
						}
					}
				}
			}
		}
	}

	myfile.close();
}

void weapdata()
{
	std::string in;
	ifstream weapondata("weapons.txt");
	for (int i = 0; 4 > i; i++)
	{
		getline(weapondata, Weapons[i].Name); // Gets name of Weapon
		weapondata >> Weapons[i].ClipMax;
		weapondata >> Weapons[i].Reload;
		weapondata >> Weapons[i].Range;
	}
	weapondata.close();
}

void reload()
{
	Weapons[currentWeapon].AmmoTotal += Weapons[currentWeapon].Clip;	// Adds ammo left in clip to total
	Weapons[currentWeapon].AmmoTotal = 6;
	if (Weapons[currentWeapon].ClipMax >= Weapons[currentWeapon].AmmoTotal)	// if cap is higher or equal to remaining
	{
		Weapons[currentWeapon].Clip = Weapons[currentWeapon].AmmoTotal; // Clip is filled to remaining
		Weapons[currentWeapon].AmmoTotal = 0; // Deducted to 0
	}
	else // if more ammo than clip cap
	{
		Weapons[currentWeapon].Clip = Weapons[currentWeapon].ClipMax;
		Weapons[currentWeapon].AmmoTotal = Weapons[currentWeapon].AmmoTotal - Weapons[currentWeapon].ClipMax;
	}
}

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
SGameChar	g_enemy1;
SGameChar	g_enemy2;
SGameChar	g_enemy3;
SGameChar	g_enemy4;
SGameChar	g_enemy5;
SGameChar	g_enemy6;
SGameChar	g_weapon;
SGameChar	g_door;
size_t		deathsound = 0;
size_t		shootsound = 0;
int g_shootdist = 0;
int g_shootmaxdist = 10; // Shooting distance of weapon. Can be changed.
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
EWEAPONSTATES g_eWeaponState = Hold;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
int Lives = 3; // Number of lives the player has left (Base Value is 3)
int currentWeapon = 0;
WeaponParameters Weapons[4];
// Console object
Console g_Console(80, 25, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init(void)
{
	generate();
	weapdata();
	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;

	// sets the initial state for the game
	g_eGameState = S_SPLASHSCREEN;
	int enemyX, enemyY;
	fstream myfile("map.txt");
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
			break;
	}
	g_sChar.m_cLocation.X = enemyX;
	g_sChar.m_cLocation.Y = enemyY;
	g_sChar.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy1.m_cLocation.X = enemyX;
	g_enemy1.m_cLocation.Y = enemyY;
	g_enemy1.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy2.m_cLocation.X = enemyX;
	g_enemy2.m_cLocation.Y = enemyY;
	g_enemy2.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy3.m_cLocation.X = enemyX;
	g_enemy3.m_cLocation.Y = enemyY;
	g_enemy3.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy4.m_cLocation.X = enemyX;
	g_enemy4.m_cLocation.Y = enemyY;
	g_enemy4.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy5.m_cLocation.X = enemyX;
	g_enemy5.m_cLocation.Y = enemyY;
	g_enemy5.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy6.m_cLocation.X = enemyX;
	g_enemy6.m_cLocation.Y = enemyY;
	g_enemy6.m_bActive = true;
	g_weapon.m_cLocation.X = 10;
	g_weapon.m_cLocation.Y = 2;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		char * buffer = new char[0];
		myfile.seekg(enemyX + enemyY * 82);
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
			break;
	}
	g_door.m_cLocation.X = enemyX;
	g_door.m_cLocation.Y = enemyY;
	g_door.m_bActive = false;
	g_weapon.m_cLocation.X = 10;
	g_weapon.m_cLocation.Y = 2;
	myfile.close();
	// sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(0, 16, L"Consolas");
	reload();
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown(void)
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput(void)
{
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_W] = isKeyPressed(87);
	g_abKeyPressed[K_A] = isKeyPressed(65);
	g_abKeyPressed[K_S] = isKeyPressed(83);
	g_abKeyPressed[K_D] = isKeyPressed(68);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
	// get the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;

	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;
	case S_GAME: gameplay(); // gameplay logic when we are in the game
		break;
	}
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
	clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: renderSplashScreen();
		break;
	case S_GAME: renderGame();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_abKeyPressed[K_SPACE]) // wait for 0.5 seconds to switch to game mode, else do nothing
		g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacter();    // moves the character, collision detection, physics, etc
	sound();			// sound can be played here too.
}

void moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	fstream myfile("map.txt");
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (Weapons[currentWeapon].Clip > 0)
	{
		if (g_abKeyPressed[K_UP] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireUp;
			g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_DOWN] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireDown;
			g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_LEFT] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireLeft;
			g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
		if (g_abKeyPressed[K_RIGHT] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireRight;
			g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			shootsound++;
			Weapons[currentWeapon].Clip--;
			bSomethingHappened = true;
		}
	}
	char * buffer2 = new char[0];
	if (g_eWeaponState == FireUp)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.Y--;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireDown)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.Y++;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireLeft)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.X--;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireRight)
	{
		myfile.seekg(g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ')
		{
			g_weapon.m_cLocation.X++;
			bSomethingHappened = true;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}


	if (g_shootdist >= g_shootmaxdist)
	{
		g_eWeaponState = Hold;
		g_weapon.m_cLocation.X = 10;
		g_weapon.m_cLocation.Y = 2;
		g_shootdist = 0;
	}

	if (g_abKeyPressed[K_W] && g_sChar.m_cLocation.Y > 0)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 - 82);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_A] && g_sChar.m_cLocation.X > 0)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 - 1);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_S] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 + 82);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_D] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		myfile.seekg(g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 82 + 1);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == ' ')
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
	}
	if (
		(g_sChar.m_cLocation.X == g_enemy1.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy1.m_cLocation.Y && g_enemy1.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy2.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y && g_enemy2.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y && g_enemy3.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y && g_enemy4.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y && g_enemy5.m_bActive == false) ||
		(g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y && g_enemy6.m_bActive == false)
		)
	{
		reload();
	}
	if (
		(g_sChar.m_cLocation.X == g_enemy1.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy1.m_cLocation.Y && g_enemy1.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy2.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y && g_enemy2.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y && g_enemy3.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y && g_enemy4.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y && g_enemy5.m_bActive == true) ||
		(g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y && g_enemy6.m_bActive == true)
		)
	{
		g_sChar.m_bActive = false;
		bSomethingHappened = true;
	}
	if (g_sChar.m_cLocation.X == g_enemy1.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy1.m_cLocation.Y)
	{
		g_enemy1.m_bActive = false;
		g_enemy1.m_cLocation.X = 0;
		g_enemy1.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy2.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y)
	{
		g_enemy2.m_bActive = false;
		g_enemy2.m_cLocation.X = 0;
		g_enemy2.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y)
	{
		g_enemy3.m_bActive = false;
		g_enemy3.m_cLocation.X = 0;
		g_enemy3.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y)
	{
		g_enemy4.m_bActive = false;
		g_enemy4.m_cLocation.X = 0;
		g_enemy4.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y)
	{
		g_enemy5.m_bActive = false;
		g_enemy5.m_cLocation.X = 0;
		g_enemy5.m_cLocation.Y = 0;
	}
	if (g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y)
	{
		g_enemy6.m_bActive = false;
		g_enemy6.m_cLocation.X = 0;
		g_enemy6.m_cLocation.Y = 0;
	}

	switch (rand() % 64)
	{
	case 0:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.X++;
		break;
	case 1:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.Y++;
		break;
	case 2:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.X--;
		break;
	case 3:
		myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy1.m_bActive == true)
			g_enemy1.m_cLocation.Y--;
		break;
	case 4:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.X++;
		break;
	case 5:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.Y++;
		break;
	case 6:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.X--;
		break;
	case 7:
		myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy2.m_bActive == true)
			g_enemy2.m_cLocation.Y--;
		break;
	case 8:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.X++;
		break;
	case 9:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.Y++;
		break;
	case 10:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.X--;
		break;
	case 11:
		myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy3.m_bActive == true)
			g_enemy3.m_cLocation.Y--;
		break;
	case 12:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.X++;
		break;
	case 13:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.Y++;
		break;
	case 14:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.X--;
		break;
	case 15:
		myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy4.m_bActive == true)
			g_enemy4.m_cLocation.Y--;
		break;
	case 16:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.X++;
		break;
	case 17:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.Y++;
		break;
	case 18:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.X--;
		break;
	case 19:
		myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy5.m_bActive == true)
			g_enemy5.m_cLocation.Y--;
		break;
	case 20:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 + 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.X++;
		break;
	case 21:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 + 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.Y++;
		break;
	case 22:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 - 1);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.X--;
		break;
	case 23:
		myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 - 82);
		myfile.read(buffer2, 1);
		if (buffer2[0] == ' ' && g_enemy6.m_bActive == true)
			g_enemy6.m_cLocation.Y--;
		break;
	}

	myfile.close();


	if (g_abKeyPressed[K_SPACE])
	{
		g_sChar.m_bActive = true;
		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.07; // 125ms should be enough
	}
}
void processUserInput()
{
	// quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
		g_bQuitGame = true;
	if (g_sChar.m_bActive == false) // Took damage
	{
		g_sChar.m_bActive = true;
		Lives--;
		deathsound = 5;
	}
	if (g_enemy1.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy1.m_cLocation.Y == g_weapon.m_cLocation.Y)
	{
		g_enemy1.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy2.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy2.m_cLocation.Y == g_weapon.m_cLocation.Y)
	{
		g_enemy2.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy3.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy3.m_cLocation.Y == g_weapon.m_cLocation.Y)
	{
		g_enemy3.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy4.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy4.m_cLocation.Y == g_weapon.m_cLocation.Y)
	{
		g_enemy4.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy5.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy5.m_cLocation.Y == g_weapon.m_cLocation.Y)
	{
		g_enemy5.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy6.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy6.m_cLocation.Y == g_weapon.m_cLocation.Y)
	{
		g_enemy6.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy1.m_bActive == false &&
		g_enemy2.m_bActive == false &&
		g_enemy3.m_bActive == false &&
		g_enemy4.m_bActive == false &&
		g_enemy5.m_bActive == false &&
		g_enemy6.m_bActive == false)
		g_door.m_bActive = true;
	if (g_door.m_bActive == true && g_sChar.m_cLocation.X == g_door.m_cLocation.X && g_sChar.m_cLocation.Y == g_door.m_cLocation.Y)
		init();
}

void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x1F);
}

void renderSplashScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 9;
	g_Console.writeToBuffer(c, "Use <WASD> to move", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "Use Arrow Keys to attack", 0x09);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 11;
	g_Console.writeToBuffer(c, "Press 'Space' to start", 0x0E);
}

void renderGame()
{
	renderMap();        // renders the map to the buffer first
	renderDoor();
	renderWeapon();
	renderCharacter();  // renders the character into the buffer
	renderEnemy1();
	renderEnemy2();
	renderEnemy3();
	renderEnemy4();
	renderEnemy5();
	renderEnemy6();
	renderUI();
}

void renderMap()
{
	// Set up sample colours, and output shadings
	//const WORD colors[] = {
	//    0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	//    0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	//};

	//COORD c;
	for (int i = 0; i < 12; ++i)
	{
		fstream myfile("map.txt");
		string sLine;
		for (short i = 0; i < 24 * 80; i++)
		{
			if (i % 80 == 0)
				//{
				getline(myfile, sLine);
			//for (size_t i = 0; i < 24; i++)
			//	for (size_t j = 0; j < 80; j++)
			//	{
			//						if (sLine[j] == '#')
			//							sLine[j] = 219;
			//					}
			//			}
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, sLine[i % 80], 0x0F);
		}
		//c.X = 0;
		//c.Y = 0;
		//colour(colors[i]);
		//g_Console.writeToBuffer(c, " °±²Û", colors[i]);
	}
}
void renderUI()
{
	COORD UIBG;
	COORD UI;
	for (int i = 0; g_Console.getConsoleSize().X > i; i++) // For every value of x
	{
		UIBG.X = i;
		for (int j = 0; 3 > j; j++) // Sets UI Height to 3
		{
			UIBG.Y = j;
			g_Console.writeToBuffer(UIBG, " ", 0x00);
		}
	}
	UI.Y = 1; // Sets Height of UI text
	UI.X = g_Console.getConsoleSize().X / 3 - 8; // Start of UI text
	g_Console.writeToBuffer(UI, "Lives : ", 0x08);
	UI.X = g_Console.getConsoleSize().X / 3;
	std::string display = to_string(Lives);
	g_Console.writeToBuffer(UI, display, 0x08); // Displays the number of lives
	UI.X = g_Console.getConsoleSize().X / 3 + 2;
	g_Console.writeToBuffer(UI, "Weapon : ", 0x08);
	UI.X = UI.X + 9;
	g_Console.writeToBuffer(UI, Weapons[currentWeapon].Name, 0x08); // Display Equipped Weapon
	UI.X = UI.X + Weapons[currentWeapon].Name.length() + 1; // Increases UI.X by text length of weapon 1's name
	g_Console.writeToBuffer(UI, "Ammo : ", 0x08);
	UI.X = UI.X + 7;
	display = to_string(Weapons[currentWeapon].Clip);
	g_Console.writeToBuffer(UI, display, 0x07); // Display Current Clip
	UI.X = UI.X + display.length();
	g_Console.writeToBuffer(UI, "/", 0x08);
	UI.X = UI.X + 1;
	display = to_string(Weapons[currentWeapon].AmmoTotal);
	g_Console.writeToBuffer(UI, display, 0x08); // Total Ammo not in clip
}
void renderCharacter()
{
	// Draw the location of the character
	WORD charColor = 0x05;
	if (g_sChar.m_bActive)
	{
		charColor = 0x0A;
	}
	g_Console.writeToBuffer(g_sChar.m_cLocation, (char)'P', charColor);
}
void renderEnemy1()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy1.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy1.m_cLocation, character, charColor);
}
void renderEnemy2()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy2.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy2.m_cLocation, character, charColor);
}
void renderEnemy3()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy3.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy3.m_cLocation, character, charColor);
}
void renderEnemy4()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy4.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy4.m_cLocation, character, charColor);
}
void renderEnemy5()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy5.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy5.m_cLocation, character, charColor);
}
void renderEnemy6()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	char character = 'E';
	if (g_enemy6.m_bActive == false)
	{
		character = 'R';
		charColor = 0x0E;
	}
	g_Console.writeToBuffer(g_enemy6.m_cLocation, character, charColor);
}
void renderDoor()
{
	// Draw the location of the character
	WORD charColor = 0x00;
	if (g_door.m_bActive == true)
		charColor = 0x0B;
	g_Console.writeToBuffer(g_door.m_cLocation, (char)'D', charColor);
}
void renderWeapon()
{
	// Draw the location of the character
	WORD charColor = 0x0E;
	g_Console.writeToBuffer(g_weapon.m_cLocation, (char)254, charColor);
}


void renderFramerate()
{
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / g_dDeltaTime << "fps";
	c.X = g_Console.getConsoleSize().X - 9;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());

	// displays the elapsed time
	ss.str("");
	ss << g_dElapsedTime << "secs";
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
	// Writes the buffer to the console, hence you will see what you have written
	g_Console.flushBufferToConsole();
}

void sound()
{
	if (deathsound > 0)
	{
		Beep(deathsound * 150, 15);
		deathsound--;
	}
	if (shootsound > 0)
	{
		Beep(shootsound * 1000, 15);
		shootsound--;
	}
}

void generate()
{
	int random, point1, point2, point3, point4, point5;
	srand(time(NULL));
	fstream myfile("map.txt");
	for (size_t i = 0; i < 24; i++)
	{
		if (rand() % 3 && i > 7 && i < 17)
		{
			int random1 = rand() % 20 + 15;
			int random2 = rand() % 20 + 15;
			for (size_t i = 0; i < random1; i++)
				myfile.write("`", 1);
			for (size_t i = 0; i < 80 - random1 - random2; i++)
				myfile.write(" ", 1);
			for (size_t i = 0; i < random2; i++)
				myfile.write("`", 1);
		}
		else
			for (size_t i = 0; i < 80; i++)
				myfile.write("`", 1);
		myfile.write("\n", 1);
	}
	random = rand() % 5 + 37;
	for (size_t i = 0; i < 10; i++)
	{
		myfile.seekp(random + 82 * (i + 7));
		myfile.write(" ", 1);
		myfile.write(" ", 1);
	}
	point1 = (rand() % 10 + 5) + ((rand() % 2) + 13) * 82;
	myfile.seekp(point1);
	random = rand() % 10 + 20;
	point2 = point1 + random;
	for (size_t i = 0; i < random; i++)
		myfile.write(" ", 1);
	random = rand() % 4 + 8;
	for (size_t f = 0; f < random; f++)
	{
		myfile.seekp(point1 + (4 - f) * 82);
		if (f > 3)
			for (size_t i = 0; i < random + 5 - f; i++)
				myfile.write(" ", 1);
		else
			for (size_t i = 0; i < random + 5 + f; i++)
				myfile.write(" ", 1);
	}
	random = rand() % 5 + 3;
	if (rand() % 2)
	{
		for (size_t f = 0; f < random; f++)
		{
			myfile.seekp(point2 + f * 82 - f);
			for (size_t i = 0; i < random + 5 + f; i++)
				myfile.write(" ", 1);
		}
	}
	else
	{
		for (size_t f = 0; f < random; f++)
		{
			myfile.seekp(point2 - f * 82 + f);
			for (size_t i = 0; i < random + 8 - f; i++)
				myfile.write(" ", 1);
		}
	}
	point3 = myfile.tellp();
	random = rand() % 3 + 2;
	for (size_t f = 0; f < random; f++)
	{
		myfile.seekp(point3 - (82 * f) + 2 * f);
		for (size_t i = 0; i < (random * 2) - f; i++)
			myfile.write(" ", 1);
	}
	random = rand() % 3 + 2;
	if (rand() % 2)
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point1 - 1 + i * 82);
			myfile.write(" ", 1);
		}
	else
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point1 - 1 - i * 82 + 82);
			myfile.write(" ", 1);
		}
	point4 = myfile.tellp();
	random = rand() % 3;
	if (point4 < myfile.end / 2)
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point4 + 82 * i);
			for (size_t i = 0; i < (random); i++)
				myfile.write(" ", 1);
		}
	else
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point4 - (82 * i));
			for (size_t i = 0; i < (random); i++)
				myfile.write(" ", 1);
		}
	point5 = myfile.tellp();
	random = rand() % 20 + 8;
	for (size_t f = 0; f < random; f++)
	{
		myfile.seekp(point5 + (rand() % 4 + 1) * 82);
		for (size_t i = 0; i < random; i++)
			myfile.write(" ", 1);
	}
	for (size_t i = 0; i < 82 * 24; i++)
	{
		myfile.seekg(i);
		char * buffer = new char[0];
		myfile.read(buffer, 1);
		if (buffer[0] == '`' && i > 82 && i < 23 * 82)
		{
			myfile.seekg(i - 82);
			char * buffer = new char[0];
			myfile.read(buffer, 1);
			if (buffer[0] == ' ')
			{
				myfile.seekp(i);
				myfile.write("\228", 1);
			}
			else
			{
				myfile.seekg(i + 82);
				char * buffer = new char[0];
				myfile.read(buffer, 1);
				if (buffer[0] == ' ')
				{
					myfile.seekp(i);
					myfile.write("\228", 1);
				}
				else
				{
					myfile.seekg(i + 1);
					char * buffer = new char[0];
					myfile.read(buffer, 1);
					if (buffer[0] == ' ')
					{
						myfile.seekp(i);
						myfile.write("\228", 1);
					}
					else
					{
						myfile.seekg(i - 1);
						char * buffer = new char[0];
						myfile.read(buffer, 1);
						if (buffer[0] == ' ')
						{
							myfile.seekp(i);
							myfile.write("\228", 1);
						}
					}
				}
			}
		}
	}

	myfile.close();
}

void weapdata()
{
	std::string in;
	ifstream weapondata("weapons.txt");
	for (int i = 0; 4 > i; i++)
	{
		getline(weapondata, Weapons[i].Name); // Gets name of Weapon
		weapondata >> Weapons[i].ClipMax;
		weapondata >> Weapons[i].Reload;
		weapondata >> Weapons[i].Range;
	}
	weapondata.close();
}

void reload()
{
	Weapons[currentWeapon].AmmoTotal += Weapons[currentWeapon].Clip;	// Adds ammo left in clip to total
	Weapons[currentWeapon].AmmoTotal = 6;
	if (Weapons[currentWeapon].ClipMax >= Weapons[currentWeapon].AmmoTotal)	// if cap is higher or equal to remaining
	{
		Weapons[currentWeapon].Clip = Weapons[currentWeapon].AmmoTotal; // Clip is filled to remaining
		Weapons[currentWeapon].AmmoTotal = 0; // Deducted to 0
	}
	else // if more ammo than clip cap
	{
		Weapons[currentWeapon].Clip = Weapons[currentWeapon].ClipMax;
		Weapons[currentWeapon].AmmoTotal = Weapons[currentWeapon].AmmoTotal - Weapons[currentWeapon].ClipMax;
	}
}
