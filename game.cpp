// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];


bool	g_Pressed = true;

bool	g_PressedToMove = true;

// Game specific variables here
SGameChar	g_sChar; // Player Character
SGameChar	g_enemy1;
SGameChar	g_enemy2;
SGameChar	g_enemy3;
SGameChar	g_enemy4;
SGameChar	g_enemy5;
SGameChar	g_enemy6;
SGameChar   g_weapon;
SBossGaster	g_gaster1;
SBossGaster	g_gaster2;
SBossGaster	g_gaster3;
SBossGaster	g_gaster4;
SMinigame1	g_minigame1_beat1;	
SMinigame1	g_minigame1_beat2;	
SMinigame1	g_minigame1_beat3;	
SMinigame1	g_minigame1_beat4;	
SGameChar	g_minigame2_paddle1;	
SGameChar	g_minigame2_paddle2;
SGameChar	g_door;
SGameChar	g_shopkeeper;
COORD		g_snake;
COORD		Apple;
std::vector<char>	Title;
std::vector<char>	GameOver;
std::vector<char>	SHOP;
std::vector<char>	Map;
std::vector<char>	Instructions;
std::vector<char>	SansMap;
std::vector<char>	SansFightMap;
std::vector<char>	Minigame1Map;	
std::vector<char>	Minigame2Map;	
std::vector<char>   tictactoeGame;	
std::vector<char>   minigameMenu;
std::vector<char>	Scene1;
std::vector<char>	Scene2;
std::vector<char>	Scene3;
std::vector<char>	Scene4;
std::vector<char>	Scene5;
std::vector<char>	SnakeMap;
std::vector<char>   Highscore;
std::vector<COORD>	SnakeLocation; // Part locations
size_t		minigame1time = 0;
size_t		minigame1random = 0;
size_t		deathsound = 0;
size_t		reloadsound = 0;
bool		minigame1sound = false;
bool		shootsound = false;
bool		shootfailsound = false;
int		    MMSelect = MMStart;
int		    int_stages = 1;
int		    MMgame = MMrhythm;
double		stages = 0.000 + int_stages;
size_t		StageType = EMainMenu;
bool		b_play = false;
bool		bossSpeech = false;
int			Weapon1 = 0;
int			Weapon2 = 0;
bool		ticgame = false;
bool        multi = false;
bool        win = false;
bool		g_bMinigame = false;
bool        g_bforscore = false;
int		    g_shootdist = 0;
int		    g_shootmaxdist = 2; // Shooting distance of weapon. Can be changed.
EGAMESTATES	    g_eGameState = S_INTRO;
EWEAPONSTATES	g_eWeaponState = Hold;
EWEAPONSTATES	g_eM2WeaponState = FireUp;
size_t		b_number = 1;
size_t		introPage = 0;
char        charOne = 49;
char        charTwo = 50;
char        charThree = 51;
char        charFour = 52;
char        charFive = 53;
char        charSix = 54;
char        charSeven = 55;
char        charEight = 56;
char        charNine = 57;
double      g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
int		    Lives = 3; // Number of lives the player has left (Base Value is 3)
int			Coin = 0;
int		    currentWeapon = 0; // Current Weapon
WeaponParameters Weapons[4]; // Number of Weapons

// Snake Mini Stuff
int         snake_Size = 1; // Size of snake tail
int         delay = 0; // Delay for movement
char        Direction = 0;
bool        AppleCollected = true;
// Snake Mini Stuff

// Highscore
int rally = 0;
int pong_t = 0,pong_t2 = 0, pong_t3 = 0;
int snake_length = 0, snake_length2 = 0, snake_length3 = 0;

// Console object
Console g_Console(80, 24, "Monster Dungeon"); // name at the top

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void minigame1_init()
{
	b_play = false;
	weapdata();
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;
	g_sChar.m_cLocation.Y = 13;
	g_minigame1_beat1.m_cLocation.Y = 13;
	g_minigame1_beat2.m_cLocation.Y = 13;
	g_minigame1_beat3.m_cLocation.Y = 13;
	g_minigame1_beat4.m_cLocation.Y = 13;
	g_sChar.m_cLocation.X = 40;
	g_minigame1_beat1.m_bActive = false;
	g_minigame1_beat2.m_bActive = false;
	g_minigame1_beat3.m_bActive = false;
	g_minigame1_beat4.m_bActive = false;
	g_door.m_cLocation.X = 40;
	g_door.m_cLocation.Y = 13;
	g_door.m_bActive = false;
	g_shopkeeper.m_bActive = false;
	if (!g_bMinigame)
	{
		if (Lives + int_stages / 10 <= 99)
			Lives += int_stages / 10;
		else
			Lives = 99;
	}
}
void minigame2_init()
{
	b_play = false;
	weapdata();
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;
	g_sChar.m_cLocation.X = 10;
	g_sChar.m_cLocation.Y = 13;
	g_eWeaponState = FireLeft;
	g_weapon.m_cLocation.X = 69;
	g_weapon.m_cLocation.Y = 13;
	g_minigame2_paddle1.m_bActive = true;
	g_minigame2_paddle2.m_bActive = true;
	g_minigame2_paddle1.m_cLocation.X = g_sChar.m_cLocation.X;
	g_minigame2_paddle1.m_cLocation.Y = g_sChar.m_cLocation.Y;
	g_minigame2_paddle2.m_cLocation.X = 70;
	g_minigame2_paddle2.m_cLocation.Y = g_weapon.m_cLocation.Y;
	g_weapon.m_bActive;
	g_door.m_cLocation.X = 10;
	g_door.m_cLocation.Y = 13;
	g_door.m_bActive = false;
	g_shopkeeper.m_bActive = false;
}
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
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		if (Map[enemyX + enemyY * 80] == ' ')
			break;
	}
	g_sChar.m_cLocation.X = enemyX;
	g_sChar.m_cLocation.Y = enemyY;
	g_sChar.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		if (Map[enemyX + enemyY * 80] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy1.m_cLocation.X = enemyX;
	g_enemy1.m_cLocation.Y = enemyY;
	g_enemy1.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		if (Map[enemyX + enemyY * 80] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy2.m_cLocation.X = enemyX;
	g_enemy2.m_cLocation.Y = enemyY;
	g_enemy2.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		if (Map[enemyX + enemyY * 80] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy3.m_cLocation.X = enemyX;
	g_enemy3.m_cLocation.Y = enemyY;
	g_enemy3.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		if (Map[enemyX + enemyY * 80] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy4.m_cLocation.X = enemyX;
	g_enemy4.m_cLocation.Y = enemyY;
	g_enemy4.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		if (Map[enemyX + enemyY * 80] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
			break;
	}
	g_enemy5.m_cLocation.X = enemyX;
	g_enemy5.m_cLocation.Y = enemyY;
	g_enemy5.m_bActive = true;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		if (Map[enemyX + enemyY * 80] == ' ' && (g_sChar.m_cLocation.X != enemyX || g_sChar.m_cLocation.Y != enemyY))
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
		if (Map[enemyX + enemyY * 80] == ' ')
			break;
	}
	g_door.m_cLocation.X = enemyX;
	g_door.m_cLocation.Y = enemyY;
	g_door.m_bActive = false;
	while (1)
	{
		enemyX = rand() % 80;
		enemyY = rand() % 24;
		if (Map[enemyX + enemyY * 80] == ' ')
			break;
	}
	g_shopkeeper.m_cLocation.X = enemyX;
	g_shopkeeper.m_cLocation.Y = enemyY;
	g_shopkeeper.m_bActive = false;
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
	g_abKeyPressed[K_1] = isKeyPressed(49);
	g_abKeyPressed[K_2] = isKeyPressed(50);
	g_abKeyPressed[K_3] = isKeyPressed(51);
	g_abKeyPressed[K_4] = isKeyPressed(52);
	g_abKeyPressed[K_5] = isKeyPressed(53);
	g_abKeyPressed[K_6] = isKeyPressed(54);
	g_abKeyPressed[K_7] = isKeyPressed(55);
	g_abKeyPressed[K_8] = isKeyPressed(56);
	g_abKeyPressed[K_9] = isKeyPressed(57);
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
		break;
	case S_TITLE: splashScreenWait(); // game logic for the splash screen
		break;
	case S_GAME: gameplay(); // gameplay logic when we are in the game
		break;
	case S_MINIGAME: minigameselect();
		break;
	case S_SHOP: shopoption();
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
	case S_INSTRUCTIONS: instructions();
		break;
	case S_MINIGAME: minigame();
		break;
	case S_HIGHSCORE: highscoreLoad();
		break;
	case S_CONTINUE: continueSave();
		break;
	case S_SHOP: shop();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}
void intro()
{
	if (b_play == false)
	{
		ost();
		b_play = true;
	}
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	if (g_abKeyPressed[K_RIGHT] || g_abKeyPressed[K_DOWN] || g_abKeyPressed[K_D] || g_abKeyPressed[K_S])
	{
		introPage++;
		bSomethingHappened = true;
	}
	else if (introPage > 0 && (g_abKeyPressed[K_LEFT] || g_abKeyPressed[K_UP] || g_abKeyPressed[K_A] || g_abKeyPressed[K_W]))
	{
		introPage--;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_SPACE] || introPage > 4)
	{
		g_eGameState = S_TITLE;
		StageType = EMainMenu;
		init();
		bSomethingHappened = true;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.15; // 125ms should be enough
	}
}
void splashScreenWait()
{
	Lives = 3;
	g_bMinigame = false;
	if (!b_play)
		ost();
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	if (MMSelect == MMStart && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMInstructions;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMStart && (g_abKeyPressed[K_A] || g_abKeyPressed[K_RIGHT] || g_abKeyPressed[K_D] || g_abKeyPressed[K_LEFT]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMContinue;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMContinue && (g_abKeyPressed[K_A] || g_abKeyPressed[K_RIGHT] || g_abKeyPressed[K_D] || g_abKeyPressed[K_LEFT]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMStart;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMInstructions && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMminigame;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMInstructions && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMStart;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMInstructions && (g_abKeyPressed[K_D] || g_abKeyPressed[K_RIGHT]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMHighscore;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMHighscore && (g_abKeyPressed[K_A] || g_abKeyPressed[K_LEFT]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMInstructions;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMHighscore && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMContinue;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMHighscore && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMExit;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMContinue && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMHighscore;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMExit && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMHighscore;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMHighscore && (g_abKeyPressed[K_A] || g_abKeyPressed[K_LEFT]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMInstructions;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMminigame && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMInstructions;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMStart && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMminigame;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMContinue && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP] || g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMExit;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMExit && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP] || g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMContinue;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMminigame && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMStart;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMExit && (g_abKeyPressed[K_A] || g_abKeyPressed[K_RIGHT] || g_abKeyPressed[K_D] || g_abKeyPressed[K_LEFT]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMminigame;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMminigame && (g_abKeyPressed[K_A] || g_abKeyPressed[K_RIGHT] || g_abKeyPressed[K_D] || g_abKeyPressed[K_LEFT]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMExit;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMInstructions && (g_abKeyPressed[K_A] || g_abKeyPressed[K_LEFT]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMHighscore;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMHighscore && (g_abKeyPressed[K_D] || g_abKeyPressed[K_RIGHT]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMInstructions;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMInstructions && g_eGameState == S_TITLE)
	{
		g_eGameState = S_INSTRUCTIONS;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		b_play = false;
	}
	else if (g_abKeyPressed[K_SPACE] && MMSelect == MMExit && g_eGameState == S_TITLE)
	{
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		g_bQuitGame = true;
	}
	else if (g_abKeyPressed[K_SPACE] && MMSelect == MMStart && g_eGameState == S_TITLE)
	{
		StageType = EStage;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		b_play = false;
		Weapons[0].Clip = Weapons[0].ClipMax;
		int_stages = 1;
		Weapon1 = 0;
		Weapon2 = 0;
		save();
		g_eGameState = S_CONTINUE;
	}
	else if (g_abKeyPressed[K_SPACE] && MMSelect == MMContinue && g_eGameState == S_TITLE)
	{
		StageType = EStage;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		b_play = false;
		g_eGameState = S_CONTINUE;
	}
	else if (g_abKeyPressed[K_SPACE] && MMSelect == MMminigame && g_eGameState == S_TITLE)
	{
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		b_play = false;
		g_eGameState = S_MINIGAME;
	}
	else if (g_abKeyPressed[K_SPACE] && MMSelect == MMHighscore && g_eGameState == S_TITLE)
	{
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		b_play = false;
		g_eGameState = S_HIGHSCORE;
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
	else if (StageType == EBossBattle)
		bossbattle_moveCharacter();
	else if (StageType == EMinigame1)
		minigame1_moveCharacter();
	else if (StageType == EMinigame2)
		minigame2_moveCharacter();
	else if (StageType == ETicTacToe)
		tictactoePlay();
	else if (StageType == ETicTacToe2)
		tictactoeMulti();
	else if (StageType == EMiniGameSnake)
		snakeMovement();
	sound(); // sound can be played here too.
	if (!b_play)
		ost();
}
void minigame1_moveCharacter()	
{	
	// Minigame stuff go here	
	if (g_dElapsedTime < 3 && g_dElapsedTime >= 2.9)	
	{	
		minigame1time = 3;	
		minigame1random = 0;	
	}	
	else if (g_dElapsedTime < 4 && g_dElapsedTime >= 3.9)	
	{	
		minigame1time = 4;	
		minigame1random = 1;	
	}	
	else if (g_dElapsedTime < int_stages && g_dElapsedTime >= 4.9 && g_dElapsedTime >= minigame1time + 1)	
	{	
		minigame1time++;
		minigame1random = 2;
	}
	else if (g_dElapsedTime >= int_stages + 3)
	{	
		if (g_bMinigame)	
			g_eGameState = S_MINIGAME;	
		else	
		{	
			g_door.m_bActive = true;	
			g_minigame1_beat1.m_bActive = false;	
			g_minigame1_beat2.m_bActive = false;	
			g_minigame1_beat3.m_bActive = false;	
			g_minigame1_beat4.m_bActive = false;	
		}	
	}	
	switch (minigame1random)	
	{	
	case 0:	
	{	
		if (g_dElapsedTime < minigame1time + 0.1 && g_dElapsedTime >= minigame1time)	
		{	
			g_minigame1_beat1.m_bActive = true;	
			g_minigame1_beat1.m_cLocation.X = 2;	
			g_minigame1_beat1.m_bLeft = true;	
		}	
		else if (g_dElapsedTime < minigame1time + 0.3 && g_dElapsedTime >= minigame1time + 0.2)	
		{	
			g_minigame1_beat2.m_bActive = true;	
			g_minigame1_beat2.m_cLocation.X = 2;	
			g_minigame1_beat2.m_bLeft = true;	
		}	
		else if (g_dElapsedTime < minigame1time + 0.5 && g_dElapsedTime >= minigame1time + 0.4)	
		{	
			g_minigame1_beat3.m_bActive = true;	
			g_minigame1_beat3.m_cLocation.X = 2;	
			g_minigame1_beat3.m_bLeft = true;	
		}	
		else if (g_dElapsedTime < minigame1time + 0.7 && g_dElapsedTime >= minigame1time + 0.6)	
		{	
			g_minigame1_beat4.m_bActive = true;	
			g_minigame1_beat4.m_cLocation.X = 2;	
			g_minigame1_beat4.m_bLeft = true;	
		}	
		break;	
	}	
	case 1:	
		{	
			if (g_dElapsedTime < minigame1time + 0.1 && g_dElapsedTime >= minigame1time)	
			{	
				g_minigame1_beat1.m_bActive = true;	
				g_minigame1_beat1.m_cLocation.X = 77;	
				g_minigame1_beat1.m_bLeft = false;	
			}	
			else if (g_dElapsedTime < minigame1time + 0.3 && g_dElapsedTime >= minigame1time + 0.2)	
			{	
				g_minigame1_beat2.m_bActive = true;	
				g_minigame1_beat2.m_cLocation.X = 77;	
				g_minigame1_beat2.m_bLeft = false;	
			}	
			else if (g_dElapsedTime < minigame1time + 0.5 && g_dElapsedTime >= minigame1time + 0.4)	
			{	
				g_minigame1_beat3.m_bActive = true;	
				g_minigame1_beat3.m_cLocation.X = 77;	
				g_minigame1_beat3.m_bLeft = false;	
			}	
			else if (g_dElapsedTime < minigame1time + 0.7 && g_dElapsedTime >= minigame1time + 0.6)	
			{	
				g_minigame1_beat4.m_bActive = true;	
				g_minigame1_beat4.m_cLocation.X = 77;	
				g_minigame1_beat4.m_bLeft = false;	
			}	
			break;	
		}	
	case 2:	
		{	
			if (g_dElapsedTime < minigame1time + 0.1 && g_dElapsedTime >= minigame1time)	
			{	
				g_minigame1_beat1.m_bActive = true;	
				if (rand() % 2)	
				{	
					g_minigame1_beat1.m_cLocation.X = 2;	
					g_minigame1_beat1.m_bLeft = true;	
				}	
				else	
				{	
					g_minigame1_beat1.m_cLocation.X = 77;	
					g_minigame1_beat1.m_bLeft = false;	
				}	
			}	
			else if (g_dElapsedTime < minigame1time + 0.35 && g_dElapsedTime >= minigame1time + 0.25)	
			{	
				g_minigame1_beat2.m_bActive = true;	
				if (rand() % 2)	
				{	
					g_minigame1_beat2.m_cLocation.X = 2;	
					g_minigame1_beat2.m_bLeft = true;	
				}	
				else	
				{	
					g_minigame1_beat2.m_cLocation.X = 77;	
					g_minigame1_beat2.m_bLeft = false;	
				}	
			}	
			else if (g_dElapsedTime < minigame1time + 0.6 && g_dElapsedTime >= minigame1time + 0.5)	
			{	
				g_minigame1_beat3.m_bActive = true;	
				if (rand() % 2)	
				{	
					g_minigame1_beat3.m_cLocation.X = 2;	
					g_minigame1_beat3.m_bLeft = true;	
				}	
				else	
				{	
					g_minigame1_beat3.m_cLocation.X = 77;	
					g_minigame1_beat3.m_bLeft = false;	
				}	
			}	
			else if (g_dElapsedTime < minigame1time + 0.85 && g_dElapsedTime >= minigame1time + 0.75)	
			{	
				g_minigame1_beat4.m_bActive = true;	
				if (rand() % 2)	
				{	
					g_minigame1_beat4.m_cLocation.X = 2;	
					g_minigame1_beat4.m_bLeft = true;	
				}	
				else	
				{	
					g_minigame1_beat4.m_cLocation.X = 77;	
					g_minigame1_beat4.m_bLeft = false;	
				}	
			}	
			break;	
		}	
	}	
	// Minigame stuff end	
	if (g_abKeyPressed[K_LEFT])	
	{	
		g_weapon.m_cLocation.X = g_sChar.m_cLocation.X - 3;	
		g_weapon.m_cLocation.Y = 13;
		/*if (Shots.size() > 0)
			Shots.erase(Shots.begin() + 0);
		Shots.push_back(Bullet);*/
	}	
	else if (g_abKeyPressed[K_RIGHT])	
	{	
		g_weapon.m_cLocation.X = g_sChar.m_cLocation.X + 3;	
		g_weapon.m_cLocation.Y = 13;
		/*if (Shots.size() > 0)
			Shots.erase(Shots.begin() + 0);
		Shots.push_back(Bullet);*/
	}	
	else	
	{	
		g_weapon.m_cLocation.X = 0;	
		g_weapon.m_cLocation.Y = 0;	
	}	
	if (g_weapon.m_cLocation.X == g_minigame1_beat1.m_cLocation.X && g_minigame1_beat1.m_bActive == true)	
	{	
		minigame1sound = true;	
		g_minigame1_beat1.m_bActive = false;	
		g_minigame1_beat1.m_cLocation.X = 2;	
	}	
	if (g_weapon.m_cLocation.X == g_minigame1_beat2.m_cLocation.X && g_minigame1_beat2.m_bActive == true)	
	{	
		minigame1sound = true;	
		g_minigame1_beat2.m_bActive = false;	
		g_minigame1_beat2.m_cLocation.X = 77;	
	}	
	if (g_weapon.m_cLocation.X == g_minigame1_beat3.m_cLocation.X && g_minigame1_beat3.m_bActive == true)	
	{	
		minigame1sound = true;	
		g_minigame1_beat3.m_bActive = false;	
		g_minigame1_beat3.m_cLocation.X = 2;	
	}	
	if (g_weapon.m_cLocation.X == g_minigame1_beat4.m_cLocation.X && g_minigame1_beat4.m_bActive == true)	
	{	
		minigame1sound = true;	
		g_minigame1_beat4.m_bActive = false;	
		g_minigame1_beat4.m_cLocation.X = 77;	
	}	
	if (g_minigame1_beat1.m_cLocation.X == g_sChar.m_cLocation.X && g_minigame1_beat1.m_bActive == true)	
	{	
		g_minigame1_beat1.m_bActive = false;	
		g_minigame1_beat1.m_cLocation.X = 2;	
		g_sChar.m_bActive = false;	
		deathsound = 5;	
	}	
	if (g_minigame1_beat2.m_cLocation.X == g_sChar.m_cLocation.X && g_minigame1_beat2.m_bActive == true)	
	{	
		g_minigame1_beat2.m_bActive = false;	
		g_minigame1_beat2.m_cLocation.X = 77;	
		g_sChar.m_bActive = false;	
		deathsound = 5;	
	}	
	if (g_minigame1_beat3.m_cLocation.X == g_sChar.m_cLocation.X && g_minigame1_beat3.m_bActive == true)	
	{	
		g_minigame1_beat3.m_bActive = false;	
		g_minigame1_beat3.m_cLocation.X = 2;	
		g_sChar.m_bActive = false;	
		deathsound = 5;	
	}	
	if (g_minigame1_beat4.m_cLocation.X == g_sChar.m_cLocation.X && g_minigame1_beat4.m_bActive == true)	
	{	
		g_minigame1_beat4.m_bActive = false;	
		g_minigame1_beat4.m_cLocation.X = 77;	
		g_sChar.m_bActive = false;	
		deathsound = 5;	
	}	
	bool bSomethingHappened = false;	
	if (g_dBounceTime > g_dElapsedTime)	
		return;	
	if (g_minigame1_beat1.m_bActive)	
	{	
		if (g_minigame1_beat1.m_bLeft)	
			g_minigame1_beat1.m_cLocation.X++;	
		else	
			g_minigame1_beat1.m_cLocation.X--;	
		bSomethingHappened = true;	
	}	
	if (g_minigame1_beat2.m_bActive)	
	{	
		if (g_minigame1_beat2.m_bLeft)	
			g_minigame1_beat2.m_cLocation.X++;	
		else	
			g_minigame1_beat2.m_cLocation.X--;	
		bSomethingHappened = true;	
	}	
	if (g_minigame1_beat3.m_bActive)	
	{	
		if (g_minigame1_beat3.m_bLeft)	
			g_minigame1_beat3.m_cLocation.X++;	
		else	
			g_minigame1_beat3.m_cLocation.X--;	
		bSomethingHappened = true;	
	}	
	if (g_minigame1_beat4.m_bActive)	
	{	
		if (g_minigame1_beat4.m_bLeft)	
			g_minigame1_beat4.m_cLocation.X++;	
		else	
			g_minigame1_beat4.m_cLocation.X--;	
		bSomethingHappened = true;	
	}	
	if (bSomethingHappened)	
	{	
		// set the bounce time to some time in the future to prevent accidental triggers	
		g_dBounceTime = g_dElapsedTime + 0.02; // 125ms should be enough	
	}	
}	
void minigame2_moveCharacter()	
{	
	bool bSomethingHappened = false;	
	if (g_dBounceTime > g_dElapsedTime)	
		return;	
	if (g_eWeaponState == FireLeft)	
	{	
		if (g_eM2WeaponState == FireUp)	
		{	
			if (Minigame2Map[g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 80 - 80] == ' ' || Minigame2Map[g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 80 - 80] == '|')	
			{	
				g_weapon.m_cLocation.X--;	
				g_weapon.m_cLocation.Y--;	
				bSomethingHappened = true;
			}	
			else	
				g_eM2WeaponState = FireDown;	
		}	
		else if (g_eM2WeaponState == FireDown)	
		{	
			if (Minigame2Map[g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 80 + 80] == ' ' || Minigame2Map[g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 80 + 80] == '|')	
			{	
				g_weapon.m_cLocation.X--;	
				g_weapon.m_cLocation.Y++;	
				bSomethingHappened = true;
			}	
			else	
				g_eM2WeaponState = FireUp;	
		}	
	}	
	if (g_eWeaponState == FireRight)	
	{	
		if (g_eM2WeaponState == FireUp)	
		{	
			if (Minigame2Map[g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 80 - 80] == ' ' || Minigame2Map[g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 80 - 80] == '|')	
			{	
				g_weapon.m_cLocation.X++;	
				g_weapon.m_cLocation.Y--;	
				bSomethingHappened = true;
			}	
			else	
				g_eM2WeaponState = FireDown;	
		}	
		else if (g_eM2WeaponState == FireDown)	
		{	
			if (Minigame2Map[g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 80 + 80] == ' ' || Minigame2Map[g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 80 + 80] == '|')	
			{	
				g_weapon.m_cLocation.X++;	
				g_weapon.m_cLocation.Y++;	
				bSomethingHappened = true;
			}	
			else	
				g_eM2WeaponState = FireUp;	
		}	
	}	
	if (g_weapon.m_cLocation.X == 1)	
	{	
		g_sChar.m_bActive = false;	
		g_eWeaponState = FireRight;	
		g_weapon.m_cLocation.X = 2;	
	}	
	if (g_weapon.m_cLocation.X >= 78)	
	{	
		if (g_bMinigame)	
			g_eGameState = S_MINIGAME;	
		else	
		{	
			g_weapon.m_cLocation.X = 78;	
			g_door.m_bActive = true;	
			g_door.m_cLocation = g_sChar.m_cLocation;
		}	
	}	
	if (g_weapon.m_cLocation.X == g_minigame2_paddle1.m_cLocation.X && (g_weapon.m_cLocation.Y >= g_minigame2_paddle1.m_cLocation.Y - 2 && g_weapon.m_cLocation.Y <= g_minigame2_paddle1.m_cLocation.Y + 2) && g_eWeaponState == FireLeft)	
	{	
		g_eWeaponState = FireRight;
		rally++;
		if (g_bforscore)
			stages++;
		shootsound = true;	
	}	
	if (g_weapon.m_cLocation.X == g_minigame2_paddle2.m_cLocation.X && (g_weapon.m_cLocation.Y >= g_minigame2_paddle2.m_cLocation.Y - 2 && g_weapon.m_cLocation.Y <= g_minigame2_paddle2.m_cLocation.Y + 2))	
	{	
		g_eWeaponState = FireLeft;	
		shootsound = true;	
	}	
	if (g_abKeyPressed[K_W] && g_sChar.m_cLocation.Y > 0)	
	{	
		if (Minigame2Map[g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 80 - 80] == ' ')	
		{	
			g_sChar.m_cLocation.Y--;	
			bSomethingHappened = true;	
		}	
	}	
	if (g_abKeyPressed[K_S] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)	
	{	
		if (Minigame2Map[g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 80 + 80] == ' ')	
		{	
			g_sChar.m_cLocation.Y++;	
			bSomethingHappened = true;	
		}	
	}	
	g_minigame2_paddle1.m_cLocation.Y = g_sChar.m_cLocation.Y;

	if (g_bforscore) // unlimited gameplay
	{
		if(g_eWeaponState == FireRight && g_minigame2_paddle2.m_cLocation.Y <= g_weapon.m_cLocation.Y + 1 && g_minigame2_paddle2.m_cLocation.Y >= g_weapon.m_cLocation.Y - 1 && g_weapon.m_cLocation.X >= 38)
			g_minigame2_paddle2.m_cLocation.Y = g_weapon.m_cLocation.Y;
	}
	else
	{
		if (g_dElapsedTime < int_stages + 5 && g_eWeaponState == FireRight && g_minigame2_paddle2.m_cLocation.Y <= g_weapon.m_cLocation.Y + 1  && g_minigame2_paddle2.m_cLocation.Y >= g_weapon.m_cLocation.Y - 1 && g_weapon.m_cLocation.X >= 38)	
		    g_minigame2_paddle2.m_cLocation.Y = g_weapon.m_cLocation.Y;
	}
	if (bSomethingHappened)	
		g_dBounceTime = g_dElapsedTime + 0.03 + 0.1/stages; // 125ms should be enough	
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
		(g_dElapsedTime > 19 && g_dElapsedTime <= 21) ||
		(g_dElapsedTime > 23.5 && g_dElapsedTime <= 25.5) ||
		(g_dElapsedTime > 29 && g_dElapsedTime <= 31) ||
		(g_dElapsedTime > 36 && g_dElapsedTime <= 38) ||
		(g_dElapsedTime > 47 && g_dElapsedTime <= 49) ||
		(g_dElapsedTime > 63.5 && g_dElapsedTime <= 65) ||
		(g_dElapsedTime > 66 && g_dElapsedTime <= 73) ||
		(g_dElapsedTime > 75 && g_dElapsedTime <= 87))
		bossSpeech = true;
	else
		bossSpeech = false;

	if (g_dElapsedTime > 21 && g_dElapsedTime <= 21.5) // ATTACK 1 (21)
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
		shootsound = true;
	}
	else if (g_dElapsedTime > 25 && g_dElapsedTime <= 26) // ATTACK 2 (25)
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
		shootsound = true;
	}
	else if (g_dElapsedTime > 28 && g_dElapsedTime <= 29)
	{
		g_gaster1.m_cLocation.Y = 10 - 10 * (g_dElapsedTime - 28);
		g_gaster1.m_bFire = true;
		g_gaster4.m_cLocation.Y = 10 - 10 * (g_dElapsedTime - 28);
		g_gaster4.m_bFire = true;
		shootsound = true;
	}
	else if (g_dElapsedTime > 30 && g_dElapsedTime <= 31) // ATTACK 3 (30)
	{
		g_gaster2.m_cLocation.X = 14;
		g_gaster2.m_bActive = true;
		g_gaster2.m_cLocation.Y = 9 * (g_dElapsedTime - 30);
	}
	else if (g_dElapsedTime > 31 && g_dElapsedTime <= 32)
	{
		g_gaster2.m_cLocation.Y = 9 + 5 * (g_dElapsedTime - 31);
		g_gaster2.m_bFire = true;
		shootsound = true;
	}
	else if (g_dElapsedTime > 32 && g_dElapsedTime <= 33)
	{
		g_gaster2.m_cLocation.Y = 14 + 5 * (g_dElapsedTime - 32);
		g_gaster2.m_bFire = false;
	}
	else if (g_dElapsedTime > 33 && g_dElapsedTime <= 34)
	{
		g_gaster2.m_cLocation.Y = 19;
		g_gaster2.m_bFire = true;
		shootsound = true;
	}
	else if (g_dElapsedTime > 34 && g_dElapsedTime <= 35)
	{
		g_gaster2.m_cLocation.Y = 19 - 9 * (g_dElapsedTime - 34);
		g_gaster2.m_bFire = true;
		shootsound = true;
	}
	else if (g_dElapsedTime > 35 && g_dElapsedTime <= 36)
	{
		g_gaster2.m_cLocation.Y = 10;
		g_gaster2.m_cLocation.X = 14 - 14 * (g_dElapsedTime - 35);
		g_gaster2.m_bFire = true;
		shootsound = true;
	}
	else if (g_dElapsedTime > 37 && g_dElapsedTime <= 38) // ATTACK 4 (37)
	{

		g_gaster4.m_bActive = true;
		g_gaster4.m_cLocation.Y = 9;
		g_gaster4.m_cLocation.X = g_sChar.m_cLocation.X * (g_dElapsedTime - 39);
		g_gaster2.m_cLocation.X = 15;
		g_gaster2.m_bActive = true;
		g_gaster2.m_cLocation.Y = 24 - 10 * (g_dElapsedTime - 37);
	}
	else if (g_dElapsedTime > 38 && g_dElapsedTime <= 39)
	{
		g_gaster4.m_cLocation.X = g_sChar.m_cLocation.X;
		g_gaster2.m_bFire = true;
		g_gaster3.m_cLocation.X = 66;
		g_gaster3.m_bActive = true;
		g_gaster3.m_cLocation.Y = 21 * (g_dElapsedTime - 38);
		shootsound = true;
	}
	else if (g_dElapsedTime > 39 && g_dElapsedTime <= 40)
	{
		g_gaster1.m_bActive = true;
		g_gaster1.m_cLocation.Y = 9;
		g_gaster4.m_cLocation.X = g_sChar.m_cLocation.X;
		g_gaster3.m_bFire = true;
		g_gaster1.m_cLocation.X = 20 * (g_dElapsedTime - 39);
		g_gaster3.m_cLocation.Y = 21 - 2 * (g_dElapsedTime - 39);
		g_gaster2.m_cLocation.Y = 14 + 2 * (g_dElapsedTime - 39);
		shootsound = true;
	}
	else if (g_dElapsedTime > 40 && g_dElapsedTime <= 43)
	{
		g_gaster4.m_cLocation.X = g_sChar.m_cLocation.X;
		g_gaster1.m_bFire = true;
		g_gaster1.m_cLocation.X = 20 + 10 * (g_dElapsedTime - 40);
		shootsound = true;
	}
	else if (g_dElapsedTime > 43 && g_dElapsedTime <= 45)
	{
		g_gaster4.m_cLocation.X = g_sChar.m_cLocation.X;
		g_gaster1.m_bFire = true;
		g_gaster1.m_cLocation.X = 50 - 30 * (g_dElapsedTime - 43);
		shootsound = true;
	}
	else if (g_dElapsedTime > 45 && g_dElapsedTime <= 46)
	{
		g_gaster4.m_cLocation.Y = 10;
		g_gaster2.m_cLocation.Y = 16 - 3 * (g_dElapsedTime - 45);
		g_gaster3.m_cLocation.Y = 19 + 3 * (g_dElapsedTime - 45);
		shootsound = true;
	}
	else if (g_dElapsedTime > 46 && g_dElapsedTime <= 47)
	{
		g_gaster4.m_cLocation.Y = 10 - 10 * (g_dElapsedTime - 46);
		g_gaster4.m_bFire = true;
		g_gaster2.m_cLocation.X = 15 - 15 * (g_dElapsedTime - 46);
		g_gaster3.m_cLocation.X = 66 + 15 * (g_dElapsedTime - 46);
		shootsound = true;
	}
	else if (g_dElapsedTime > 48 && g_dElapsedTime <= 49) // ATTACK 5 (48)
	{
		g_gaster1.m_cLocation.X = 20;
		g_gaster4.m_cLocation.X = 60;
		g_gaster1.m_bActive = true;
		g_gaster4.m_bActive = true;
		g_gaster1.m_cLocation.Y = 10 * (g_dElapsedTime - 48);
		g_gaster4.m_cLocation.Y = 10 * (g_dElapsedTime - 48);
	}
	else if (g_dElapsedTime > 49 && g_dElapsedTime <= 51)
	{
		g_gaster1.m_cLocation.X = 20 + 9 * (g_dElapsedTime - 49);
		g_gaster4.m_cLocation.X = 61 - 9 * (g_dElapsedTime - 49);
		g_gaster1.m_bFire = true;
		g_gaster4.m_bFire = true;
		shootsound = true;
	}
	else if (g_dElapsedTime > 51 && g_dElapsedTime <= 52)
	{
		g_gaster1.m_cLocation.X = 37;
		g_gaster4.m_cLocation.X = 43;
		g_gaster1.m_bFire = true;
		g_gaster4.m_bFire = true;
		g_gaster2.m_bActive = true;
		g_gaster2.m_bFire = true;
		g_gaster2.m_cLocation.X = 15;
		g_gaster2.m_cLocation.Y = 24 - 7 * (g_dElapsedTime - 51);
		shootsound = true;
	}
	else if (g_dElapsedTime > 52 && g_dElapsedTime <= 53)
	{
		g_gaster1.m_bFire = true;
		g_gaster4.m_bFire = true;
		shootsound = true;
	}
	else if (g_dElapsedTime > 53 && g_dElapsedTime <= 54)
	{
		g_gaster1.m_cLocation.X = 37 - 10 * (g_dElapsedTime - 53);
		shootsound = true;
	}
	else if (g_dElapsedTime > 54 && g_dElapsedTime <= 55)
	{
		g_gaster4.m_cLocation.X = 43 - 10 * (g_dElapsedTime - 54);
		shootsound = true;
	}
	else if (g_dElapsedTime > 55 && g_dElapsedTime <= 56)
	{
		g_gaster2.m_cLocation.Y = 17 + 3 * (g_dElapsedTime - 55);
		g_gaster3.m_bActive = true;
		g_gaster3.m_cLocation.Y = 10;
		g_gaster3.m_cLocation.X = 81 - 15 * (g_dElapsedTime - 55);
		shootsound = true;
	}
	else if (g_dElapsedTime > 56 && g_dElapsedTime <= 57)
	{
		g_gaster2.m_cLocation.Y = 20;
		g_gaster3.m_bFire = true;
		g_gaster3.m_cLocation.Y = 10 + 5 * (g_dElapsedTime - 56);
		g_gaster3.m_cLocation.X = 66;
		shootsound = true;
	}
	else if (g_dElapsedTime > 57 && g_dElapsedTime <= 57.5)
	{
		g_gaster4.m_cLocation.X = 34;
		g_gaster1.m_cLocation.X = 26;
		g_gaster2.m_cLocation.Y = 21;
		g_gaster3.m_cLocation.Y = 14;
		shootsound = true;
	}
	else if (g_dElapsedTime > 57.5 && g_dElapsedTime <= 58.5)
	{
		g_gaster4.m_cLocation.X = 34 + 5 * (g_dElapsedTime - 57.5);
		g_gaster1.m_cLocation.X = 26 + 5 * (g_dElapsedTime - 57.5);
		shootsound = true;
	}
	else if (g_dElapsedTime > 58.5 && g_dElapsedTime <= 59.5)
	{
		g_gaster4.m_cLocation.X = 39 + 5 * (g_dElapsedTime - 58.5);
		g_gaster1.m_cLocation.X = 31 + 5 * (g_dElapsedTime - 58.5);
		g_gaster2.m_cLocation.Y = 21 + 3 * (g_dElapsedTime - 58.5);
		g_gaster3.m_cLocation.Y = 14 + 3 * (g_dElapsedTime - 58.5);
		shootsound = true;
	}
	else if (g_dElapsedTime > 59.5 && g_dElapsedTime <= 60.5)
	{
		g_gaster4.m_cLocation.X = 44;
		g_gaster1.m_cLocation.X = 36;
		g_gaster2.m_cLocation.Y = 24 - 3 * (g_dElapsedTime - 59.5);
		g_gaster3.m_cLocation.Y = 17 - 3 * (g_dElapsedTime - 59.5);
		shootsound = true;
	}
	else if (g_dElapsedTime > 60.5 && g_dElapsedTime <= 61.5)
	{
		g_gaster2.m_cLocation.Y = 21 + 4 * (g_dElapsedTime - 60.5);
		g_gaster3.m_cLocation.Y = 14 + 4 * (g_dElapsedTime - 60.5);
		shootsound = true;
	}
	else if (g_dElapsedTime > 61.5 && g_dElapsedTime <= 62.5)
	{
		g_gaster2.m_cLocation.Y = 25 - 5 * (g_dElapsedTime - 61.5);
		g_gaster3.m_cLocation.Y = 18 - 5 * (g_dElapsedTime - 61.5);
		shootsound = true;
	}
	else if (g_dElapsedTime > 62.5 && g_dElapsedTime <= 63.5)
	{
		g_gaster2.m_cLocation.X = 15 - 15 * (g_dElapsedTime - 62.5);
		g_gaster3.m_cLocation.X = 66 + 15 * (g_dElapsedTime - 62.5);
		g_gaster1.m_cLocation.Y = 10 - 10 * (g_dElapsedTime - 62.5);
		g_gaster4.m_cLocation.Y = 10 - 10 * (g_dElapsedTime - 62.5);
		shootsound = true;
	}
	else if (g_dElapsedTime > 72 && g_dElapsedTime <= 73) // ATTACK 6 (72)
	{
		g_gaster1.m_bActive = true;
		g_gaster2.m_bActive = true;
		g_gaster3.m_bActive = true;
		g_gaster4.m_bActive = true;
		g_gaster2.m_cLocation.X = 15 * (g_dElapsedTime - 72);
		g_gaster3.m_cLocation.X = 81 - 15 * (g_dElapsedTime - 72);
		g_gaster1.m_cLocation.Y = 10 * (g_dElapsedTime - 72);
		g_gaster4.m_cLocation.Y = 10 * (g_dElapsedTime - 72);
		g_gaster2.m_cLocation.Y = g_sChar.m_cLocation.Y + 4;
		g_gaster3.m_cLocation.Y = g_sChar.m_cLocation.Y - 4;
		g_gaster1.m_cLocation.X = g_sChar.m_cLocation.X + 4;
		g_gaster4.m_cLocation.X = g_sChar.m_cLocation.X - 4;
	}
	else if (g_dElapsedTime > 73 && g_dElapsedTime <= 73.5)
	{
		g_gaster1.m_bFire = true;
		g_gaster2.m_bFire = true;
		g_gaster3.m_bFire = true;
		g_gaster4.m_bFire = true;
		g_gaster2.m_cLocation.Y = g_sChar.m_cLocation.Y + 4;
		g_gaster3.m_cLocation.Y = g_sChar.m_cLocation.Y - 4;
		g_gaster1.m_cLocation.X = g_sChar.m_cLocation.X + 4;
		g_gaster4.m_cLocation.X = g_sChar.m_cLocation.X - 4;
		shootsound = true;
	}
	else if (g_dElapsedTime > 73.5 && g_dElapsedTime <= 80)
	{
		int randomone, randomtwo, randomthree, randomfour;
		if (rand() % 2)
			randomone = 3;
		else
			randomone = 4;
		if (rand() % 2)
			randomtwo = 3;
		else
			randomtwo = 4;
		if (rand() % 2)
			randomthree = 3;
		else
			randomthree = 4;
		if (rand() % 2)
			randomfour = 3;
		else
			randomfour = 4;
		g_gaster2.m_cLocation.Y = g_sChar.m_cLocation.Y + randomone;
		g_gaster3.m_cLocation.Y = g_sChar.m_cLocation.Y - randomtwo;
		g_gaster1.m_cLocation.X = g_sChar.m_cLocation.X + randomthree;
		g_gaster4.m_cLocation.X = g_sChar.m_cLocation.X - randomfour;
		shootsound = true;
	}
	else if (g_dElapsedTime > 80 && g_dElapsedTime <= 85)
	{
		g_gaster1.m_bFire = false;
		g_gaster2.m_bFire = false;
		g_gaster3.m_bFire = false;
		g_gaster4.m_bFire = false;
		g_gaster2.m_cLocation.Y = g_sChar.m_cLocation.Y;
		g_gaster3.m_cLocation.Y = g_sChar.m_cLocation.Y;
		g_gaster1.m_cLocation.X = g_sChar.m_cLocation.X;
		g_gaster4.m_cLocation.X = g_sChar.m_cLocation.X;
	}
	else if (g_dElapsedTime > 87)
	{
		g_door.m_bActive = true;
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


	if (g_abKeyPressed[K_W] && g_sChar.m_cLocation.Y > 0)
	{
		if (SansFightMap[g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 80 - 80] == ' ')
		{
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_A] && g_sChar.m_cLocation.X > 0)
	{
		if (SansFightMap[g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 80 - 1] == ' ')
		{
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_S] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		if (SansFightMap[g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 80 + 80] == ' ')
		{
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_D] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		if (SansFightMap[g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 80 + 1] == ' ')
		{
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
	}
	if (((g_sChar.m_cLocation.X == g_gaster1.m_cLocation.X - 1 || g_sChar.m_cLocation.X == g_gaster1.m_cLocation.X || g_sChar.m_cLocation.X == g_gaster1.m_cLocation.X + 1) && g_gaster1.m_bFire) ||
		((g_sChar.m_cLocation.Y == g_gaster2.m_cLocation.Y - 1 || g_sChar.m_cLocation.Y == g_gaster2.m_cLocation.Y || g_sChar.m_cLocation.Y == g_gaster2.m_cLocation.Y + 1) && g_gaster2.m_bFire) ||
		((g_sChar.m_cLocation.Y == g_gaster3.m_cLocation.Y - 1 || g_sChar.m_cLocation.Y == g_gaster3.m_cLocation.Y || g_sChar.m_cLocation.Y == g_gaster3.m_cLocation.Y + 1) && g_gaster3.m_bFire) ||
		((g_sChar.m_cLocation.X == g_gaster4.m_cLocation.X - 1 || g_sChar.m_cLocation.X == g_gaster4.m_cLocation.X || g_sChar.m_cLocation.X == g_gaster4.m_cLocation.X + 1) && g_gaster4.m_bFire))
	{
		g_sChar.m_bActive = false;
		bSomethingHappened = true;
	}
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
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character

	if (g_abKeyPressed[K_W] && g_sChar.m_cLocation.Y > 0)
	{
		if (SansMap[g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 80 - 80] == ' ')
		{
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_A] && g_sChar.m_cLocation.X > 0)
	{
		if (SansMap[g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 80 - 1] == ' ')
		{
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_S] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		if (SansMap[g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 80 + 80] == ' ')
		{
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_D] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		if (SansMap[g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 80 + 1] == ' ')
		{
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.07; // 125ms should be enough
	}
}
void moveCharacter()
{
	if ((g_abKeyPressed[K_UP] || g_abKeyPressed[K_DOWN] || g_abKeyPressed[K_LEFT] || g_abKeyPressed[K_RIGHT]) && (g_eWeaponState != Hold || Weapons[currentWeapon].Clip == 0) && currentWeapon)
	{
		shootfailsound = true;
	}
	if (Weapons[currentWeapon].Clip > 0)
	{
		if (g_abKeyPressed[K_UP] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireUp;
			g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			shootsound = true;
			if (currentWeapon)
				Weapons[currentWeapon].Clip--;
		}
		if (g_abKeyPressed[K_DOWN] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireDown;
			g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			shootsound = true;
			if (currentWeapon)
				Weapons[currentWeapon].Clip--;
		}
		if (g_abKeyPressed[K_LEFT] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireLeft;
			g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			shootsound = true;
			if (currentWeapon)
				Weapons[currentWeapon].Clip--;
		}
		if (g_abKeyPressed[K_RIGHT] && g_eWeaponState == Hold)
		{
			g_eWeaponState = FireRight;
			g_weapon.m_cLocation.X = g_sChar.m_cLocation.X;
			g_weapon.m_cLocation.Y = g_sChar.m_cLocation.Y;
			shootsound = true;
			if (currentWeapon)
				Weapons[currentWeapon].Clip--;
		}
	}
	if (g_eWeaponState == FireUp)
	{
		if (Map[g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 80 - 80] == ' ')
		{
			g_weapon.m_cLocation.Y--;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireDown)
	{
		if (Map[g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 80 + 80] == ' ')
		{
			g_weapon.m_cLocation.Y++;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireLeft)
	{
		if (Map[g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 80 - 1] == ' ')
		{
			g_weapon.m_cLocation.X--;
			g_shootdist++;
		}
		else
			g_shootdist = g_shootmaxdist;
	}
	if (g_eWeaponState == FireRight)
	{
		if (Map[g_weapon.m_cLocation.X + g_weapon.m_cLocation.Y * 80 + 1] == ' ')
		{
			g_weapon.m_cLocation.X++;
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

	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character

	if (g_abKeyPressed[K_W] && g_sChar.m_cLocation.Y > 0)
	{
		if (Map[g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 80 - 80] == ' ')
		{
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_A] && g_sChar.m_cLocation.X > 0)
	{
		if (Map[g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 80 - 1] == ' ')
		{
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_S] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		if (Map[g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 80 + 80] == ' ')
		{
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_D] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		if (Map[g_sChar.m_cLocation.X + g_sChar.m_cLocation.Y * 80 + 1] == ' ')
		{
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_E])
	{
		if (currentWeapon < 1 && !Weapon1 && !Weapon2)
			currentWeapon = 1;
		else if (currentWeapon == 1 && !Weapon1 && !Weapon2)
			currentWeapon = 0;
		else if (currentWeapon == 1 && Weapon1 && !Weapon2)
			currentWeapon = 2;
		else if (currentWeapon == 1 && !Weapon1 && Weapon2)
			currentWeapon = 3;
		else if (currentWeapon == 2 && !Weapon2)
			currentWeapon = 0;
		else if (currentWeapon == 2 && Weapon2)
			currentWeapon = 3;
		else if (currentWeapon < 3)
			currentWeapon++;
		else
			currentWeapon = 0;
		g_shootmaxdist = Weapons[currentWeapon].Range;
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
	size_t rate = 100 / (stages + 1) + 100;
	switch (rand() % rate)
	{
	case 0:
		if (g_enemy1.m_bActive == true && Map[g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 80 + 1] == ' ')
			g_enemy1.m_cLocation.X++;
		break;
	case 1:
		if (g_enemy1.m_bActive == true && Map[g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 80 + 80] == ' ')
			g_enemy1.m_cLocation.Y++;
		break;
	case 2:
		if (g_enemy1.m_bActive == true && Map[g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 80 - 1] == ' ')
			g_enemy1.m_cLocation.X--;
		break;
	case 3:
		if (g_enemy1.m_bActive == true && Map[g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 80 - 80] == ' ')
			g_enemy1.m_cLocation.Y--;
		break;
	case 4:
		if (g_enemy2.m_bActive == true && Map[g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 80 + 1] == ' ')
			g_enemy2.m_cLocation.X++;
		break;
	case 5:
		if (g_enemy2.m_bActive == true && Map[g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 80 + 80] == ' ')
			g_enemy2.m_cLocation.Y++;
		break;
	case 6:
		if (g_enemy2.m_bActive == true && Map[g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 80 - 1] == ' ')
			g_enemy2.m_cLocation.X--;
		break;
	case 7:
		if (g_enemy2.m_bActive == true && Map[g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 80 - 80] == ' ')
			g_enemy2.m_cLocation.Y--;
		break;
	case 8:
		if (g_enemy3.m_bActive == true && Map[g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 80 + 1] == ' ')
			g_enemy3.m_cLocation.X++;
		break;
	case 9:
		if (g_enemy3.m_bActive == true && Map[g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 80 + 80] == ' ')
			g_enemy3.m_cLocation.Y++;
		break;
	case 10:
		if (g_enemy3.m_bActive == true && Map[g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 80 - 1] == ' ')
			g_enemy3.m_cLocation.X--;
		break;
	case 11:
		if (g_enemy3.m_bActive == true && Map[g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 80 - 80] == ' ')
			g_enemy3.m_cLocation.Y--;
		break;
	case 12:
		if (g_enemy4.m_bActive == true && Map[g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 80 + 1] == ' ')
			g_enemy4.m_cLocation.X++;
		break;
	case 13:
		if (g_enemy4.m_bActive == true && Map[g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 80 + 80] == ' ')
			g_enemy4.m_cLocation.Y++;
		break;
	case 14:
		if (g_enemy4.m_bActive == true && Map[g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 80 - 1] == ' ')
			g_enemy4.m_cLocation.X--;
		break;
	case 15:
		if (g_enemy4.m_bActive == true && Map[g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 80 - 80] == ' ')
			g_enemy4.m_cLocation.Y--;
		break;
	case 16:
		if (g_enemy5.m_bActive == true && Map[g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 80 + 1] == ' ')
			g_enemy5.m_cLocation.X++;
		break;
	case 17:
		if (g_enemy5.m_bActive == true && Map[g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 80 + 80] == ' ')
			g_enemy5.m_cLocation.Y++;
		break;
	case 18:
		if (g_enemy5.m_bActive == true && Map[g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 80 - 1] == ' ')
			g_enemy5.m_cLocation.X--;
		break;
	case 19:
		if (g_enemy5.m_bActive == true && Map[g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 80 - 80] == ' ')
			g_enemy5.m_cLocation.Y--;
		break;
	case 20:
		if (g_enemy6.m_bActive == true && Map[g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 80 + 1] == ' ')
			g_enemy6.m_cLocation.X++;
		break;
	case 21:
		if (g_enemy6.m_bActive == true && Map[g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 80 + 80] == ' ')
			g_enemy6.m_cLocation.Y++;
		break;
	case 22:
		if (g_enemy6.m_bActive == true && Map[g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 80 - 1] == ' ')
			g_enemy6.m_cLocation.X--;
		break;
	case 23:
		if (g_enemy6.m_bActive == true && Map[g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 80 - 80] == ' ')
			g_enemy6.m_cLocation.Y--;
		break;
	}
	if (g_weapon.m_cLocation.Y == g_enemy1.m_cLocation.Y && g_enemy1.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 5)
		{
		case 0:
			if (Map[g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 80 + 80] == ' ')
				g_enemy1.m_cLocation.X++;
			else
				g_enemy1.m_cLocation.X--;

			break;
		case 1:
			if (Map[g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 80 - 80] == ' ')
				g_enemy1.m_cLocation.X--;
			else
				g_enemy1.m_cLocation.X++;
			break;
		}
	}
	else if (g_weapon.m_cLocation.X == g_enemy1.m_cLocation.X && g_enemy1.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 5)
		{
		case 0:
			if (Map[g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 80 + 1] == ' ')
				g_enemy1.m_cLocation.Y++;
			else
				g_enemy1.m_cLocation.Y--;
			break;
		case 1:
			if (Map[g_enemy1.m_cLocation.X + g_enemy1.m_cLocation.Y * 80 - 1] == ' ')
				g_enemy1.m_cLocation.Y--;
			else
				g_enemy1.m_cLocation.Y--;
			break;
		}
	}
	if (g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y && g_enemy2.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 5)
		{
		case 0:
			if (Map[g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 80 + 1] == ' ')
				g_enemy2.m_cLocation.X++;
			else
				g_enemy2.m_cLocation.X--;

			break;
		case 1:
			if (Map[g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 80 - 1] == ' ')
				g_enemy2.m_cLocation.X--;
			else
				g_enemy2.m_cLocation.X++;
			break;
		}
	}
	else if (g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_enemy6.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 5)
		{
		case 0:
			if (Map[g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 80 + 80] == ' ')
				g_enemy2.m_cLocation.Y++;
			else
				g_enemy2.m_cLocation.Y--;
			break;
		case 1:
			if (Map[g_enemy2.m_cLocation.X + g_enemy2.m_cLocation.Y * 80 - 80] == ' ')
				g_enemy2.m_cLocation.Y--;
			else
				g_enemy2.m_cLocation.Y++;
			break;
		}
	}
	if (g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_enemy3.m_bActive == true && !(rand() % 20))
	{
		if (g_sChar.m_cLocation.Y > g_enemy3.m_cLocation.Y)
		{
			if (Map[g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 80 + 80] == ' ')
				g_enemy3.m_cLocation.Y++;
		}
		else
		{
			if (Map[g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 80 - 80] == ' ')
				g_enemy3.m_cLocation.Y--;
		}
	}
	else if (g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y && g_enemy3.m_bActive == true && !(rand() % 20))
	{
		if (g_sChar.m_cLocation.X > g_enemy3.m_cLocation.X)
		{
			if (Map[g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 80 + 1] == ' ')
				g_enemy3.m_cLocation.X++;
		}
		else
		{
			if (Map[g_enemy3.m_cLocation.X + g_enemy3.m_cLocation.Y * 80 - 1] == ' ')
				g_enemy3.m_cLocation.X--;
		}
	}
	if (g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_enemy4.m_bActive == true && !(rand() % 20))
	{
		if (g_sChar.m_cLocation.Y > g_enemy4.m_cLocation.Y)
		{
			if (Map[g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 80 + 80] == ' ')
				g_enemy4.m_cLocation.Y++;
		}
		else
		{
			if (Map[g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 80 - 80] == ' ')
				g_enemy4.m_cLocation.Y--;
		}
	}
	else if (g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y && g_enemy4.m_bActive == true && !(rand() % 20))
	{
		if (g_sChar.m_cLocation.X > g_enemy4.m_cLocation.X)
		{
			if (Map[g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 80 + 1] == ' ')
				g_enemy4.m_cLocation.X++;
		}
		else
		{
			if (Map[g_enemy4.m_cLocation.X + g_enemy4.m_cLocation.Y * 80 - 1] == ' ')
				g_enemy4.m_cLocation.X--;
		}
	}
	if (g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y && g_enemy5.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 5)
		{
		case 0:
			if (Map[g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 80 + 80] == ' ')
				g_enemy5.m_cLocation.X++;
			else
				g_enemy5.m_cLocation.X--;

			break;
		case 1:
			if (Map[g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 80 - 80] == ' ')
				g_enemy5.m_cLocation.X--;
			else
				g_enemy5.m_cLocation.X++;
			break;
		}
	}
	else if (g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_enemy5.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 5)
		{
		case 0:
			if (Map[g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 80 + 1] == ' ')
				g_enemy5.m_cLocation.Y++;
			else
				g_enemy5.m_cLocation.Y--;
			break;
		case 1:
			if (Map[g_enemy5.m_cLocation.X + g_enemy5.m_cLocation.Y * 80 - 1] == ' ')
				g_enemy5.m_cLocation.Y--;
			else
				g_enemy5.m_cLocation.Y--;
			break;
		}
	}
	if (g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y && g_enemy6.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 5)
		{
		case 0:
			if (Map[g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 80 + 80] == ' ')
				g_enemy6.m_cLocation.X++;
			else
				g_enemy6.m_cLocation.X--;

			break;
		case 1:
			if (Map[g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 80 - 80] == ' ')
				g_enemy6.m_cLocation.X--;
			else
				g_enemy6.m_cLocation.X++;
			break;
		}
	}
	else if (g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_enemy6.m_bActive == true)
	{
		switch (rand() % 100 / (int_stages + 1) + 5)
		{
		case 0:
			if (Map[g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 80 + 1] == ' ')
				g_enemy6.m_cLocation.Y++;
			else
				g_enemy6.m_cLocation.Y--;
			break;
		case 1:
			if (Map[g_enemy6.m_cLocation.X + g_enemy6.m_cLocation.Y * 80 - 1] == ' ')
				g_enemy6.m_cLocation.Y--;
			else
				g_enemy6.m_cLocation.Y--;
			break;
		}
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.07; // 125ms should be enough
	}
}
void processUserInput()
{
	if (g_abKeyPressed[K_SPACE] && StageType == EBossBattle && g_dElapsedTime < 20)
		g_dElapsedTime = 20;
	if ((Lives < 1 || g_abKeyPressed[K_ESCAPE]) && g_eGameState != S_SHOP)
	{
		if (g_bMinigame)
		{
			highscoreLoad();
			highscoreSave();
			g_eGameState = S_MINIGAME;
			g_dBounceTime = g_dElapsedTime + 0.125;
			b_play = false;
		}
		else
		{
			g_eGameState = S_GAMEOVER;
			PlaySound(TEXT("sound/dead.wav"), NULL, SND_FILENAME | SND_LOOP);
		}
	}
	if (g_abKeyPressed[K_C])
	{
		g_enemy1.m_bActive = false;
		g_enemy2.m_bActive = false;
		g_enemy3.m_bActive = false;
		g_enemy4.m_bActive = false;
		g_enemy5.m_bActive = false;
		g_enemy6.m_bActive = false;
		if (StageType == EBossBattle)
			g_dElapsedTime = 20;
		if (StageType == EMinigame2)
			g_sChar.m_cLocation.Y = g_weapon.m_cLocation.Y;
	}
	if (g_sChar.m_bActive == false) // Took damage
	{
		g_sChar.m_bActive = true;
		Lives--;
		deathsound = 5;
	}
	if (g_enemy1.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy1.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy1.m_bActive == true && StageType == EStage)
	{
		g_enemy1.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy2.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy2.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy2.m_bActive == true && StageType == EStage)
	{
		g_enemy2.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy3.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy3.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy3.m_bActive == true && StageType == EStage)
	{
		g_enemy3.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy4.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy4.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy4.m_bActive == true && StageType == EStage)
	{
		g_enemy4.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy5.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy5.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy5.m_bActive == true && StageType == EStage)
	{
		g_enemy5.m_bActive = false;
		deathsound = 5;
	}
	if (g_enemy6.m_cLocation.X == g_weapon.m_cLocation.X && g_enemy6.m_cLocation.Y == g_weapon.m_cLocation.Y && g_enemy6.m_bActive == true && StageType == EStage)
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
		StageType == EStage)
	{
		if (int_stages % 5 == 4)
			g_shopkeeper.m_bActive = true;
		else
			g_door.m_bActive = true;

	}
	if (g_door.m_bActive == true && g_sChar.m_cLocation.X == g_door.m_cLocation.X && g_sChar.m_cLocation.Y == g_door.m_cLocation.Y)
	{
		if (StageType == EBoss)
		{
			boss_battle_init();
			StageType = EBossBattle;
		}
		else
		{
			int_stages++;
			stages++;
			if (int_stages == 50)
				StageType = EBoss;
			else if (int_stages % 10 == 0)	
				StageType = EMinigame1;	
			else if (int_stages % 5 == 0)
			{
				StageType = EMinigame2;
				g_bforscore = false;
			}
			else
			{
				if (StageType == EBossBattle || StageType == EMinigame1 || StageType == EMinigame2)
					b_play = false;
				StageType = EStage;
			}
			if (StageType == EBoss)
				boss_init();
			else if (StageType == EMinigame1)	
				minigame1_init();	
			else if (StageType == EMinigame2)	
				minigame2_init();
			else
				init();
			if (Lives != 99)
				Lives++;
			save();
		}
	}
	if (g_shopkeeper.m_bActive == true && g_sChar.m_cLocation.X == g_shopkeeper.m_cLocation.X && g_sChar.m_cLocation.Y == g_shopkeeper.m_cLocation.Y)
	{
		StageType = EShop;
		g_eGameState = S_SHOP;

		g_door.m_bActive = false;

		g_sChar.m_cLocation.X = 0;
		g_sChar.m_cLocation.Y = 0;
		g_shopkeeper.m_bActive = false;
		g_shopkeeper.m_cLocation.X = 0;
		g_shopkeeper.m_cLocation.Y = 0;
	}
	if (StageType == EMiniGameSnake)
	{
		snakeInput();
	}
}
void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x00);
}
void renderIntro()
{
	if (introPage == 0)
	{
		std::vector<char>::iterator it = Scene1.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}
	}
	if (introPage == 1)
	{
		std::vector<char>::iterator it = Scene2.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}
	}
	if (introPage == 2)
	{
		std::vector<char>::iterator it = Scene3.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}
	}
	if (introPage == 3)
	{
		std::vector<char>::iterator it = Scene4.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}
	}
	if (introPage == 4)
	{
		std::vector<char>::iterator it = Scene5.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}
	}
}
void renderSplashScreen()  // renders the splash screen
{
	std::vector<char>::iterator it = Title.begin();
	for (short i = 0; i < 80 * 24; ++i)
	{
		g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
	}
	COORD m = g_Console.getConsoleSize();
	switch (MMSelect)
	{
	case MMStart:
		m.Y = 20;
		m.X = 27;
		g_Console.writeToBuffer(m, (char)3, 0x0E);
		m.X += 2;
		g_Console.writeToBuffer(m, "Start", 0x0E);
		m.X = 46;
		g_Console.writeToBuffer(m, "Continue", 0x03);
		m.Y += 1;
		m.X = 26;
		g_Console.writeToBuffer(m, "Instructions", 0x03);
		m.X = 44;
		g_Console.writeToBuffer(m, "LeaderBoard", 0x03);
		m.Y += 1;
		m.X = 27;
		g_Console.writeToBuffer(m, "Minigames", 0x03);
		m.X = 47;
		g_Console.writeToBuffer(m, "Exit", 0x03);
		break;

	case MMInstructions:
		m.Y = 20;
		m.X = 29;
		g_Console.writeToBuffer(m, "Start", 0x03);
		m.X = 46;
		g_Console.writeToBuffer(m, "Continue", 0x03);
		m.Y += 1;
		m.X = 24;
		g_Console.writeToBuffer(m, (char)3, 0x0E);
		m.X += 2;
		g_Console.writeToBuffer(m, "Instructions", 0x0E);
		m.X = 44;
		g_Console.writeToBuffer(m, "LeaderBoard", 0x03);
		m.Y += 1;
		m.X = 27;
		g_Console.writeToBuffer(m, "Minigames", 0x03);
		m.X = 47;
		g_Console.writeToBuffer(m, "Exit", 0x03);
		break;

	case MMExit:
		m.Y = 20;
		m.X = 29;
		g_Console.writeToBuffer(m, "Start", 0x03);
		m.X = 46;
		g_Console.writeToBuffer(m, "Continue", 0x03);
		m.Y += 1;
		m.X = 26;
		g_Console.writeToBuffer(m, "Instructions", 0x03);
		m.X = 44;
		g_Console.writeToBuffer(m, "LeaderBoard", 0x03);
		m.Y += 1;
		m.X = 27;
		g_Console.writeToBuffer(m, "Minigames", 0x03);
		m.X = 45;
		g_Console.writeToBuffer(m, (char)3, 0x0E);
		m.X += 2;;
		g_Console.writeToBuffer(m, "Exit", 0x0E);
		break;

	case MMContinue:
		m.Y = 20;
		m.X = 29;
		g_Console.writeToBuffer(m, "Start", 0x03);
		m.X = 44;
		g_Console.writeToBuffer(m, (char)3, 0x0E);
		m.X += 2;
		g_Console.writeToBuffer(m, "Continue", 0x0E);
		m.Y += 1;
		m.X = 26;
		g_Console.writeToBuffer(m, "Instructions", 0x03);
		m.X = 44;
		g_Console.writeToBuffer(m, "LeaderBoard", 0x03);
		m.Y += 1;
		m.X = 27;
		g_Console.writeToBuffer(m, "Minigames", 0x03);
		m.X = 47;
		g_Console.writeToBuffer(m, "Exit", 0x03);
		break;

	case MMminigame:
		m.Y = 20;
		m.X = 29;
		g_Console.writeToBuffer(m, "Start", 0x03);
		m.X = 46;
		g_Console.writeToBuffer(m, "Continue", 0x03);
		m.Y += 1;
		m.X = 26;
		g_Console.writeToBuffer(m, "Instructions", 0x03);
		m.X = 44;
		g_Console.writeToBuffer(m, "LeaderBoard", 0x03);
		m.Y += 1;
		m.X = 25;
		g_Console.writeToBuffer(m, (char)3, 0x0E);
		m.X += 2;
		g_Console.writeToBuffer(m, "Minigames", 0x0E);
		m.X = 47;
		g_Console.writeToBuffer(m, "Exit", 0x03);
		break;

	case MMHighscore:
		m.Y = 20;
		m.X = 29;
		g_Console.writeToBuffer(m, "Start", 0x03);
		m.X = 46;
		g_Console.writeToBuffer(m, "Continue", 0x03);
		m.Y += 1;
		m.X = 26;
		g_Console.writeToBuffer(m, "Instructions", 0x03);
		m.X = 42;
		g_Console.writeToBuffer(m, (char)3, 0x0E);
		m.X += 2;
		g_Console.writeToBuffer(m, "LeaderBoard", 0x0E);
		m.Y += 1;
		m.X = 27;
		g_Console.writeToBuffer(m, "Minigames", 0x03);
		m.X = 47;
		g_Console.writeToBuffer(m, "Exit", 0x03);
		break;
	}
}
void renderGame()
{
	renderMap();        // renders the map to the buffer first
	renderDoor();
	if (StageType == EStage)
	{
		renderEnemy1();
		renderEnemy2();
		renderEnemy3();
		renderEnemy4();
		renderEnemy5();
		renderEnemy6();
		renderWeapon();
		renderShopkeeper();
	}
	if (StageType == EBossBattle)
	{
		renderBossSpeech();
		renderGaster1();
		renderGaster2();
		renderGaster3();
		renderGaster4();
	}
	if (StageType == EMinigame1)
	{
		renderbeat1();
		renderbeat2();
		renderbeat3();
		renderbeat4();
		renderWeapon();
	}
	if (StageType == EMinigame2)
	{
		renderpaddle1();
		renderpaddle2();
		renderWeapon();
	}
	if (StageType == EMiniGameSnake)
	{
		renderSnake();
		renderApple();
		renderUI();
	}
	if (StageType == ETicTacToe || StageType == ETicTacToe2)
		renderTicTacToe();
	else
		renderCharacter();  // renders the character into the buffer
	if (!g_bMinigame)
	renderUI();
	
	
}
void renderMap()
{
	if (StageType == EStage)
	{
		std::vector<char>::iterator it = Map.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}
	}
	else if (StageType == EBoss)
	{
		std::vector<char>::iterator it = SansMap.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}
	}
	else if (StageType == EBossBattle)
	{
		std::vector<char>::iterator it = SansFightMap.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}
	}
	else if (StageType == EMinigame1)
	{
		std::vector<char>::iterator it = Minigame1Map.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}
	}
	else if (StageType == EMinigame2)
	{
		std::vector<char>::iterator it = Minigame2Map.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}
	}

	else if (StageType == EMiniGameSnake)
	{
		std::vector<char>::iterator it = SnakeMap.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}

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
	UI.X = g_Console.getConsoleSize().X / 3 - 15; // Start of UI text
	g_Console.writeToBuffer(UI, "Lives : ", 0x9f);

	UI.X = g_Console.getConsoleSize().X / 4 - 1;
	std::string display = std::to_string(Lives);
	g_Console.writeToBuffer(UI, display, 0x9f); // Displays the number of lives

	UI.X = g_Console.getConsoleSize().X / 3 - 3;
	g_Console.writeToBuffer(UI, "Weapon : ", 0x9f);
	UI.X = UI.X + 9;
	g_Console.writeToBuffer(UI, Weapons[currentWeapon].Name, 0x9f); // Display Equipped Weapon

	UI.X = UI.X + Weapons[currentWeapon].Name.length() + 3; // Increases UI.X by text length of weapon's name
	g_Console.writeToBuffer(UI, "Ammo : ", 0x9f);

	UI.X = UI.X + 7;
	display = std::to_string(Weapons[currentWeapon].Clip);
	g_Console.writeToBuffer(UI, display, 0x9f); // Display Current Clip

	UI.X += 6; // Increases UI.X by 
	g_Console.writeToBuffer(UI, "Coin : ", 0x9f);

	UI.X = UI.X + 6;
	display = std::to_string(Coin);
	g_Console.writeToBuffer(UI, display, 0x9f); // Display Current Coin
	
	UI.X += 6;
	g_Console.writeToBuffer(UI, "Stage ", 0x9f);

	UI.X = UI.X + 6;
	display = std::to_string(int_stages);
	g_Console.writeToBuffer(UI, display, 0x9f); // Display Current Stage
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
				for (size_t i = g_gaster3.m_cLocation.X - 1; i > 0; i--)
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
void renderbeat1()
{
	WORD charColor = 0x0E;
	char character = '<';
	if (g_minigame1_beat1.m_bLeft)
		character = '>';
	if (g_minigame1_beat1.m_bActive)
	{
		g_Console.writeToBuffer(g_minigame1_beat1.m_cLocation, character, charColor);
	}
}
void renderbeat2()
{
	WORD charColor = 0x0E;
	char character = '<';
	if (g_minigame1_beat2.m_bLeft)
		character = '>';
	if (g_minigame1_beat2.m_bActive)
	{
		g_Console.writeToBuffer(g_minigame1_beat2.m_cLocation, character, charColor);
	}
}
void renderbeat3()
{
	WORD charColor = 0x0E;
	char character = '<';
	if (g_minigame1_beat3.m_bLeft)
		character = '>';
	if (g_minigame1_beat3.m_bActive)
	{
		g_Console.writeToBuffer(g_minigame1_beat3.m_cLocation, character, charColor);
	}
}
void renderbeat4()
{
	WORD charColor = 0x0E;
	char character = '<';
	if (g_minigame1_beat4.m_bLeft)
		character = '>';
	if (g_minigame1_beat4.m_bActive)
	{
		g_Console.writeToBuffer(g_minigame1_beat4.m_cLocation, character, charColor);
	}
}
void renderpaddle1()
{
	WORD charColor = 0x0A;
	char character = 186;
	if (g_minigame2_paddle1.m_bActive)
	{
		COORD c;
		for (size_t i = 0; i < 5; i++)
		{
			c.X = g_minigame2_paddle1.m_cLocation.X;
			c.Y = g_minigame2_paddle1.m_cLocation.Y + i - 2;
			g_Console.writeToBuffer(c, character, charColor);
		}

	}
}
void renderpaddle2()
{
	WORD charColor = 0x0C;
	char character = 186;
	if (g_minigame2_paddle2.m_bActive)
	{
		COORD c;
		for (size_t i = 0; i < 5; i++)
		{
			c.X = g_minigame2_paddle2.m_cLocation.X;
			c.Y = g_minigame2_paddle2.m_cLocation.Y + i - 2;
			g_Console.writeToBuffer(c, character, charColor);
		}

	}
}						
void renderDoor()
{
	// Draw the location of the door
	WORD charColor = 0x0B;
	if (g_door.m_bActive)
		g_Console.writeToBuffer(g_door.m_cLocation, (char)'D', charColor);
}
void renderShopkeeper()
{
	// Draw the location of the moving shopkeeper
	WORD charColor = 0x0D;
	if (g_shopkeeper.m_bActive == true)
		g_Console.writeToBuffer(g_shopkeeper.m_cLocation, (char)'S', charColor);
}
void renderWeapon()
{
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
	else if (g_dElapsedTime > 6 && g_dElapsedTime <= 9)
	{
		char text[] = "You've made it this far.";
		for (short i = 0; i < 24; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 12 + 60, i / 12 + 6 }, text[i % 24], 0x0F);
		}
	}
	else if (g_dElapsedTime > 10 && g_dElapsedTime <= 14)
	{
		char text[] = "I am the one who destroyed your town.";
		for (short i = 0; i < 37; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 13 + 60, i / 13 + 6 }, text[i % 37], 0x0F);
		}
	}
	else if (g_dElapsedTime > 15 && g_dElapsedTime <= 18)
	{
		char text[] = "I assume you'rehere to destroyme too.";
		for (short i = 0; i < 37; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 15 + 59, i / 15 + 6 }, text[i % 37], 0x0F);
		}
	}
	else if (g_dElapsedTime > 19 && g_dElapsedTime <= 21)
	{
		char text[] = "Not if I canhelp it!";
		for (short i = 0; i < 20; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 12 + 60, i / 12 + 6 }, text[i % 20], 0x0C);
		}
	}
	else if ((g_dElapsedTime > 23.5 && g_dElapsedTime <= 25.5))
	{
		char text[] = "Whoa... You    have fast feet!";
		for (short i = 0; i < 30; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 15 + 60, i / 15 + 6 }, text[i % 30], 0x0F);
		}
	}
	else if ((g_dElapsedTime > 29 && g_dElapsedTime <= 31))
	{
		char text[] = "Let's see if youcan dodge this!";
		for (short i = 0; i < 31; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 16 + 59, i / 16 + 6 }, text[i % 31], 0x0F);
		}
	}
	else if ((g_dElapsedTime > 36 && g_dElapsedTime <= 38))
	{
		char text[] = "Don't make me use my SPECIAL ATTACK!";
		for (short i = 0; i < 36; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 18 + 58, i / 18 + 6 }, text[i % 36], 0x0F);
		}
	}
	else if ((g_dElapsedTime > 47 && g_dElapsedTime <= 49))
	{
		char text[] = "Live this and Iwill use my    SPECIAL ATTACK!";
		for (short i = 0; i < 45; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 15 + 59, i / 15 + 6 }, text[i % 45], 0x0F);
		}
	}
	else if ((g_dElapsedTime > 63.5 && g_dElapsedTime <= 65))
	{
		char text[] = "Huff... Puff...";
		for (short i = 0; i < 15; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 15 + 59, i / 15 + 7 }, text[i % 15], 0x0F);
		}
	}
	else if ((g_dElapsedTime > 66 && g_dElapsedTime <= 69.5))
	{
		char text[] = "My SPECIAL ATTACK  is so strong that  I may die using it.";
		for (short i = 0; i < 57; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 19 + 57, i / 19 + 6 }, text[i % 57], 0x0F);
		}
	}
	else if ((g_dElapsedTime > 69.5 && g_dElapsedTime <= 71))
	{
		char text[] = "It doesn't matter.";
		for (short i = 0; i < 18; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 18 + 58, i / 18 + 7 }, text[i % 18], 0x0F);
		}
	}
	else if ((g_dElapsedTime > 71 && g_dElapsedTime <= 73))
	{
		char text[] = "I WILL STOP YOU!";
		for (short i = 0; i < 16; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 16 + 59, i / 16 + 7 }, text[i % 16], 0x0C);
		}
	}
	else if ((g_dElapsedTime > 75 && g_dElapsedTime <= 80))
	{
		char text[] = "HAHAHAHAHAHAHAHA";
		for (short i = 0; i < 16; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 16 + 59, i / 16 + 7 }, text[i % 16], 0x0C);
		}
	}
	else if ((g_dElapsedTime > 80 && g_dElapsedTime <= 85))
	{
		char text[] = "I've got you now!";
		for (short i = 0; i < 17; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 17 + 59, i / 17 + 7 }, text[i % 17], 0x0C);
		}
	}
	else if ((g_dElapsedTime > 85 && g_dElapsedTime <= 87))
	{
		char text[] = "Ack!";
		for (short i = 0; i < 4; i++)
		{
			g_Console.writeToBuffer(COORD{ i % 4 + 63, i / 4 + 7 }, text[i % 4], 0x0C);
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
void gameOver()
{
	std::vector<char>::iterator it = GameOver.begin();
	for (short i = 0; i < 80 * 24; ++i)
	{
		g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
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
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	if (MMSelect == MMStart && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN] || g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_GAMEOVER) // MENU FOR GAME_OVER
	{
		MMSelect = MMExit;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMExit && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN] || g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_GAMEOVER)
	{
		MMSelect = MMStart;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMExit && g_eGameState == S_GAMEOVER) // QUIT_GAME
	{
		StageType = EMainMenu;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		b_play = false;
		g_eGameState = S_TITLE;
	}
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMStart && g_eGameState == S_GAMEOVER) // CONTINUE_GAME
	{
		StageType = EStage;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		b_play = false;
		init();
		Lives = 3;
		stages = 1;
		Coin = 0;
		int_stages = 1;
		for (size_t i = 1; i < 4; i++)
			Weapons[i].Clip = 0;
		g_eGameState = S_CONTINUE;
	}
	if (bSomethingHappened)
	{
		g_dBounceTime = g_dElapsedTime + 0.125;
	}
}
void shop() {

	std::vector<char>::iterator it = SHOP.begin();
	for (short i = 0; i < 80 * 24; ++i)
	{
		g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
	}
	COORD m = g_Console.getConsoleSize();
	switch (MMSelect)
	{
		//buy lives
	case MMLive:
		m.Y = 17;
		m.X = m.X / 2 - 21;
		g_Console.writeToBuffer(m, "25 Coins: 1 life", 0x0E);


		if (Weapon1 == 0)
		{
			m.Y += 2;
			m.X = g_Console.getConsoleSize().X / 2 - 21;
			g_Console.writeToBuffer(m, "100 Coins: Crossbow", 0x03);
		}
		else
		{
			m.Y += 2;
			m.X = g_Console.getConsoleSize().X / 2 - 21;
			g_Console.writeToBuffer(m, "100 Coins: Crossbow", 0x0D);
		}

		if (Weapon2 == 0)
		{
			m.Y = 17;
			m.X = m.X / 2 + 32;
			g_Console.writeToBuffer(m, "150 Coins: Rifle", 0x03);
		}
		else
		{
			m.Y = 17;
			m.X = m.X / 2 + 32;
			g_Console.writeToBuffer(m, "150 Coins: Rifle", 0x0D);
		}

		m.Y += 2;
		m.X = g_Console.getConsoleSize().X / 2 + 1;
		g_Console.writeToBuffer(m, "Next Level", 0x03);

		break;

		//buy Crossbow
	case MMW1:
		m.Y = 17;
		m.X = m.X / 2 - 21;
		g_Console.writeToBuffer(m, "25 Coins: 1 life", 0x03);

		m.Y += 2;
		m.X = g_Console.getConsoleSize().X / 2 - 21;
		g_Console.writeToBuffer(m, "100 Coins: Crossbow", 0x0E);


		if (Weapon2 == 0)
		{
			m.Y = 17;
			m.X = m.X / 2 + 32;
			g_Console.writeToBuffer(m, "150 Coins: Rifle", 0x03);
		}
		else
		{
			m.Y = 17;
			m.X = m.X / 2 + 32;
			g_Console.writeToBuffer(m, "150 Coins: Rifle", 0x0D);
		}

		m.Y += 2;
		m.X = g_Console.getConsoleSize().X / 2 + 1;
		g_Console.writeToBuffer(m, "Next Level", 0x03);

		break;

		//buy Rifle
	case MMW2:
		m.Y = 17;
		m.X = m.X / 2 - 21;
		g_Console.writeToBuffer(m, "25 Coins: 1 life", 0x03);

		if (Weapon1 == 0)
		{
			m.Y += 2;
			m.X = g_Console.getConsoleSize().X / 2 - 21;
			g_Console.writeToBuffer(m, "100 Coins: Crossbow", 0x03);
		}
		else
		{
			m.Y += 2;
			m.X = g_Console.getConsoleSize().X / 2 - 21;
			g_Console.writeToBuffer(m, "100 Coins: Crossbow", 0x0D);
		}

		m.Y = 17;
		m.X = m.X / 2 + 32;
		g_Console.writeToBuffer(m, "150 Coins: Rifle", 0x0E);

		m.Y += 2;
		m.X = g_Console.getConsoleSize().X / 2 + 1;
		g_Console.writeToBuffer(m, "Next Level", 0x03);

		break;

		//back to game
	case MMBack:
		m.Y = 17;
		m.X = m.X / 2 - 21;
		g_Console.writeToBuffer(m, "25 Coins: 1 life", 0x03);


		if (Weapon1 == 0)
		{
			m.Y += 2;
			m.X = g_Console.getConsoleSize().X / 2 - 21;
			g_Console.writeToBuffer(m, "100 Coins: Crossbow", 0x03);
		}
		else if (Weapon1)
		{
			m.Y += 2;
			m.X = g_Console.getConsoleSize().X / 2 - 21;
			g_Console.writeToBuffer(m, "100 Coins: Crossbow", 0x0D);
		}

		if (Weapon2 == 0)
		{
			m.Y = 17;
			m.X = m.X / 2 + 32;
			g_Console.writeToBuffer(m, "150 Coins: Rifle", 0x03);
		}
		else
		{
			m.Y = 17;
			m.X = m.X / 2 + 32;
			g_Console.writeToBuffer(m, "150 Coins: Rifle", 0x0D);
		}

		m.Y += 2;
		m.X = g_Console.getConsoleSize().X / 2 + 1;
		g_Console.writeToBuffer(m, "Next Level", 0x0E);

		break;
	}

	if (MMSelect == MMLive && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_SHOP)
	{

		if (g_PressedToMove == true)
		{
			g_PressedToMove = false;
			MMSelect = MMW1;
		}
		else if ((g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_PressedToMove == false)
		{
			g_PressedToMove = false;
		}
	}

	else if (MMSelect == MMW1 && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_SHOP)
	{

		if (g_PressedToMove == true)
		{
			g_PressedToMove = false;
			MMSelect = MMLive;
		}
		else if ((g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_PressedToMove == false)
		{
			g_PressedToMove = false;
		}
	}


	else if (MMSelect == MMLive && (g_abKeyPressed[K_D] || g_abKeyPressed[K_RIGHT]) && g_eGameState == S_SHOP)
	{

		if (g_PressedToMove == true)
		{
			g_PressedToMove = false;
			MMSelect = MMW2;
		}
		else if ((g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_PressedToMove == false)
		{
			g_Pressed = false;
		}
	}

	else if (MMSelect == MMW2 && (g_abKeyPressed[K_A] || g_abKeyPressed[K_LEFT]) && g_eGameState == S_SHOP)
	{

		if (g_PressedToMove == true)
		{
			g_PressedToMove = false;
			MMSelect = MMLive;
		}
		else if ((g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_PressedToMove == false)
		{
			g_PressedToMove = false;
		}
	}

	else if (MMSelect == MMW2 && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_SHOP)
	{

		if (g_PressedToMove == true)
		{
			g_PressedToMove = false;
			MMSelect = MMBack;
		}
		else if ((g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_PressedToMove == false)
		{
			g_Pressed = false;
		}
	}

	else if (MMSelect == MMBack && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_SHOP)
	{
		MMSelect = MMW2;
		if (g_PressedToMove == true)
		{
			g_PressedToMove = false;
			MMSelect = MMW2;
		}
		else if ((g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_PressedToMove == false)
		{
			g_PressedToMove = false;
		}
	}

	else if (MMSelect == MMBack && (g_abKeyPressed[K_A] || g_abKeyPressed[K_LEFT]) && g_eGameState == S_SHOP)
	{
		MMSelect = MMW1;
		if (g_PressedToMove == true)
		{
			g_PressedToMove = false;
			MMSelect = MMW1;
		}
		else if ((g_abKeyPressed[K_A] || g_abKeyPressed[K_LEFT]) && g_PressedToMove == false)
		{
			g_PressedToMove = false;
		}
	}

	else if (MMSelect == MMW1 && (g_abKeyPressed[K_D] || g_abKeyPressed[K_RIGHT]) && g_eGameState == S_SHOP)
	{
		MMSelect = MMBack;
		if (g_PressedToMove == true)
		{
			g_PressedToMove = false;
			MMSelect = MMW1;
		}
		else if ((g_abKeyPressed[K_D] || g_abKeyPressed[K_RIGHT]) && g_PressedToMove == false)
		{
			g_PressedToMove = false;
		}
	}

	else 
		g_PressedToMove = true;
	//processUserInput();
	renderUI();
}

void shopoption()
{
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMLive && g_eGameState == S_SHOP) // When pressed Add 1 live
	{
		if (Coin >= 25 && g_Pressed == true)
		{
			Coin -= 25;
			Lives++;
			g_Pressed = false;
		}
		else if (g_abKeyPressed[K_SPACE] && g_Pressed == false)
		{
			g_Pressed = false;
		}
	}
	else {
		g_Pressed = true;
	}

	if (g_abKeyPressed[K_SPACE] && MMSelect == MMW1 && g_eGameState == S_SHOP && Weapon1 == 0) // CONTINUE_GAME
	{
		if (Coin >= 100 && Weapon1 == 0)
		{
			Coin -= 100;
			Weapon1 = 1;
		}
	}

	if (g_abKeyPressed[K_SPACE] && MMSelect == MMW2 && g_eGameState == S_SHOP && Weapon2 == 0) // CONTINUE_GAME
	{
		if (Coin >= 150 && Weapon2 == 0)
		{
			Coin -= 150;
			Weapon2 = 1;
		}
	}

	if (g_abKeyPressed[K_SPACE] && MMSelect == MMBack && g_eGameState == S_SHOP)
	{
		int_stages++;
		stages++;
		if (int_stages == 50)
			StageType = EBoss;
		else if (int_stages % 10 == 0)
			StageType = EMinigame1;
		else if (int_stages % 5 == 0)
		{
			StageType = EMinigame2;
			g_bforscore = false;
		}
		else
		{
			if (StageType == EBossBattle || StageType == EMinigame1 || StageType == EMinigame2)
				b_play = false;
			StageType = EStage;
		}
		if (StageType == EBoss)
			boss_init();
		else if (StageType == EMinigame1)
			minigame1_init();
		else if (StageType == EMinigame2)
			minigame2_init();
		else
			init();
		if (Lives != 99)
			Lives++;
		save();
		g_eGameState = S_CONTINUE;
	}

}
void instructions()
{
	std::vector<char>::iterator it = Instructions.begin();
	for (short i = 0; i < 80 * 24; ++i)
	{
		g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
	}
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_eGameState = S_TITLE;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
	}
}
void sound()
{
	if (deathsound > 0)
	{
		Beep(deathsound * 150, 15);
		deathsound--;
	}
	if (shootsound)
	{
		Beep(1500, 10);
		shootsound = false;
	}
	if (reloadsound > 0)
	{
		Beep((3 - reloadsound) * 450, 15);
		reloadsound--;
	}
	if (shootfailsound)
	{
		Beep(400, 15);
		shootfailsound = false;
	}
	if (minigame1sound)
	{
		Beep(1000, 15);
		minigame1sound = false;
	}
}
void generate()
{
	Map.clear();
	size_t random, point1, point2, point3, point4;
	srand(time(NULL));
	for (size_t i = 0; i < 24; i++)
	{
		if (rand() % 3 && i > 7 && i < 17)
		{
			int random1 = rand() % 20 + 15;
			int random2 = rand() % 20 + 15;
			for (size_t i = 0; i < random1; i++)
				Map.push_back('`');
			for (size_t i = 0; i < 80 - random1 - random2; i++)
				Map.push_back(' ');
			for (size_t i = 0; i < random2; i++)
				Map.push_back('`');
		}
		else
			for (size_t i = 0; i < 80; i++)
				Map.push_back('`');
	}
	random = rand() % 5 + 37;
	for (size_t i = 0; i < 10; i++)
	{
		Map[random + 80 * (i + 7)] = ' ';
		Map[random + 80 * (i + 7) + 1] = ' ';
	}
	point1 = (rand() % 10 + 5) + ((rand() % 2) + 13) * 80;
	random = rand() % 10 + 20;
	point2 = point1 + random;
	for (size_t i = 0; i < random; i++)
	{
		Map[point1 + i] = ' ';
	}
	random = rand() % 4 + 8;
	for (size_t f = 0; f < random; f++)
	{
		if (f > 3)
			for (size_t i = 0; i < random + 5 - f; i++)
			{
				Map[point1 + (4 - f) * 80 + i] = ' ';
			}
		else
			for (size_t i = 0; i < random + 5 + f; i++)
			{
				Map[point1 + (4 - f) * 80 + i] = ' ';
			}
	}
	random = rand() % 5 + 3;
	if (rand() % 2)
	{
		for (size_t f = 0; f < random; f++)
		{
			for (size_t i = 0; i < random + 5 + f; i++)
			{
				Map[point2 + f * 80 - f + i] = ' ';
				point3 = point2 + f * 80 - f + i + 1;
			}
		}
	}
	else
	{
		for (size_t f = 0; f < random; f++)
		{
			for (size_t i = 0; i < random + 8 - f; i++)
			{
				Map[point2 - f * 80 + f + i] = ' ';
				point3 = point2 - f * 80 + f + i + 1;
			}
		}
	}
	random = rand() % 3 + 2;
	for (size_t f = 0; f < random; f++)
	{
		for (size_t i = 0; i < (random * 2) - f; i++)
		{
			Map[point3 - (80 * f) + 2 * f + i] = ' ';
		}
	}
	random = rand() % 3 + 2;
	if (rand() % 2)
		for (size_t i = 0; i < random; i++)
		{
			Map[point1 - 1 + i * 80] = ' ';
			point4 = point1 - 1 + i * 80 + 1;
		}
	else
		for (size_t i = 0; i < random; i++)
		{
			Map[point1 - 1 - i * 80 + 80] = ' ';
			point4 = point1 - 1 - i * 80 + 80 + 1;
		}
	random = rand() % 3;
	if (point4 < Map.size() / 2)
		for (size_t f = 0; f < random; f++)
		{
			for (size_t i = 0; i < random; i++)
			{
				Map[point4 + 80 * f + i] = ' ';
			}
		}
	else
		for (size_t f = 0; f < random; f++)
		{
			for (size_t i = 0; i < random; i++)
			{
				Map[point4 - 80 * f + i] = ' ';
			}
		}
	for (size_t i = 0; i < 80 * 24; i++)
	{
		if (Map[i] == '`' && i > 80 && i < 23 * 80 && ((Map[i - 80] == ' ') || Map[i + 80] == ' '|| Map[i + 1] == ' ' || Map[i - 1] == ' '))
			Map[i] = 219;	
	}
}
void weapdata()
{
	int i = 0;
	std::string in;
	std::ifstream weapondata("weapons.txt");
	getline(weapondata, Weapons[i].Name); // Gets Spear
	weapondata >> Weapons[i].ClipMax;
	weapondata >> Weapons[i].Reload;
	weapondata >> Weapons[i].Range;
	i++;
	weapondata.ignore();
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
	getline(weapondata, Weapons[i].Name); // Gets Rifle
	weapondata >> Weapons[i].ClipMax;
	weapondata >> Weapons[i].Reload;
	weapondata >> Weapons[i].Range;
	i++;
	weapondata.close();
}
void reload()
{
	Coin += 3; //Add Coin
	if (currentWeapon)
		Weapons[currentWeapon].Clip += Weapons[currentWeapon].ClipMax;	// Adds ammo left in clip to total
	else
		Weapons[1].Clip += Weapons[1].ClipMax;
}
void ost()
{
	if (StageType == EMainMenu)
		PlaySound(TEXT("sound/menu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else if (StageType == EStage)
		PlaySound(TEXT("sound/cave.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else if (StageType == EBoss)
		PlaySound(TEXT("sound/boss.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else if (StageType == EMinigame1 || StageType == EMinigame2 || StageType == ETicTacToe || StageType == ETicTacToe2 || StageType == EMiniGameSnake | StageType == EShop)
		PlaySound(TEXT("sound/minigame.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	b_play = true;
}
void convertToString()
{
	std::fstream myfile1("map/bossmap.txt");
	std::string sLine;
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile1.seekg(i);
		char * buffer = new char[1];
		myfile1.read(buffer, 1);
		if (buffer[0] != '\n')
			SansMap.push_back(buffer[0]);
	}
	myfile1.close();
	std::fstream myfile2("map/bossscreen.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile2.seekg(i);
		char * buffer = new char[1];
		myfile2.read(buffer, 1);
		if (buffer[0] != '\n')
			SansFightMap.push_back(buffer[0]);
	}
	myfile2.close();
	std::fstream myfile3("map/instructions.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile3.seekg(i);
		char * buffer = new char[1];
		myfile3.read(buffer, 1);
		if (buffer[0] != '\n')
			Instructions.push_back(buffer[0]);
	}
	myfile3.close();
	std::fstream myfile4("map/title.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile4.seekg(i);
		char * buffer = new char[1];
		myfile4.read(buffer, 1);
		if (buffer[0] != '\n')
			Title.push_back(buffer[0]);
	}
	myfile4.close();
	std::fstream myfile5("map/gameover.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile5.seekg(i);
		char * buffer = new char[1];
		myfile5.read(buffer, 1);
		if (buffer[0] != '\n')
			GameOver.push_back(buffer[0]);
	}
	myfile5.close();
	std::fstream myfile6("map/scene1.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile6.seekg(i);
		char * buffer = new char[1];
		myfile6.read(buffer, 1);
		if (buffer[0] != '\n')
			Scene1.push_back(buffer[0]);
	}
	myfile6.close();
	std::fstream myfile7("map/scene2.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile7.seekg(i);
		char * buffer = new char[1];
		myfile7.read(buffer, 1);
		if (buffer[0] != '\n')
			Scene2.push_back(buffer[0]);
	}
	myfile7.close();
	std::fstream myfile8("map/scene3.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile8.seekg(i);
		char * buffer = new char[1];
		myfile8.read(buffer, 1);
		if (buffer[0] != '\n')
			Scene3.push_back(buffer[0]);
	}
	myfile8.close();
	std::fstream myfile9("map/scene4.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile9.seekg(i);
		char * buffer = new char[1];
		myfile9.read(buffer, 1);
		if (buffer[0] != '\n')
			Scene4.push_back(buffer[0]);
	}
	myfile9.close();
	std::fstream myfile10("map/scene5.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile10.seekg(i);
		char * buffer = new char[1];
		myfile10.read(buffer, 1);
		if (buffer[0] != '\n')
			Scene5.push_back(buffer[0]);
	}
	myfile10.close();
	std::fstream myfile11("map/minigame1map.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile11.seekg(i);
		char * buffer = new char[1];
		myfile11.read(buffer, 1);
		if (buffer[0] != '\n')
			Minigame1Map.push_back(buffer[0]);
	}
	myfile11.close();
	std::fstream myfile12("map/minigame2map.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile12.seekg(i);
		char * buffer = new char[1];
		myfile12.read(buffer, 1);
		if (buffer[0] != '\n')
			Minigame2Map.push_back(buffer[0]);
	}
	myfile12.close();

	std::fstream tictactoe("map/tictactoe.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		tictactoe.seekg(i);
		char * buffer = new char[1];
		tictactoe.read(buffer, 1);
		if (buffer[0] != '\n')
			tictactoeGame.push_back(buffer[0]);
	}
	tictactoe.close();
	std::fstream MgameMenu("map/minigamemenu.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		MgameMenu.seekg(i);
		char * buffer = new char[1];
		MgameMenu.read(buffer, 1);
		if (buffer[0] != '\n')
			minigameMenu.push_back(buffer[0]);
	}
	MgameMenu.close();
	std::fstream myfile13("map/snek.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile11.seekg(i);
		char * buffer = new char[i];
		myfile13.read(buffer, 1);
		if (buffer[0] != '\n')
		{
			SnakeMap.push_back(buffer[0]);
		}
	}
	myfile13.close();
	std::fstream score("map/ladder.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile11.seekg(i);
		char * buffer = new char[i];
		score.read(buffer, 1);
		if (buffer[0] != '\n')
		{
			Highscore.push_back(buffer[0]);
		}
	}
	score.close();
	std::fstream myfile14("map/Shop.txt");
	for (short i = 0; i < 25 * 80; i++)
	{
		myfile14.seekg(i);
		char * buffer = new char[1];
		myfile14.read(buffer, 1);
		if (buffer[0] != '\n')
			SHOP.push_back(buffer[0]);
	}
}					
void save()
{
	std::ofstream stats("map/stats.txt");
	for (int currentWeapon = 0; currentWeapon < 4; currentWeapon++)
	{
		stats << Weapons[currentWeapon].Name << std::endl;
		stats << Weapons[currentWeapon].Clip << std::endl;
	}
	stats << Weapon1 << std::endl;
	stats << Weapon2 << std::endl;
	stats << Coin << std::endl;
	stats << Lives << std::endl;
	stats << int_stages << std::endl;
	stats.close();
	g_eGameState = S_GAME;
}
void continueSave()
{
	init();
	std::fstream stats("map/stats.txt"); // get back the stats from ui (for every weapons + lives left + stage level currently at + location of stuffs)
	for (int currentWeapon = 0; currentWeapon < 4; currentWeapon++)
	{
		stats >> Weapons[currentWeapon].Name;
		stats >> Weapons[currentWeapon].Clip;
	}
	stats >> Weapon1;
	stats >> Weapon2;
	stats >> Coin;
	stats >> Lives;
	stats >> int_stages;
	stats.close();
	stages = 0.000 + int_stages;
	if (int_stages == 50)
		StageType = EBoss;
	else if (int_stages % 10 == 0)
		StageType = EMinigame1;
	else if (int_stages % 5 == 0)
		StageType = EMinigame2;
	else
	{
		if (StageType == EBossBattle || StageType == EMinigame1 || StageType == EMinigame2)
			b_play = false;
		StageType = EStage;
	}
	if (StageType == EBoss)
		boss_init();
	else if (StageType == EMinigame1)
		minigame1_init();
	else if (StageType == EMinigame2)
		minigame2_init();
	else
		init();
	MMSelect = MMStart;
	g_eGameState = S_GAME;
}
void highscoreSave()
{
	std::fstream score("map/highscore.txt");

	if (rally > pong_t && StageType == EMinigame2)
	{
		pong_t3 = pong_t2;
		pong_t2 = pong_t;
		pong_t = rally;
	}
	else if (rally > pong_t2 && rally < pong_t && StageType == EMinigame2)
	{
		pong_t3 = pong_t2;
		pong_t2 = rally;
	}
	else if (rally > pong_t3 && rally < pong_t2 && StageType == EMinigame2)
		pong_t3 = rally;

	if (snake_Size > snake_length && StageType == EMiniGameSnake)
	{
		snake_length3 = snake_length2;
		snake_length2 = snake_length;
		snake_length = snake_Size;
	}
	else if (snake_Size > snake_length2 && snake_Size < snake_length && StageType == EMiniGameSnake)
	{
		snake_length3 = snake_length2;
		snake_length2 = snake_Size;
	}
	else if (snake_Size > snake_length3 && snake_Size < snake_length2 && StageType == EMiniGameSnake)
		snake_length3 = snake_Size;

	score << pong_t << std::endl;
	score << pong_t2 << std::endl;
	score << pong_t3 << std::endl;
	score << snake_length << std::endl;
	score << snake_length2 << std::endl;
	score << snake_length3 << std::endl;
	score.close();
}
void highscoreLoad()
{
	std::vector<char>::iterator it = Highscore.begin();
	for (short i = 0; i < 80 * 24; ++i)
	{
		g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
	}
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_eGameState = S_TITLE;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
	}
	std::ifstream score("map/highscore.txt");
	score >> pong_t;
	score >> pong_t2;
	score >> pong_t3;
	score >> snake_length;
	score >> snake_length2;
	score >> snake_length3;
	std::string first = std::to_string(pong_t);
	std::string second = std::to_string(pong_t2);
	std::string third = std::to_string(pong_t3);
	std::string length1 = std::to_string(snake_length);
	std::string length2 = std::to_string(snake_length2);
	std::string length3 = std::to_string(snake_length3);
	COORD c = g_Console.getConsoleSize();
	c.X = 37;
	c.Y = 6;
	g_Console.writeToBuffer(c, first, 0x0f);
	c.Y += 1;
	g_Console.writeToBuffer(c, second, 0x0f);
	c.Y += 1;
	g_Console.writeToBuffer(c, third, 0x0f);
	c.Y = 15;
	c.X += 3;
	g_Console.writeToBuffer(c, length1, 0x0f);
	c.Y += 1;
	g_Console.writeToBuffer(c, length2, 0x0f);
	c.Y += 1;
	g_Console.writeToBuffer(c, length3, 0x0f);
	score.close();
}
void tictactoePlay()
{
	if (b_number == 0)
	{
		b_number = 1;
		if (charOne == '1' && (charTwo == charThree || charFour == charSeven || charFive == charNine)) // Counter/Win priority
			charOne = 88;
		else if (charTwo == '2' && (charOne == charThree || charFive == charEight))
			charTwo = 88;
		else if (charThree == '3' && (charOne == charTwo || charSix == charNine || charFive == charSeven))
			charThree = 88;
		else if (charFour == '4' && (charOne == charSeven || charFive == charSix))
			charFour = 88;
		else if (charFive == '5' && (charFour == charSix || charTwo == charEight || charOne == charNine || charThree == charSeven))
			charFive = 88;
		else if (charSix == '6' && (charThree == charNine || charFour == charFive))
			charSix = 88;
		else if (charSeven == '7' && (charOne == charFour || charEight == charNine || charFive == charThree))
			charSeven = 88;
		else if (charEight == '8' && (charSeven == charNine || charTwo == charFive))
			charEight = 88;
		else if (charNine == '9' && (charOne == charFive || charSeven == charEight || charThree == charSix))
			charNine = 88;
		else if (charFive == '5') // Middle slot next priority
			charFive = 88;
		else if (charSeven == '7')
			charSeven = 88;
		else if (charThree == '3')
			charThree = 88;
		else if (charEight == '8')
			charEight = 88;
		else if (charTwo == '2')
			charTwo = 88;
		else if (charOne == '1')
			charOne = 88;
		else if (charFour == '4')
			charFour = 88;
		else if (charSix == '6')
			charSix = 88;
		else if (charNine == '9')
			charNine = 88;
		else
			b_number = 2;
	}
	else if (b_number == 1)
	{
		if (g_abKeyPressed[K_1] && charOne == '1')
		{
			charOne = 79;
			b_number = 0;
		}
		else if (g_abKeyPressed[K_2] && charTwo == '2')
		{
			charTwo = 79;
			b_number = 0;
		}
		else if (g_abKeyPressed[K_3] && charThree == '3')
		{
			charThree = 79;
			b_number = 0;
		}
		else if (g_abKeyPressed[K_4] && charFour == '4')
		{
			charFour = 79;
			b_number = 0;
		}
		else if (g_abKeyPressed[K_5] && charFive == '5')
		{
			charFive = 79;
			b_number = 0;
		}
		else if (g_abKeyPressed[K_6] && charSix == '6')
		{
			charSix = 79;
			b_number = 0;
		}
		else if (g_abKeyPressed[K_7] && charSeven == '7')
		{
			charSeven = 79;
			b_number = 0;
		}
		else if (g_abKeyPressed[K_8] && charEight == '8')
		{
			charEight = 79;
			b_number = 0;
		}
		else if (g_abKeyPressed[K_9] && charNine == '9')
		{
			charNine = 79;
			b_number = 0;
		}
	}
}
void tictactoeMulti()
{
	bool bSomethingHappened = false;
	if (b_number == 1 && !win)
	{
		if (g_abKeyPressed[K_1])
			if (charOne == '1')
			{
				charOne = 79;
				b_number = 2;
			}
		if (g_abKeyPressed[K_2])
			if (charTwo == '2')
			{
				charTwo = 79;
				b_number = 2;
			}
		if (g_abKeyPressed[K_3])
			if (charThree == '3')
			{
				charThree = 79;
				b_number = 2;
			}
		if (g_abKeyPressed[K_4])
			if (charFour == '4')
			{
				charFour = 79;
				b_number = 2;
			}
		if (g_abKeyPressed[K_5])
			if (charFive == '5')
			{
				charFive = 79;
				b_number = 2;
			}
		if (g_abKeyPressed[K_6])
			if (charSix == '6')
			{
				charSix = 79;
				b_number = 2;
			}
		if (g_abKeyPressed[K_7])
			if (charSeven == '7')
			{
				charSeven = 79;
				b_number = 2;
			}
		if (g_abKeyPressed[K_8])
			if (charEight == '8')
			{
				charEight = 79;
				b_number = 2;
			}
		if (g_abKeyPressed[K_9])
			if (charNine == '9')
			{
				charNine = 79;
				b_number = 2;
			}
	}
	else if (b_number == 2 && !win)
	{
		if (g_abKeyPressed[K_1])
			if (charOne == '1')
			{
				charOne = 88;
				b_number = 1;
			}
		if (g_abKeyPressed[K_2])
			if (charTwo == '2')
			{
				charTwo = 88;
				b_number = 1;
			}
		if (g_abKeyPressed[K_3])
			if (charThree == '3')
			{
				charThree = 88;
				b_number = 1;
			}
		if (g_abKeyPressed[K_4])
			if (charFour == '4')
			{
				charFour = 88;
				b_number = 1;
			}
		if (g_abKeyPressed[K_5])
			if (charFive == '5')
			{
				charFive = 88;
				b_number = 1;
			}
		if (g_abKeyPressed[K_6])
			if (charSix == '6')
			{
				charSix = 88;
				b_number = 1;
			}
		if (g_abKeyPressed[K_7])
			if (charSeven == '7')
			{
				charSeven = 88;
				b_number = 1;
			}
		if (g_abKeyPressed[K_8])
			if (charEight == '8')
			{
				charEight = 88;
				b_number = 1;
			}
		if (g_abKeyPressed[K_9])
			if (charNine == '9')
			{
				charNine = 88;
				b_number = 1;
			}
	}
	if (g_dBounceTime > g_dElapsedTime)
		return;
	if (bSomethingHappened)
	{
		g_dBounceTime = g_dElapsedTime + 0.125; // set the bounce time to some time in the future to prevent accidental triggers // 125ms should be enough
	}
}
void renderTicTacToe()
{
	std::vector<char>::iterator it = tictactoeGame.begin();
	for (short i = 0; i < 80 * 24; ++i)
	{
		g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
	}
	COORD one; one.X = 33; one.Y = 9;
	COORD two; two.X = 40; two.Y = 9;
	COORD three; three.X = 47; three.Y = 9;
	COORD four; four.X = 33; four.Y = 12;
	COORD five; five.X = 40; five.Y = 12;
	COORD six; six.X = 47; six.Y = 12;
	COORD seven; seven.X = 33; seven.Y = 15;
	COORD eight; eight.X = 40; eight.Y = 15;
	COORD nine; nine.X = 47; nine.Y = 15;
	COORD player; player.X = 5; player.Y = 21; // player b_number
	g_sChar.m_cLocation.X = 0;
	g_sChar.m_cLocation.Y = 0;
	g_Console.writeToBuffer(one, charOne, charColouring(charOne));
	g_Console.writeToBuffer(two, charTwo, charColouring(charTwo));
	g_Console.writeToBuffer(three, charThree, charColouring(charThree));
	g_Console.writeToBuffer(four, charFour, charColouring(charFour));
	g_Console.writeToBuffer(five, charFive, charColouring(charFive));
	g_Console.writeToBuffer(six, charSix, charColouring(charSix));
	g_Console.writeToBuffer(seven, charSeven, charColouring(charSeven));
	g_Console.writeToBuffer(eight, charEight, charColouring(charEight));
	g_Console.writeToBuffer(nine, charNine, charColouring(charNine));
	if (multi)
	{
		COORD c = g_Console.getConsoleSize();
		c.X = 24;
		c.Y = 18;
		g_Console.writeToBuffer(c, "PLAYER 1", 0x0f);
		c.X += 3;
		c.Y += 1;
		g_Console.writeToBuffer(c, "PLAYER 2", 0x0f);

		g_Console.writeToBuffer(player, "Player", 0x0f);
		player.X += 7;
		std::string playerNo = std::to_string(b_number);
		g_Console.writeToBuffer(player, playerNo, 0x0f);
	}
	tictactoeWin();
}
void tictactoeWin()
{
	COORD c; c.X = 37; c.Y = 21;
	if (!multi)
	{
		if (b_number == 2)
		{
			g_Console.writeToBuffer(c, "Tie", 0x0f);

		}
		else if (charOne == charTwo && charTwo == charThree
			|| charFour == charFive && charFive == charSix
			|| charSeven == charEight && charEight == charNine
			|| charOne == charFour && charFour == charSeven
			|| charTwo == charFive && charFive == charEight
			|| charThree == charSix && charSix == charNine
			|| charOne == charFive && charFive == charNine
			|| charThree == charFive && charFive == charSeven)
		{
			if (b_number == 0 || b_number == 3)
			{
				g_Console.writeToBuffer(c, "You Win", 0x0f);
				b_number = 3;
			}
			else if (b_number == 1 || b_number == 4)
			{
				g_Console.writeToBuffer(c, "You Lose", 0x0f);
				b_number = 4;
			}
		}
		if (g_abKeyPressed[K_SPACE])
		{
			b_number = 1;
			charOne = 49;
			charTwo = 50;
			charThree = 51;
			charFour = 52;
			charFive = 53;
			charSix = 54;
			charSeven = 55;
			charEight = 56;
			charNine = 57;
		}
	}
	else
	{
		if (charOne == charTwo && charTwo == charThree
			|| charFour == charFive && charFive == charSix
			|| charSeven == charEight && charEight == charNine
			|| charOne == charFour && charFour == charSeven
			|| charTwo == charFive && charFive == charEight
			|| charThree == charSix && charSix == charNine
			|| charOne == charFive && charFive == charNine
			|| charThree == charFive && charFive == charSeven)
		{
			win = true;
			if (b_number == 1)
			{
				g_Console.writeToBuffer(c, "Player 2 win", 0x0f);
			}
			if (b_number == 2)
			{
				g_Console.writeToBuffer(c, "Player 1 win", 0x0f);
			}
			if (g_abKeyPressed[K_SPACE])
			{
				b_number = 1;
				charOne = 49;
				charTwo = 50;
				charThree = 51;
				charFour = 52;
				charFive = 53;
				charSix = 54;
				charSeven = 55;
				charEight = 56;
				charNine = 57;
				win = false;
			}
		}
	}
}
void minigame()
{
	std::vector<char>::iterator it = minigameMenu.begin();
	for (short i = 0; i < 80 * 24; ++i)
	{
		g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
	}
	COORD m = g_Console.getConsoleSize();
	switch (MMgame)
	{
	case MMrhythm:
		m.Y = 6;
		m.X = 33;
		g_Console.writeToBuffer(m, "1. Beat Tapper", 0x0E);
		m.Y += 2;
		g_Console.writeToBuffer(m, "2. Pong", 0x03);
		m.Y += 2;
		g_Console.writeToBuffer(m, "3. Tic Tac Toe >", 0x03);
		m.Y += 2;
		g_Console.writeToBuffer(m, "4. Snake", 0x03);
		break;
	case MMpong:
		m.Y = 6;
		m.X = 33;
		g_Console.writeToBuffer(m, "1. Beat Tapper", 0x03);
		m.Y += 2;
		g_Console.writeToBuffer(m, "2. Pong", 0x0E);
		m.Y += 2;
		g_Console.writeToBuffer(m, "3. Tic Tac Toe >", 0x03);
		m.Y += 2;
		g_Console.writeToBuffer(m, "4. Snake", 0x03);
		break;
	case MMtictactoe:
		m.Y = 6;
		m.X = 33;
		g_Console.writeToBuffer(m, "1. Beat Tapper", 0x03);
		m.Y += 2;
		g_Console.writeToBuffer(m, "2. Pong", 0x03);
		m.Y += 2;
		g_Console.writeToBuffer(m, "3. Tic Tac Toe >", 0x0E);
		m.Y += 2;
		g_Console.writeToBuffer(m, "4. Snake", 0x03);
		break;
	case MMsnake:
		m.Y = 6;
		m.X = 33;
		g_Console.writeToBuffer(m, "1. Beat Tapper", 0x03);
		m.Y += 2;
		g_Console.writeToBuffer(m, "2. Pong", 0x03);
		m.Y += 2;
		g_Console.writeToBuffer(m, "3. Tic Tac Toe >", 0x03);
		m.Y += 2;
		g_Console.writeToBuffer(m, "4. Snake", 0x0E);
		break;
	case MM1P:
		m.Y = 6;
		m.X = 33;
		g_Console.writeToBuffer(m, "1. Beat Tapper", 0x03);
		m.Y += 2;
		g_Console.writeToBuffer(m, "2. Pong", 0x03);
		m.Y += 2;
		g_Console.writeToBuffer(m, "3. Tic Tac Toe", 0x03);
		m.Y += 2;
		m.X += 3;
		g_Console.writeToBuffer(m, "1 Player", 0x0E);
		m.Y += 1;
		g_Console.writeToBuffer(m, "2 Player", 0x03);
		m.Y += 2;
		m.X -= 3;
		g_Console.writeToBuffer(m, "4. Snake", 0x03);
		break;
	case MM2P:
		m.Y = 6;
		m.X = 33;
		g_Console.writeToBuffer(m, "1. Beat Tapper", 0x03);
		m.Y += 2;
		g_Console.writeToBuffer(m, "2. Pong", 0x03);
		m.Y += 2;
		g_Console.writeToBuffer(m, "3. Tic Tac Toe", 0x03);
		m.Y += 2;
		m.X += 3;
		g_Console.writeToBuffer(m, "1 Player", 0x03);
		m.Y += 1;
		g_Console.writeToBuffer(m, "2 Player", 0x0E);
		m.Y += 2;
		m.X -= 3;
		g_Console.writeToBuffer(m, "4. Snake", 0x03);
		break;
	}
}
void minigameselect()
{
	g_bMinigame = true;
	Lives = 5;
	b_play = false;
	ost();
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	if (MMgame == MMrhythm && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_MINIGAME)
	{
		MMgame = MMpong;
		bSomethingHappened = true;
	}
	else if (MMgame == MMpong && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_MINIGAME)
	{
		MMgame = MMtictactoe;
		bSomethingHappened = true;
	}
	else if (MMgame == MMtictactoe && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_MINIGAME)
	{
		MMgame = MMsnake;
		bSomethingHappened = true;
	}
	else if (MMgame == MMsnake && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_MINIGAME)
	{
		MMgame = MMrhythm;
		bSomethingHappened = true;
	}
	else if (MMgame == MMrhythm && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_MINIGAME)
	{
		MMgame = MMsnake;
		bSomethingHappened = true;
	}
	else if (MMgame == MMpong && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_MINIGAME)
	{
		MMgame = MMrhythm;
		bSomethingHappened = true;
	}
	else if (MMgame == MMtictactoe && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_MINIGAME)
	{
		MMgame = MMpong;
		bSomethingHappened = true;
	}
	else if (MMgame == MMsnake && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_MINIGAME)
	{
		MMgame = MMtictactoe;
		bSomethingHappened = true;
	}
	else if (MMgame == MMtictactoe && (g_abKeyPressed[K_RIGHT] || g_abKeyPressed[K_D]) && g_eGameState == S_MINIGAME)
	{
		MMgame = MM1P;
		bSomethingHappened = true;
	}
	else if ((MMgame == MM1P || MMgame == MM2P) && (g_abKeyPressed[K_LEFT] || g_abKeyPressed[K_A]) && g_eGameState == S_MINIGAME)
	{
		MMgame = MMtictactoe;
		bSomethingHappened = true;
	}
	else if (MMgame == MM1P && (g_abKeyPressed[K_W] || g_abKeyPressed[K_S] || g_abKeyPressed[K_UP] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_MINIGAME)
	{
		MMgame = MM2P;
		bSomethingHappened = true;
	}
	else if (MMgame == MM2P && (g_abKeyPressed[K_W] || g_abKeyPressed[K_S] || g_abKeyPressed[K_UP] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_MINIGAME)
	{
		MMgame = MM1P;
		bSomethingHappened = true;
	}
	if (MMgame == MMrhythm && g_abKeyPressed[K_SPACE] && g_eGameState == S_MINIGAME)
	{
		b_play = false;
		g_dElapsedTime = 0;
		StageType = EMinigame1;
		g_eGameState = S_GAME;
		minigame1_init();
		stages = 50;
		int_stages = 50;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
	}
	else if (MMgame == MMpong && g_abKeyPressed[K_SPACE] && g_eGameState == S_MINIGAME)
	{
		b_play = false;
	    g_bforscore = true;
		g_dElapsedTime = 0;
		StageType = EMinigame2;
		g_eGameState = S_GAME;
		minigame2_init();
	    Lives = 2;
		stages = 10;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
	}
	else if (MMgame == MM1P && g_abKeyPressed[K_SPACE] && g_eGameState == S_MINIGAME)
	{
		b_play = false;
		multi = false;
		g_eGameState = S_GAME;
		StageType = ETicTacToe;
		b_number = 1;
		charOne = 49;
		charTwo = 50;
		charThree = 51;
		charFour = 52;
		charFive = 53;
		charSix = 54;
		charSeven = 55;
		charEight = 56;
		charNine = 57;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
	}
	else if (MMgame == MM2P && g_abKeyPressed[K_SPACE] && g_eGameState == S_MINIGAME)
	{
		b_play = false;
		multi = true;
		g_eGameState = S_GAME;
		StageType = ETicTacToe2;
		b_number = 1;
		charOne = 49;
		charTwo = 50;
		charThree = 51;
		charFour = 52;
		charFive = 53;
		charSix = 54;
		charSeven = 55;
		charEight = 56;
		charNine = 57;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
	}
	else if (MMgame == MMsnake && g_abKeyPressed[K_SPACE] && g_eGameState == S_MINIGAME)
	{
		b_play = false;
		snake_Size = 1;
		SnakeLocation.resize(1);
		g_dElapsedTime = 0;
		g_eGameState = S_GAME;
		StageType = EMiniGameSnake;
		g_snake.X = 40;
		g_snake.Y = 15;
		g_sChar.m_cLocation.X = 0;
		g_sChar.m_cLocation.Y = 0;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
	}
	if(bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_eGameState = S_TITLE;
		StageType = EMainMenu;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		b_play = false;
	}
}					
void renderSnake()
{
	for (size_t i = 0; SnakeLocation.size() > i; i++)
	{
		if (i == SnakeLocation.size() - 1)
		{
			g_Console.writeToBuffer(SnakeLocation[i], '#', 0x0a);
		}
		else
			g_Console.writeToBuffer(SnakeLocation[i], 254, 0x0a);
		for (size_t j = 0; SnakeLocation.size() > j; j++)
		{
			if (i == j)
			{
				break;
			}
			if (SnakeLocation[i].X == SnakeLocation[j].X && SnakeLocation[i].Y == SnakeLocation[j].Y)
			{
				highscoreLoad();
				highscoreSave();
				g_eGameState = S_MINIGAME;
				b_play = false;
			}
		}
	}
}
void renderApple()
{
	if (AppleCollected == true)
	{
		Apple.X = rand() % 78 + 1;
		Apple.Y = rand() % 19 + 4;
		if (SnakeMap[Apple.X + Apple.Y * 80] == ' ')
		{
			AppleCollected = false;
		}
	}
	g_Console.writeToBuffer(Apple,254,0x0c);
}
void snakeInput()
{
	if (StageType == EMiniGameSnake)
	{
		if (g_abKeyPressed[K_W] && Direction != 'S')
		{
			Direction = 'W';
		}
		if (g_abKeyPressed[K_A] && Direction != 'D')
		{
			Direction = 'A';
		}
		if (g_abKeyPressed[K_S] && Direction != 'W')
		{
			Direction = 'S';
		}
		if (g_abKeyPressed[K_D] && Direction != 'A')
		{
			Direction = 'D';
		}
		if (SnakeMap[g_snake.X + g_snake.Y * 80] != ' ' && SnakeMap[g_snake.X + g_snake.Y * 80] != 'a')
		{
			highscoreLoad();
			highscoreSave();
			g_eGameState = S_MINIGAME;
			b_play = false;
		}
		if (g_snake.X == Apple.X && g_snake.Y == Apple.Y)
		{
			AppleCollected = true;
			shootsound = true;
			snake_Size++;
		}
	}
}
void snakeMovement()
{
	if(delay > 15) // Once every 15 frames move by 1.
	{
		if(Direction == 'W')
		{
			g_snake.Y--;
			SnakeLocation.push_back(g_snake);
		}
		if(Direction == 'A')
		{
			g_snake.X--;
			SnakeLocation.push_back(g_snake);
		}
		if(Direction == 'S')
		{
			g_snake.Y++;
			SnakeLocation.push_back(g_snake);
		}
		if(Direction == 'D')
		{
			g_snake.X++;
			SnakeLocation.push_back(g_snake);
		}
		if(SnakeLocation.size() > snake_Size) // Controls the size of the snake
		{
			SnakeLocation.erase(SnakeLocation.begin());
		}
		delay = 0;
	}
	delay++;
}
WORD charColouring(char character)
{
	if (character == 79)
		return 0x0C;
	else if (character == 88)
		return 0x0B;
	else
		return 0x0F;
}
