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
#include <ctime>
#include <string>
using namespace std;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(80, 25, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
	generate();
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
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
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
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
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
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
    if (g_dElapsedTime > 0.5) // wait for 0.5 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void moveCharacter()
{
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
    if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_SPACE])
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
        bSomethingHappened = true;
    }

    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
    }
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
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
    g_Console.writeToBuffer(c, "A game in 0.5 seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
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
				getline(myfile, sLine);
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, sLine[i % 80], 0x0F);
		}
        //c.X = 0;
        //c.Y = 0;
        //colour(colors[i]);
        //g_Console.writeToBuffer(c, " °±²Û", colors[i]);
    }
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
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

void generate()
{
	int random, point1, point2, point3, point4, point5;
	srand(time(NULL));
	fstream myfile("map.txt");
	for (size_t i = 0; i < 24; i++)
	{
		if (rand() % 2 && i > 7 && i < 17)
		{
			int random1 = rand() % 20 + 15;
			int random2 = rand() % 20 + 15;
			for (size_t i = 0; i < random1; i++)
				myfile.write("#", 1);
			for (size_t i = 0; i < 80 - random1 - random2; i++)
				myfile.write(" ", 1);
			for (size_t i = 0; i < random2; i++)
				myfile.write("#", 1);
		}
		else
			for (size_t i = 0; i < 80; i++)
				myfile.write("#", 1);
		myfile.write("\n", 1);
	}
	random = rand() % 5 + 37;
	for (size_t i = 0; i < 10; i++)
	{
		myfile.seekp(random + 82 * (i + 7));
		myfile.write(" ", 1);
		myfile.write(" ", 1);
	}
	point1 = (rand() % 10 + 2) + ((rand() % 8) + 8) * 82;
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
	if (point3 < myfile.end / 2)
		for (size_t f = 0; f < random; f++)
		{
			myfile.seekp(point3 + 82 * f + 2 * f);
			for (size_t i = 0; i < (random * 2) + f; i++)
				myfile.write(" ", 1);
		}
	else
		for (size_t f = 0; f < random; f++)
		{
			myfile.seekp(point3 - (82 * f) + 2 * f);
			for (size_t i = 0; i < (random * 2) - f; i++)
				myfile.write(" ", 1);
		}
	random = rand() % 3 + 3;
	if (point1 < myfile.end / 2)
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point1 - 1 + i * 82);
			if (rand() % 2)
			{
				myfile.write(" ", 1);
				myfile.write(" ", 1);
			}
			else
				myfile.write(" ", 1);
		}
	else
		for (size_t i = 0; i < random; i++)
		{
			myfile.seekp(point1 - 1 - i * 82);
			myfile.write(" ", 1);
		}
	point4 = myfile.tellp();
	random = rand() % 3 + 1;
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

	myfile.close();
}
