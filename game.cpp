// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar; // Player Character
SGameChar	g_enemy1;
SGameChar	g_enemy2;
SGameChar	g_enemy3;
SGameChar	g_enemy4;
SGameChar	g_enemy5;
SGameChar	g_enemy6;
SGameChar	g_weapon;
SBossGaster	g_gaster1;
SBossGaster	g_gaster2;
SBossGaster	g_gaster3;
SBossGaster	g_gaster4;
SGameChar	g_door;
size_t		deathsound = 0;
size_t		shootsound = 0;
size_t		reloadsound = 0;
size_t		shootfailsound = 0;
int			MMSelect = MMStart;
double		stages = 9.000; // set to 0 normally... 9 for boss testing
int			int_stages = stages;
size_t		SongType = EMainMenu;
bool		b_play = false;
bool		bossSpeech = false;
int g_shootdist = 0;
int g_shootmaxdist = 10; // Shooting distance of weapon. Can be changed.
EGAMESTATES g_eGameState = S_INTRO;
EWEAPONSTATES g_eWeaponState = Hold;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
int Lives = 3; // Number of lives the player has left (Base Value is 3)
int currentWeapon = 0; // Current Weapon
WeaponParameters Weapons[4]; // Number of Weapons
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
	g_sChar.m_cLocation.Y = 11;
	g_sChar.m_bActive = true;
	g_door.m_cLocation.X = 40;
	g_door.m_cLocation.Y = 5;
	g_door.m_bActive = true;
	g_enemy1.m_cLocation.X = 0;
	g_enemy1.m_cLocation.Y = 0;
	g_enemy2.m_cLocation.X = 0;
	g_enemy2.m_cLocation.Y = 0;
	g_enemy3.m_cLocation.X = 0;
	g_enemy3.m_cLocation.Y = 0;
	g_enemy4.m_cLocation.X = 0;
	g_enemy4.m_cLocation.Y = 0;
	g_enemy5.m_cLocation.X = 0;
	g_enemy5.m_cLocation.Y = 0;
	g_enemy6.m_cLocation.X = 0;
	g_enemy6.m_cLocation.Y = 0;
}
void boss_battle_init()
{
	g_sChar.m_cLocation.X = 40;
	g_sChar.m_cLocation.Y = 20;
	weapdata();
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;
	g_Console.setConsoleFont(0, 16, L"Consolas");
	reload();
	g_door.m_cLocation.X = 40;
	g_door.m_cLocation.Y = 14;
	g_door.m_bActive = false;
}
void init(void)
{
	generate();
	weapdata();
	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;

	// sets the initial state for the game
	g_eGameState = S_TITLE;
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
	g_gaster1.m_bActive = false;
	g_gaster2.m_bActive = false;
	g_gaster3.m_bActive = false;
	g_gaster4.m_bActive = false;
	g_gaster1.m_bFire = false;
	g_gaster2.m_bFire = false;
	g_gaster3.m_bFire = false;
	g_gaster4.m_bFire = false;
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
	g_abKeyPressed[K_E] = isKeyPressed(69); // For Weapon Switching
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
	case S_INTRO: intro();
	case S_TITLE: splashScreenWait(); // game logic for the splash screen
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
	case S_INTRO: renderIntro();
		break;
	case S_TITLE: renderSplashScreen();
		break;
	case S_GAME: renderGame();
		break;
	case S_GAMEOVER: gameOver();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}
void intro()
{
	if ((g_dElapsedTime > 35) || g_abKeyPressed[K_W] || g_abKeyPressed[K_A] || g_abKeyPressed[K_S] || g_abKeyPressed[K_D] || g_abKeyPressed[K_UP] || g_abKeyPressed[K_LEFT] || g_abKeyPressed[K_DOWN] || g_abKeyPressed[K_RIGHT])
	{
		g_eGameState = S_TITLE;
		SongType = EMainMenu;
		init();
	}
}
void splashScreenWait() 
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	if ((MMSelect == MMStart || MMSelect == MMInstructions) && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_TITLE)
	{
		MMSelect++;
		bSomethingHappened = true;
	}
	else if ((MMSelect == MMExit || MMSelect == MMInstructions) && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_TITLE)
	{
		MMSelect--;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMStart && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMExit;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMExit && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMStart;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMExit && g_eGameState == S_TITLE)
	{
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		g_bQuitGame = true;
	}
	if(!b_play)
		ost();
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMStart && g_eGameState == S_TITLE)
	{
		SongType = EStage;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
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
	if (SongType == EStage)
		moveCharacter();// moves the character, collision detection, physics, etc
	else if (SongType == EBoss)
		boss_moveCharacter();
	else if (SongType == EBossBattle)
		bossbattle_moveCharacter();
	sound(); // sound can be played here too.
	if (!b_play)
		ost();
}
void bossbattle_moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;


	// Boss stuff go here
	if ((g_dElapsedTime > 2 && g_dElapsedTime <= 5) || 
		(g_dElapsedTime > 6 && g_dElapsedTime <= 9) || 
		(g_dElapsedTime > 10 && g_dElapsedTime <= 14) ||
		(g_dElapsedTime > 15 && g_dElapsedTime <= 18) ||
		(g_dElapsedTime > 19 && g_dElapsedTime <= 21))
		bossSpeech = true;
	else
		bossSpeech = false;
	if (g_dElapsedTime > 21 && g_dElapsedTime <= 21.5) // ATTACK 1
	{
		g_gaster1.m_bActive = true;
		g_gaster1.m_bFire = false;
		g_gaster1.m_cLocation.X = (g_dElapsedTime - 21) * g_sChar.m_cLocation.X * 2 + 1;
		g_gaster1.m_cLocation.Y = 10;
		g_gaster2.m_bActive = true;
		g_gaster2.m_bFire = false;
		g_gaster2.m_cLocation.Y = (g_dElapsedTime - 21) * g_sChar.m_cLocation.Y * 2 + 1;
		g_gaster2.m_cLocation.X = 5;
	}
	else if (g_dElapsedTime > 21.5 && g_dElapsedTime <= 22)
	{
		g_gaster1.m_cLocation.X = g_sChar.m_cLocation.X;
		g_gaster2.m_cLocation.Y = g_sChar.m_cLocation.Y;
	}
	else if (g_dElapsedTime > 22 && g_dElapsedTime <= 22.5)
	{
		g_gaster1.m_cLocation.Y = 11;
		g_gaster2.m_cLocation.X = 6;
	}
	else if (g_dElapsedTime > 22.5 && g_dElapsedTime <= 23.5)
	{
		g_gaster1.m_cLocation.Y = 10 - 10 * (g_dElapsedTime - 22.5);
		g_gaster1.m_bFire = true;
		g_gaster2.m_cLocation.X = 5 - 10 * (g_dElapsedTime - 22.5);
		g_gaster2.m_bFire = true;
	}
	else if (g_dElapsedTime > 25 && g_dElapsedTime <= 26) // ATTACK 2
	{
		g_gaster1.m_cLocation.X = 20;
		g_gaster4.m_cLocation.X = 60;
		g_gaster1.m_bActive = true;
		g_gaster4.m_bActive = true;
		g_gaster1.m_cLocation.Y = 10 * (g_dElapsedTime - 25);
		g_gaster4.m_cLocation.Y = 10 * (g_dElapsedTime - 25);
	}
	else if (g_dElapsedTime > 26 && g_dElapsedTime <= 28)
	{
		g_gaster1.m_cLocation.X = 20 + 9 * (g_dElapsedTime - 26);
		g_gaster4.m_cLocation.X = 61 - 9 * (g_dElapsedTime - 26);
		g_gaster1.m_bFire = true;
		g_gaster4.m_bFire = true;
	}
	else if (g_dElapsedTime > 28 && g_dElapsedTime <= 29)
	{
		g_gaster1.m_cLocation.Y = 10 - 10 * (g_dElapsedTime - 28);
		g_gaster1.m_bFire = true;
		g_gaster4.m_cLocation.Y = 10 - 10 * (g_dElapsedTime - 28);
		g_gaster4.m_bFire = true;
	}
	else if (g_dElapsedTime > 30 && g_dElapsedTime <= 31) // ATTACK 3
	{
		g_gaster2.m_cLocation.X = 20;
		g_gaster2.m_bActive = true;
		g_gaster2.m_cLocation.Y = 10 * (g_dElapsedTime - 30);
	}
	else if (g_dElapsedTime > 31 && g_dElapsedTime <= 32)
	{
		g_gaster2.m_cLocation.Y = 10 * (g_dElapsedTime - 31);

	}
	else
	{
		g_gaster1.m_bActive = false;
		g_gaster1.m_bFire = false;
		g_gaster2.m_bActive = false;
		g_gaster2.m_bFire = false;
		g_gaster3.m_bActive = false;
		g_gaster3.m_bFire = false;
		g_gaster4.m_bActive = false;
		g_gaster4.m_bFire = false;
	}
	// End Boss stuff



	std::fstream myfile("map/bossscreen.txt");
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
	if (g_abKeyPressed[K_E])
	{
		if (currentWeapon < 3)
		{
			currentWeapon++;
		}
		else
		{
			currentWeapon = 0;
		}
		g_dBounceTime = g_dElapsedTime + 0.2;
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
	if (((g_sChar.m_cLocation.X == g_gaster1.m_cLocation.X - 1 || g_sChar.m_cLocation.X == g_gaster1.m_cLocation.X || g_sChar.m_cLocation.X == g_gaster1.m_cLocation.X + 1) && g_gaster1.m_bFire) ||
		((g_sChar.m_cLocation.Y == g_gaster2.m_cLocation.Y - 1 || g_sChar.m_cLocation.Y == g_gaster2.m_cLocation.Y || g_sChar.m_cLocation.Y == g_gaster2.m_cLocation.Y + 1) && g_gaster2.m_bFire) ||
		((g_sChar.m_cLocation.Y == g_gaster3.m_cLocation.Y - 1 || g_sChar.m_cLocation.Y == g_gaster3.m_cLocation.Y || g_sChar.m_cLocation.Y == g_gaster3.m_cLocation.Y + 1) && g_gaster3.m_bFire) ||
		((g_sChar.m_cLocation.X == g_gaster4.m_cLocation.X - 1 || g_sChar.m_cLocation.X == g_gaster4.m_cLocation.X || g_sChar.m_cLocation.X == g_gaster4.m_cLocation.X + 1) && g_gaster4.m_bFire))
	{
		g_sChar.m_bActive = false;
		bSomethingHappened = true;
	}
	myfile.close();
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.07; // 125ms should be enough
	}
}
void boss_moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	std::fstream myfile("map/bossmap.txt");
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	
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
	if (g_abKeyPressed[K_E])
	{
		if (currentWeapon < 3)
		{
			currentWeapon++;
		}
		else
		{
			currentWeapon = 0;
		}
		g_dBounceTime = g_dElapsedTime + 0.2;
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
	if (Lives < 1 || g_abKeyPressed[K_ESCAPE])
	{
		PlaySound(TEXT("sound/dead.wav"), NULL, SND_FILENAME);
		g_eGameState = S_GAMEOVER;
	}
	if (g_abKeyPressed[K_C])
	{
		g_enemy1.m_bActive = false;
		g_enemy2.m_bActive = false;
		g_enemy3.m_bActive = false;
		g_enemy4.m_bActive = false;
		g_enemy5.m_bActive = false;
		g_enemy6.m_bActive = false;
		if(SongType == EBossBattle)
			g_dElapsedTime = 20;
	}
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
		SongType == EStage)
		g_door.m_bActive = true;
	if (g_door.m_bActive == true && g_sChar.m_cLocation.X == g_door.m_cLocation.X && g_sChar.m_cLocation.Y == g_door.m_cLocation.Y)
	{
		if (SongType == EBoss)
		{
			boss_battle_init();
			SongType = EBossBattle;
		}
		else
		{
			stages++;
			int_stages = stages;
			if (int_stages == 10)
				SongType = EBoss;
			else
			{
				if (SongType == EBossBattle)
					b_play = false;
				SongType = EStage;
			}
			if (SongType == EBoss)
				boss_init();
			else
				init();
			g_eGameState = S_GAME;
			if (Lives != 9)
				Lives++;
		}
	}
}
void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x00);
}
void renderIntro()
{
	if (g_dElapsedTime <= 7)
		for (int i = 0; i < 12; ++i)
		{
			std::fstream myfile("map/scene1.txt");
			std::string sLine;
			for (short i = 0; i < 24 * 80; i++)
			{
				if (i % 80 == 0)
					std::getline(myfile, sLine);
				g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, sLine[i % 80], 0x0F);
			}
			myfile.close();
		}
	if (g_dElapsedTime > 7 && g_dElapsedTime <= 14)
		for (int i = 0; i < 12; ++i)
		{
			std::fstream myfile("map/scene2.txt");
			std::string sLine;
			for (short i = 0; i < 24 * 80; i++)
			{
				if (i % 80 == 0)
					std::getline(myfile, sLine);
				g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, sLine[i % 80], 0x0F);
			}
			myfile.close();
		}
	if (g_dElapsedTime > 14 && g_dElapsedTime <= 21)
		for (int i = 0; i < 12; ++i)
		{
			std::fstream myfile("map/scene3.txt");
			std::string sLine;
			for (short i = 0; i < 24 * 80; i++)
			{
				if (i % 80 == 0)
					std::getline(myfile, sLine);
				g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, sLine[i % 80], 0x0F);
			}
			myfile.close();
		}
	if (g_dElapsedTime > 21 && g_dElapsedTime <= 28)
		for (int i = 0; i < 12; ++i)
		{
			std::fstream myfile("map/scene4.txt");
			std::string sLine;
			for (short i = 0; i < 24 * 80; i++)
			{
				if (i % 80 == 0)
					std::getline(myfile, sLine);
				g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, sLine[i % 80], 0x0F);
			}
			myfile.close();
		}

	if (g_dElapsedTime > 28 && g_dElapsedTime <= 35)
		for (int i = 0; i < 12; ++i)
		{
			std::fstream myfile("map/scene5.txt");
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
	renderCharacter();  // renders the character into the buffer
	if (SongType == EStage)
	{
		renderEnemy1();
		renderEnemy2();
		renderEnemy3();
		renderEnemy4();
		renderEnemy5();
		renderEnemy6();
		renderWeapon();
	}
	if (SongType == EBossBattle)
	{
		renderGaster1();
		renderGaster2();
		renderGaster3();
		renderGaster4();
		renderBossSpeech();
		renderWeapon();
	}
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
	if (SongType == EStage)
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
	else if (SongType == EBoss)
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
	else if (SongType == EBossBattle)
		for (int i = 0; i < 12; ++i)
		{
			std::fstream myfile("map/bossscreen.txt");
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
void renderGaster1() // Up
{
	if (g_gaster1.m_bActive == true)
	{
		COORD c;
		WORD charColor = 0x0E;
		char character = '_';
		c.X = g_gaster1.m_cLocation.X;
		c.Y = g_gaster1.m_cLocation.Y - 1;
		g_Console.writeToBuffer(c, character, charColor);
		character = '/';
		c.X = g_gaster1.m_cLocation.X - 1;
		c.Y = g_gaster1.m_cLocation.Y;
		g_Console.writeToBuffer(c, character, charColor);
		character = 92;
		c.X = g_gaster1.m_cLocation.X + 1;
		c.Y = g_gaster1.m_cLocation.Y;
		g_Console.writeToBuffer(c, character, charColor);
		character = 'O';
		c.X = g_gaster1.m_cLocation.X;
		c.Y = g_gaster1.m_cLocation.Y;
		g_Console.writeToBuffer(c, character, charColor);
		if (g_gaster1.m_bFire)
			character = '|';
		else
			character = 92;
		c.X = g_gaster1.m_cLocation.X - 1;
		c.Y = g_gaster1.m_cLocation.Y + 1;
		g_Console.writeToBuffer(c, character, charColor);
		if (g_gaster1.m_bFire)
			character = '|';
		else
			character = '/';
		c.X = g_gaster1.m_cLocation.X + 1;
		c.Y = g_gaster1.m_cLocation.Y + 1;
		g_Console.writeToBuffer(c, character, charColor);
		if (g_gaster1.m_bFire)
			character = 177;
		else
			character = 176;
		c.X = g_gaster1.m_cLocation.X;
		c.Y = g_gaster1.m_cLocation.Y + 1;
		g_Console.writeToBuffer(c, character, charColor);
		if (g_gaster1.m_bFire)
		{
			for (int j = -1; j <= 1; j++)
			{
				for (size_t i = g_gaster1.m_cLocation.Y + 1; i < 24; i++)
				{
					character = 177;
					c.X = g_gaster1.m_cLocation.X + j;
					c.Y = i+1;
					g_Console.writeToBuffer(c, character, charColor);
				}
			}
		}
		
	}
}
void renderGaster2() // Left
{
	if (g_gaster2.m_bActive == true)
	{
		COORD c;
		WORD charColor = 0x0E;
		char character = '|';
		c.X = g_gaster2.m_cLocation.X - 1;
		c.Y = g_gaster2.m_cLocation.Y;
		g_Console.writeToBuffer(c, character, charColor);
		character = '/';
		c.X = g_gaster2.m_cLocation.X - 1;
		c.Y = g_gaster2.m_cLocation.Y - 1;
		g_Console.writeToBuffer(c, character, charColor);
		character = 92;
		c.X = g_gaster2.m_cLocation.X - 1;
		c.Y = g_gaster2.m_cLocation.Y + 1;
		g_Console.writeToBuffer(c, character, charColor);
		character = 'O';
		c.X = g_gaster2.m_cLocation.X;
		c.Y = g_gaster2.m_cLocation.Y;
		g_Console.writeToBuffer(c, character, charColor);
		if (g_gaster2.m_bFire)
			character = '-';
		else
			character = '/';
		c.X = g_gaster2.m_cLocation.X + 1;
		c.Y = g_gaster2.m_cLocation.Y + 1;
		g_Console.writeToBuffer(c, character, charColor);
		if (g_gaster2.m_bFire)
			character = '-';
		else
			character = 92;
		c.X = g_gaster2.m_cLocation.X + 1;
		c.Y = g_gaster2.m_cLocation.Y - 1;
		g_Console.writeToBuffer(c, character, charColor);
		if (g_gaster2.m_bFire)
			character = 177;
		else
			character = 176;
		c.X = g_gaster2.m_cLocation.X + 1;
		c.Y = g_gaster2.m_cLocation.Y;
		g_Console.writeToBuffer(c, character, charColor); 
		if (g_gaster2.m_bFire)
		{
			for (int j = -1; j <= 1; j++)
			{
				for (size_t i = g_gaster2.m_cLocation.X + 1; i < 80; i++)
				{
					character = 177;
					c.Y = g_gaster2.m_cLocation.Y + j;
					c.X = i + 1;
					g_Console.writeToBuffer(c, character, charColor);
				}
			}
		}
	}
}
void renderGaster3() // Right
{
	if (g_gaster3.m_bActive == true)
	{
		COORD c;
		WORD charColor = 0x0E;
		char character = '|';
		c.X = g_gaster3.m_cLocation.X + 1;
		c.Y = g_gaster3.m_cLocation.Y;
		g_Console.writeToBuffer(c, character, charColor);
		character = '/';
		c.X = g_gaster3.m_cLocation.X + 1;
		c.Y = g_gaster3.m_cLocation.Y + 1;
		g_Console.writeToBuffer(c, character, charColor);
		character = 92;
		c.X = g_gaster3.m_cLocation.X + 1;
		c.Y = g_gaster3.m_cLocation.Y - 1;
		g_Console.writeToBuffer(c, character, charColor);
		character = 'O';
		c.X = g_gaster3.m_cLocation.X;
		c.Y = g_gaster3.m_cLocation.Y;
		g_Console.writeToBuffer(c, character, charColor);
		if (g_gaster3.m_bFire)
			character = '-';
		else
			character = 92;
		c.X = g_gaster3.m_cLocation.X - 1;
		c.Y = g_gaster3.m_cLocation.Y + 1;
		g_Console.writeToBuffer(c, character, charColor);
		if (g_gaster3.m_bFire)
			character = '-';
		else
			character = '/';
		c.X = g_gaster3.m_cLocation.X - 1;
		c.Y = g_gaster3.m_cLocation.Y - 1;
		g_Console.writeToBuffer(c, character, charColor);
		if (g_gaster3.m_bFire)
			character = 177;
		else
			character = 176;
		c.X = g_gaster3.m_cLocation.X - 1;
		c.Y = g_gaster3.m_cLocation.Y;
		g_Console.writeToBuffer(c, character, charColor);
		if (g_gaster3.m_bFire)
		{
			for (int j = -1; j <= 1; j++)
			{
				for (size_t i = g_gaster3.m_cLocation.X + 1; i > 0; i--)
				{
					character = 177;
					c.Y = g_gaster3.m_cLocation.Y + j;
					c.X = i - 1;
					g_Console.writeToBuffer(c, character, charColor);
				}
			}
		}
	}
}
void renderGaster4() // Up2
{
	if (g_gaster4.m_bActive == true)
	{
		COORD c;
		WORD charColor = 0x0E;
		char character = '_';
		c.X = g_gaster4.m_cLocation.X;
		c.Y = g_gaster4.m_cLocation.Y - 1;
		g_Console.writeToBuffer(c, character, charColor);
		character = '/';
		c.X = g_gaster4.m_cLocation.X - 1;
		c.Y = g_gaster4.m_cLocation.Y;
		g_Console.writeToBuffer(c, character, charColor);
		character = 92;
		c.X = g_gaster4.m_cLocation.X + 1;
		c.Y = g_gaster4.m_cLocation.Y;
		g_Console.writeToBuffer(c, character, charColor);
		character = 'O';
		c.X = g_gaster4.m_cLocation.X;
		c.Y = g_gaster4.m_cLocation.Y;
		g_Console.writeToBuffer(c, character, charColor);
		if (g_gaster4.m_bFire)
			character = '|';
		else
			character = 92;
		c.X = g_gaster4.m_cLocation.X - 1;
		c.Y = g_gaster4.m_cLocation.Y + 1;
		g_Console.writeToBuffer(c, character, charColor);
		if (g_gaster4.m_bFire)
			character = '|';
		else
			character = '/';
		c.X = g_gaster4.m_cLocation.X + 1;
		c.Y = g_gaster4.m_cLocation.Y + 1;
		g_Console.writeToBuffer(c, character, charColor);
		if (g_gaster4.m_bFire)
			character = 177;
		else
			character = 176;
		c.X = g_gaster4.m_cLocation.X;
		c.Y = g_gaster4.m_cLocation.Y + 1;
		g_Console.writeToBuffer(c, character, charColor); 
		if (g_gaster4.m_bFire)
		{
			for (int j = -1; j <= 1; j++)
			{
				for (size_t i = g_gaster4.m_cLocation.Y + 1; i < 24; i++)
				{
					character = 177;
					c.X = g_gaster4.m_cLocation.X + j;
					c.Y = i + 1;
					g_Console.writeToBuffer(c, character, charColor);
				}
			}
		}
	}
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
void renderBossSpeech()
{
	if (bossSpeech == true)
	{
		for (int i = 0; i < 12; ++i)
		{
			std::fstream myfile("map/bossSpeechBubble.txt");
			std::string sLine;
			for (short i = 0; i < 8 * 27; i++)
			{
				if (i % 27 == 0)
					std::getline(myfile, sLine);
				g_Console.writeToBuffer(COORD{ i % 27 + 52, i / 27 + 3 }, sLine[i % 27], 0x0F);
			}
			myfile.close();
		}
	}
	if (g_dElapsedTime > 2 && g_dElapsedTime <= 5)
	{
		char text[] = "So...";
		for (short i = 0; i < 5; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 5 + 62, 7 }, text[i % 5], 0x0F);
		}
	}
	if (g_dElapsedTime > 6 && g_dElapsedTime <= 9)
	{
		char text[] = "You've made it this far.";
		for (short i = 0; i < 24; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 12 + 60, i / 12 + 6 }, text[i % 24], 0x0F);
		}
	}
	if (g_dElapsedTime > 10 && g_dElapsedTime <= 14)
	{
		char text[] = "I am the one who destroyed your town.";
		for (short i = 0; i < 37; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 13 + 60, i / 13 + 6 }, text[i % 37], 0x0F);
		}
	}
	if (g_dElapsedTime > 15 && g_dElapsedTime <= 18)
	{
		char text[] = "I assume you'rehere to destroyme too.";
		for (short i = 0; i < 37; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 15 + 59, i / 15 + 6 }, text[i % 37], 0x0F);
		}
	}
	if (g_dElapsedTime > 19 && g_dElapsedTime <= 21)
	{
		char text[] = "Not if I canhelp it!";
		for (short i = 0; i < 20; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 12 + 60, i / 12 + 6 }, text[i % 20], 0x0F);
		}
	}
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
	int i = 0;
	std::string in;
	std::ifstream weapondata("weapons.txt");
	getline(weapondata, Weapons[i].Name); // Gets Pistol
	weapondata >> Weapons[i].ClipMax;
	weapondata >> Weapons[i].Reload;
	weapondata >> Weapons[i].Range;
	i++;
	weapondata.ignore();
	getline(weapondata, Weapons[i].Name); // Gets Crossbow
	weapondata >> Weapons[i].ClipMax;
	weapondata >> Weapons[i].Reload;
	weapondata >> Weapons[i].Range;
	i++;
	weapondata.ignore();
	getline(weapondata, Weapons[i].Name); // Gets Spear
	weapondata >> Weapons[i].ClipMax;
	weapondata >> Weapons[i].Reload;
	weapondata >> Weapons[i].Range;
	i++;
	weapondata.ignore();
	getline(weapondata, Weapons[i].Name); // Gets Rifle
	weapondata >> Weapons[i].ClipMax;
	weapondata >> Weapons[i].Reload;
	weapondata >> Weapons[i].Range;
	i++;
	weapondata.close();
}
void reload()
{
	Weapons[currentWeapon].Clip += Weapons[currentWeapon].ClipMax;	// Adds ammo left in clip to total
}
void ost()
{
	if (SongType == EMainMenu)
		PlaySound(TEXT("sound/menu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // play sound while in stage
	else if (SongType == EStage)
		PlaySound(TEXT("sound/cave.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // change 'cave' to whatever
	else if (SongType == EBoss)
		PlaySound(TEXT("sound/boss.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // play sound while in stage
	b_play = true;
}
void gameOver()
{
	for (int i = 0; i < 24; ++i)
	{
		std::fstream myfile("map/gameover.txt");
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
		m.X = m.X / 2 - 4;
		g_Console.writeToBuffer(m, "TRY AGAIN", 0x0E);
		m.Y += 2;
		m.X = g_Console.getConsoleSize().X / 2 - 2;
		g_Console.writeToBuffer(m, "Exit", 0x03);
		break;
	case MMExit:
		m.Y = 20;
		m.X = m.X / 2 - 4;
		g_Console.writeToBuffer(m, "TRY AGAIN", 0x03);
		m.Y += 2;
		m.X = g_Console.getConsoleSize().X / 2 - 2;
		g_Console.writeToBuffer(m, "Exit", 0x0E);
		break;
	}
	if (MMSelect == MMStart && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_GAMEOVER) // MENU FOR GAME_OVER
		MMSelect = MMExit;
	else if (MMSelect == MMExit && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_GAMEOVER)
		MMSelect = MMStart;
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMExit && g_eGameState == S_GAMEOVER) // QUIT_GAME
	{
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		g_bQuitGame = true;
	}
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMStart && g_eGameState == S_GAMEOVER) // CONTINUE_GAME
	{
		SongType = EStage;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		b_play = false;
		g_eGameState = S_GAME;
		init();
		Lives = 3;
	}
}
