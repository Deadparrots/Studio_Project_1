// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"

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
SGameChar	g_boss;
SGameChar	g_door;
size_t		deathsound = 0;
size_t		shootsound = 0;
size_t		reloadsound = 0;
size_t		shootfailsound = 0;
int			MMSelect = MMStart;
double		stages = 0.000; // set to 0 normally... 9 for boss testing
int			int_stages = stages;
size_t		StageType = EMainMenu;
bool		b_play = false;
int g_shootdist = 0;
int g_shootmaxdist = 10; // Shooting distance of weapon. Can be changed.
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
EWEAPONSTATES g_eWeaponState = Hold;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
int Lives = 3; // Number of lives the player has left (Base Value is 3)
int currentWeapon = 0;
WeaponParameters Weapons[4];
// Console object
Console g_Console(80, 24, "Monster Dungeon");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void boss_init()
{
	b_play = false;
	weapdata();
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;
	g_Console.setConsoleFont(0, 16, L"Consolas");
	reload();
	g_sChar.m_cLocation.X = 40;
	g_sChar.m_cLocation.Y = 21;
	g_sChar.m_bActive = true;
	g_boss.m_cLocation.X = 40;
	g_boss.m_cLocation.Y = 10;
	g_boss.m_bActive = true;
	int enemyX, enemyY;
	std::fstream myfile("map/bossmap.txt");
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
	g_enemy1.m_cLocation.X = enemyX;
	g_enemy1.m_cLocation.Y = enemyY;
	g_enemy1.m_bActive = false;
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
	g_enemy2.m_cLocation.X = enemyX;
	g_enemy2.m_cLocation.Y = enemyY;
	g_enemy2.m_bActive = false;
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
	g_enemy3.m_cLocation.X = enemyX;
	g_enemy3.m_cLocation.Y = enemyY;
	g_enemy3.m_bActive = false;
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
	g_enemy4.m_cLocation.X = enemyX;
	g_enemy4.m_cLocation.Y = enemyY;
	g_enemy4.m_bActive = false;
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
	g_enemy5.m_cLocation.X = enemyX;
	g_enemy5.m_cLocation.Y = enemyY;
	g_enemy5.m_bActive = false;
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
	g_enemy6.m_cLocation.X = enemyX;
	g_enemy6.m_cLocation.Y = enemyY;
	g_enemy6.m_bActive = false;
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
	myfile.close();
}
void init(void)
{
	generate();
	weapdata();
	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;

	// sets the initial state for the game
	g_eGameState = S_SPLASHSCREEN;
	g_boss.m_bActive = false;
	int enemyX, enemyY;
	std::fstream myfile("map/map.txt");
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
	g_abKeyPressed[K_C] = isKeyPressed(67);
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

void splashScreenWait() 
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	if ((MMSelect == MMStart || MMSelect == MMInstructions) && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]))
	{
		MMSelect++;
		bSomethingHappened = true;
	}
	else if ((MMSelect == MMExit || MMSelect == MMInstructions) && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]))
	{
		MMSelect--;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMStart && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]))
	{
		MMSelect = MMExit;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMExit && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]))
	{
		MMSelect = MMStart;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMExit)
		g_bQuitGame = true;
	if(!b_play)
		ost();
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMStart) 
	{
		StageType = EStage;
		b_play = false;
		g_eGameState = S_GAME;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void gameplay()            // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	if (StageType == EStage)
		moveCharacter();// moves the character, collision detection, physics, etc
	else if (StageType == EBoss)
		boss_moveCharacter();
	sound(); // sound can be played here too.
	if (!b_play)
		ost();
}

void boss_moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	std::fstream myfile("map/bossmap.txt");
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if ((g_abKeyPressed[K_UP] || g_abKeyPressed[K_DOWN] || g_abKeyPressed[K_LEFT] || g_abKeyPressed[K_RIGHT]) && (g_eWeaponState != Hold || Weapons[currentWeapon].Clip == 0))
	{
		shootfailsound = 1;
		//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
	if (g_sChar.m_cLocation.X == g_boss.m_cLocation.X && g_sChar.m_cLocation.Y == g_boss.m_cLocation.Y && g_boss.m_bActive == true)
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
	if (g_weapon.m_cLocation.Y == g_boss.m_cLocation.Y && g_boss.m_bActive == true)
	{
		switch (rand() % 2)
		{
		case 0:
			myfile.seekg(g_boss.m_cLocation.X + g_boss.m_cLocation.Y * 82 + 82);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_boss.m_cLocation.Y++;
			else
				g_boss.m_cLocation.Y--;
			break;
		case 1:
			myfile.seekg(g_boss.m_cLocation.X + g_boss.m_cLocation.Y * 82 - 82);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_boss.m_cLocation.Y--;
			else
				g_boss.m_cLocation.Y++;
			break;
		}
	}
	if (g_weapon.m_cLocation.X == g_boss.m_cLocation.X && g_boss.m_bActive == true)
	{
		switch (rand() % 2)
		{
		case 0:
			myfile.seekg(g_boss.m_cLocation.X + g_boss.m_cLocation.Y * 82 + 1);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_boss.m_cLocation.X++;
			else
				g_boss.m_cLocation.X--;
			break;
		case 1:
			myfile.seekg(g_boss.m_cLocation.X + g_boss.m_cLocation.Y * 82 - 1);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_boss.m_cLocation.X--;
			else
				g_boss.m_cLocation.X++;
			break;
		}
	}

	myfile.close();
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.07; // 125ms should be enough
	}
}
void moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	std::fstream myfile("map/map.txt");
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if ((g_abKeyPressed[K_UP] || g_abKeyPressed[K_DOWN] || g_abKeyPressed[K_LEFT] || g_abKeyPressed[K_RIGHT]) && (g_eWeaponState != Hold || Weapons[currentWeapon].Clip == 0))
	{
		shootfailsound = 1;
		//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
			//bSomethingHappened = true;
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
	size_t rate = 100 / (stages + 1) + 24;
	switch (rand() % rate)
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
	}	if (g_sChar.m_cLocation.Y == g_enemy1.m_cLocation.Y && g_enemy1.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 10)
		{
		case 0:
			myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 + 82);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy1.m_cLocation.Y++;
			else if (buffer2[0] == ' ')
				g_enemy1.m_cLocation.X--;

			break;
		case 1:
			myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 - 82);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy1.m_cLocation.Y--;
			else if (buffer2[0] == ' ')
				g_enemy1.m_cLocation.Y++;
			break;
		}
	}
	else if (g_sChar.m_cLocation.X == g_enemy1.m_cLocation.X && g_enemy1.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 10)
		{
		case 0:
			myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 + 1);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy1.m_cLocation.X++;
			else if (buffer2[0] == ' ')
				g_enemy1.m_cLocation.Y--;
			break;
		case 1:
			myfile.seekg(g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 82 - 1);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy1.m_cLocation.X--;
			else if (buffer2[0] == ' ')
				g_enemy1.m_cLocation.Y--;
			break;
		}
	}
	if (g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y && g_enemy2.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 10)
		{
		case 0:
			myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 + 82);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy2.m_cLocation.Y++;
			else if (buffer2[0] == ' ')
				g_enemy2.m_cLocation.X--;

			break;
		case 1:
			myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 - 82);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy2.m_cLocation.Y--;
			else if (buffer2[0] == ' ')
				g_enemy2.m_cLocation.Y++;
			break;
		}
	}
	else if (g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_enemy6.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 10)
		{
		case 0:
			myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 + 1);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy2.m_cLocation.X++;
			else if (buffer2[0] == ' ')
				g_enemy2.m_cLocation.Y--;
			break;
		case 1:
			myfile.seekg(g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 82 - 1);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy2.m_cLocation.X--;
			else if (buffer2[0] == ' ')
				g_enemy2.m_cLocation.Y--;
			break;
		}
	}
	if (g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y && g_enemy3.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 10)
		{
		case 0:
			myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 + 82);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy3.m_cLocation.Y++;
			else if (buffer2[0] == ' ')
				g_enemy3.m_cLocation.X--;

			break;
		case 1:
			myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 - 82);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy3.m_cLocation.Y--;
			else if (buffer2[0] == ' ')
				g_enemy3.m_cLocation.Y++;
			break;
		}
	}
	else if (g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_enemy3.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 10)
		{
		case 0:
			myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 + 1);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy3.m_cLocation.X++;
			else if (buffer2[0] == ' ')
				g_enemy3.m_cLocation.Y--;
			break;
		case 1:
			myfile.seekg(g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 82 - 1);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy3.m_cLocation.X--;
			else if (buffer2[0] == ' ')
				g_enemy3.m_cLocation.Y--;
			break;
		}
	}
	if (g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y && g_enemy4.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 10)
		{
		case 0:
			myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 + 82);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy4.m_cLocation.Y++;
			else if (buffer2[0] == ' ')
				g_enemy4.m_cLocation.X--;

			break;
		case 1:
			myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 - 82);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy4.m_cLocation.Y--;
			else if (buffer2[0] == ' ')
				g_enemy4.m_cLocation.Y++;
			break;
		}
	}
	else if (g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_enemy4.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 10)
		{
		case 0:
			myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 + 1);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy4.m_cLocation.X++;
			else if (buffer2[0] == ' ')
				g_enemy4.m_cLocation.Y--;
			break;
		case 1:
			myfile.seekg(g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 82 - 1);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy4.m_cLocation.X--;
			else if (buffer2[0] == ' ')
				g_enemy4.m_cLocation.Y--;
			break;
		}
	}
	if (g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y && g_enemy5.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 10)
		{
		case 0:
			myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 + 82);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy5.m_cLocation.Y++;
			else if (buffer2[0] == ' ')
				g_enemy5.m_cLocation.X--;

			break;
		case 1:
			myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 - 82);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy5.m_cLocation.Y--;
			else if (buffer2[0] == ' ')
				g_enemy5.m_cLocation.Y++;
			break;
		}
	}
	else if (g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_enemy5.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 10)
		{
		case 0:
			myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 + 1);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy5.m_cLocation.X++;
			else if (buffer2[0] == ' ')
				g_enemy5.m_cLocation.Y--;
			break;
		case 1:
			myfile.seekg(g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 82 - 1);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy5.m_cLocation.X--;
			else if (buffer2[0] == ' ')
				g_enemy5.m_cLocation.Y--;
			break;
		}
	}
	if (g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y && g_enemy6.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 10)
		{
		case 0:
			myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 + 82);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy6.m_cLocation.Y++;
			else if (buffer2[0] == ' ')
				g_enemy6.m_cLocation.X--;

			break;
		case 1:
			myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 - 82);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy6.m_cLocation.Y--;
			else if (buffer2[0] == ' ')
				g_enemy6.m_cLocation.Y++;
			break;
		}
	}
	else if (g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_enemy6.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 10)
		{
		case 0:
			myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 + 1);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy6.m_cLocation.X++;
			else if (buffer2[0] == ' ')
				g_enemy6.m_cLocation.Y--;
			break;
		case 1:
			myfile.seekg(g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 82 - 1);
			myfile.read(buffer2, 1);
			if (buffer2[0] == ' ')
				g_enemy6.m_cLocation.X--;
			else if (buffer2[0] == ' ')
				g_enemy6.m_cLocation.Y--;
			break;
		}
	}
	myfile.close();

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.07; // 125ms should be enough
	}
}
void processUserInput()
{
	if (Lives < 0 || g_abKeyPressed[K_ESCAPE])
		g_bQuitGame = true;
	if (g_abKeyPressed[K_C])
		g_boss.m_bActive = false;
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
		g_enemy6.m_bActive == false &&
		g_boss.m_bActive == false)
		g_door.m_bActive = true;
	if (g_door.m_bActive == true && g_sChar.m_cLocation.X == g_door.m_cLocation.X && g_sChar.m_cLocation.Y == g_door.m_cLocation.Y)
	{
		stages++;
		int_stages = stages;
		if (int_stages == 10)
			StageType = EBoss;
		else
		{
			if (StageType == EBoss)
				b_play = false;
			StageType = EStage;
		}
		if (StageType == EBoss)
			boss_init();
		else
			init();
		g_eGameState = S_GAME;
		if (Lives != 9)
			Lives++;
	}
}

void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x00);
}

void renderSplashScreen()  // renders the splash screen
{
	for (int i = 0; i < 12; ++i)
	{
		std::fstream myfile("map/title.txt");
		std::string sLine;
		for (short i = 0; i < 24 * 80; i++)
		{
			if (i % 80 == 0)
				std::getline(myfile, sLine);
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, sLine[i % 80], 0x0F);
		}
		myfile.close();
	}

	COORD m = g_Console.getConsoleSize();
	switch (MMSelect)
	{
	case MMStart:
		m.Y = 20;
		m.X = m.X / 2 - 2;
		g_Console.writeToBuffer(m, "Start", 0x0E);
		m.Y += 1;
		m.X = g_Console.getConsoleSize().X / 2 - 6;
		g_Console.writeToBuffer(m, "Instructions", 0x03);
		m.Y += 1;
		m.X = g_Console.getConsoleSize().X / 2 - 2;
		g_Console.writeToBuffer(m, "Exit", 0x03);
		break;

	case MMInstructions:
		m.Y = 20;
		m.X = m.X / 2 - 2;
		g_Console.writeToBuffer(m, "Start", 0x03);
		m.Y += 1;
		m.X = g_Console.getConsoleSize().X / 2 - 6;
		g_Console.writeToBuffer(m, "Instructions", 0x0E);
		m.Y += 1;
		m.X = g_Console.getConsoleSize().X / 2 - 2;
		g_Console.writeToBuffer(m, "Exit", 0x03);
		break;

	case MMExit:
		m.Y = 20;
		m.X = m.X / 2 - 2;
		g_Console.writeToBuffer(m, "Start", 0x03);
		m.Y += 1;
		m.X = g_Console.getConsoleSize().X / 2 - 6;
		g_Console.writeToBuffer(m, "Instructions", 0x03);
		m.Y += 1;
		m.X = g_Console.getConsoleSize().X / 2 - 2;
		g_Console.writeToBuffer(m, "Exit", 0x0E);
		break;
	}
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
	if (StageType == EBoss)
		renderBoss();
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
	if (StageType == EStage)
		for (int i = 0; i < 12; ++i)
		{
			std::fstream myfile("map/map.txt");
			std::string sLine;
			for (short i = 0; i < 24 * 80; i++)
			{
				if (i % 80 == 0)
					std::getline(myfile, sLine);
				g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, sLine[i % 80], 0x0F);
			}
			myfile.close();
		}
	else
		for (int i = 0; i < 12; ++i)
		{
			std::fstream myfile("map/bossmap.txt");
			std::string sLine;
			for (short i = 0; i < 24 * 80; i++)
			{
				if (i % 80 == 0)
					std::getline(myfile, sLine);
				g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, sLine[i % 80], 0x0F);
			}
			myfile.close();
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
			g_Console.writeToBuffer(UIBG, " ", 0x90);
		}
	}
	UI.Y = 1; // Sets Height of UI text
	UI.X = g_Console.getConsoleSize().X / 3 - 13; // Start of UI text
	g_Console.writeToBuffer(UI, "Lives : ", 0x9f);
	UI.X = g_Console.getConsoleSize().X / 4 + 1;
	std::string display = std::to_string(Lives);
	g_Console.writeToBuffer(UI, display, 0x9f); // Displays the number of lives
	UI.X = g_Console.getConsoleSize().X / 3 + 2;
	g_Console.writeToBuffer(UI, "Weapon : ", 0x9f);
	UI.X = UI.X + 9;
	g_Console.writeToBuffer(UI, Weapons[currentWeapon].Name, 0x9f); // Display Equipped Weapon
	UI.X = UI.X + Weapons[currentWeapon].Name.length() + 3; // Increases UI.X by text length of weapon 1's name
	g_Console.writeToBuffer(UI, "Ammo : ", 0x9f);
	UI.X = UI.X + 7;
	display = std::to_string(Weapons[currentWeapon].Clip);
	g_Console.writeToBuffer(UI, display, 0x9f); // Display Current Clip
	UI.X = UI.X + display.length();
	g_Console.writeToBuffer(UI, "/", 0x9f);
	UI.X = UI.X + 1;
	display = std::to_string(Weapons[currentWeapon].AmmoTotal);
	g_Console.writeToBuffer(UI, display, 0x9f); // Total Ammo not in clip
}
void renderCharacter()
{
	// Draw the location of the character
	WORD charColor = 0x05;
	if (g_sChar.m_bActive)
	{
		charColor = 0x0A;
	}
	g_Console.writeToBuffer(g_sChar.m_cLocation, (char)3, charColor);
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
void renderBoss()
{
	// Draw the location of the boss
	WORD charColor = 0x0C;
	char character = '@';
	if (g_boss.m_bActive == false)
	{
		character = 'R';
		charColor = 0x00;
	}
	g_Console.writeToBuffer(g_boss.m_cLocation, character, charColor);
}
void renderDoor()
{
	// Draw the location of the door
	WORD charColor = 0x00;
	if (g_door.m_bActive == true)
		charColor = 0x0B;
	g_Console.writeToBuffer(g_door.m_cLocation, (char)'D', charColor);
}
void renderWeapon()
{
	// Draw the location of the weapon
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
	g_Console.writeToBuffer(c, ss.str(), 0x0f);
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
	std::fstream myfile("map/map.txt");
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
	std::ifstream weapondata("weapons.txt");
	for (int i = 0; 4 > i; i++)
	{
		std::getline(weapondata, Weapons[i].Name); // Gets name of Weapon
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
void ost()
{
	if (StageType == EMainMenu)
		PlaySound(TEXT("sound/menu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // play sound while in stage
	else if (StageType == EStage)
		PlaySound(TEXT("sound/cave.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // change 'cave' to whatever
	else if (StageType == EBoss)
		PlaySound(TEXT("sound/boss.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // play sound while in stage
	b_play = true;
}
