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
SMinigame1	g_minigame1_beat1;
SMinigame1	g_minigame1_beat2;
SMinigame1	g_minigame1_beat3;
SMinigame1	g_minigame1_beat4;
SGameChar	g_minigame2_paddle1;
SGameChar	g_minigame2_paddle2;
SGameChar	g_door;
std::vector<char>	Title;
std::vector<char>	GameOver;
std::vector<char>	Map;
std::vector<char>	Instructions;
std::vector<char>	SansMap;
std::vector<char>	SansFightMap;
std::vector<char>	Minigame1Map;
std::vector<char>	Minigame2Map;
std::vector<char>	Scene1;
std::vector<char>	Scene2;
std::vector<char>	Scene3;
std::vector<char>	Scene4;
std::vector<char>	Scene5;
size_t		minigame1time = 0;
size_t		minigame1random = 9;
size_t		deathsound = 0;
size_t		shootsound = 0;
size_t		reloadsound = 0;
size_t		shootfailsound = 0;
int			MMSelect = MMStart;
int			int_stages = 1;
double		stages = 0.000 + int_stages;
size_t		StageType = EMainMenu;
bool		b_play = false;
bool		bossSpeech = false;
int g_shootdist = 0;
int g_shootmaxdist = 10; // Shooting distance of weapon. Can be changed.
EGAMESTATES g_eGameState = S_INTRO;
EWEAPONSTATES g_eWeaponState = Hold;
EWEAPONSTATES g_eM2WeaponState = FireUp;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
int Lives = 3; // Number of lives the player has left (Base Value is 3)
int currentWeapon = 0; // Current Weapon
WeaponParameters Weapons[4]; // Number of Weapons
// Console object
Console g_Console(80, 24, "Monster Dungeon");
void minigame1_init()
{
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
	if (Lives + 2 <= 99)
		Lives += 2;
}
void minigame2_init()
{
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
	g_weapon.m_bActive = true;
	g_door.m_cLocation.X = 10;
	g_door.m_cLocation.Y = 13;
	g_door.m_bActive = false;
}
void boss_init()
{
	b_play = false;
	weapdata();
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;
	g_Console.setConsoleFont(0, 16, L"Consolas");
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
}
void shutdown(void)
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	g_Console.clearBuffer();
}
void getInput(void)
{
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_ENTER] = isKeyPressed(13);
	g_abKeyPressed[K_W] = isKeyPressed(87);
	g_abKeyPressed[K_A] = isKeyPressed(65);
	g_abKeyPressed[K_S] = isKeyPressed(83);
	g_abKeyPressed[K_D] = isKeyPressed(68);
	g_abKeyPressed[K_C] = isKeyPressed(67);
	g_abKeyPressed[K_E] = isKeyPressed(69); // For Weapon Switching
}
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
	}
}
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
	case S_CONTINUE: continueSave();
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
	if ((g_dElapsedTime > 35) || g_abKeyPressed[K_W] || g_abKeyPressed[K_A] || g_abKeyPressed[K_S] || g_abKeyPressed[K_D] || g_abKeyPressed[K_UP] || g_abKeyPressed[K_LEFT] || g_abKeyPressed[K_DOWN] || g_abKeyPressed[K_RIGHT])
	{
		g_eGameState = S_TITLE;
		StageType = EMainMenu;
		init();
	}
}
void splashScreenWait() 
{
	if (!b_play)
		ost();
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	if ((MMSelect == MMStart || MMSelect == MMContinue) && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_TITLE)
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
		MMSelect = MMExit;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMInstructions && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMStart;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMExit && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMInstructions;
		bSomethingHappened = true;
	}
	else if ((MMSelect == MMStart || MMSelect == MMContinue) && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMExit;
		bSomethingHappened = true;
	}
	else if (MMSelect == MMExit && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && g_eGameState == S_TITLE)
	{
		MMSelect = MMStart;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMInstructions && g_eGameState == S_TITLE)
	{
		g_eGameState = S_INSTRUCTIONS;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		b_play = false;
	}
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMExit && g_eGameState == S_TITLE)
	{
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		g_bQuitGame = true;
	}
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMStart && g_eGameState == S_TITLE)
	{
		StageType = EStage;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		b_play = false;
		Weapons[0].Clip = Weapons[0].ClipMax;
		int_stages = 1;
		g_eGameState = S_GAME;
	}
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMContinue && g_eGameState == S_TITLE)
	{
		StageType = EStage;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		b_play = false;
		g_eGameState = S_CONTINUE;
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
		g_door.m_bActive = true;
		g_minigame1_beat1.m_bActive = false;
		g_minigame1_beat2.m_bActive = false;
		g_minigame1_beat3.m_bActive = false;
		g_minigame1_beat4.m_bActive = false;
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
			else if (g_dElapsedTime < minigame1time + 0.3 && g_dElapsedTime >= minigame1time + 0.2)
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
			else if (g_dElapsedTime < minigame1time + 0.5 && g_dElapsedTime >= minigame1time + 0.4)
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
			else if (g_dElapsedTime < minigame1time + 0.7 && g_dElapsedTime >= minigame1time + 0.6)
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
	}
	else if (g_abKeyPressed[K_RIGHT])
	{
		g_weapon.m_cLocation.X = g_sChar.m_cLocation.X + 3;
		g_weapon.m_cLocation.Y = 13;
	}
	else
	{
		g_weapon.m_cLocation.X = 0;
		g_weapon.m_cLocation.Y = 0;
	}
	if (g_weapon.m_cLocation.X == g_minigame1_beat1.m_cLocation.X && g_minigame1_beat1.m_bActive == true)
	{
		deathsound = 5;
		g_minigame1_beat1.m_bActive = false;
		g_minigame1_beat1.m_cLocation.X = 2;
	}
	if (g_weapon.m_cLocation.X == g_minigame1_beat2.m_cLocation.X && g_minigame1_beat2.m_bActive == true)
	{
		deathsound = 5;
		g_minigame1_beat2.m_bActive = false;
		g_minigame1_beat2.m_cLocation.X = 77;
	}
	if (g_weapon.m_cLocation.X == g_minigame1_beat3.m_cLocation.X && g_minigame1_beat3.m_bActive == true)
	{
		deathsound = 5;
		g_minigame1_beat3.m_bActive = false;
		g_minigame1_beat3.m_cLocation.X = 2;
	}
	if (g_weapon.m_cLocation.X == g_minigame1_beat4.m_cLocation.X && g_minigame1_beat4.m_bActive == true)
	{
		deathsound = 5;
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
		g_weapon.m_cLocation.X = 78;
		g_door.m_bActive = true;
		g_door.m_cLocation = g_sChar.m_cLocation;
	}
	if (g_weapon.m_cLocation.X == g_minigame2_paddle1.m_cLocation.X && (g_weapon.m_cLocation.Y >= g_minigame2_paddle1.m_cLocation.Y - 2 && g_weapon.m_cLocation.Y <= g_minigame2_paddle1.m_cLocation.Y + 2))
		g_eWeaponState = FireRight;
	if (g_weapon.m_cLocation.X == g_minigame2_paddle2.m_cLocation.X && (g_weapon.m_cLocation.Y >= g_minigame2_paddle2.m_cLocation.Y - 2 && g_weapon.m_cLocation.Y <= g_minigame2_paddle2.m_cLocation.Y + 2))
		g_eWeaponState = FireLeft;
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
	if (g_dElapsedTime < int_stages + 5 && g_eWeaponState == FireRight && g_minigame2_paddle2.m_cLocation.Y <= g_weapon.m_cLocation.Y + 1  && g_minigame2_paddle2.m_cLocation.Y >= g_weapon.m_cLocation.Y - 1 && g_weapon.m_cLocation.X >= 40)
		g_minigame2_paddle2.m_cLocation.Y = g_weapon.m_cLocation.Y;
	if (bSomethingHappened)
	{
		g_dBounceTime = g_dElapsedTime + 0.03 + 0.1/stages; // 125ms should be enough
	}
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
	}
	else if (g_dElapsedTime > 28 && g_dElapsedTime <= 29)
	{
		g_gaster1.m_cLocation.Y = 10 - 10 * (g_dElapsedTime - 28);
		g_gaster1.m_bFire = true;
		g_gaster4.m_cLocation.Y = 10 - 10 * (g_dElapsedTime - 28);
		g_gaster4.m_bFire = true;
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
	}
	else if (g_dElapsedTime > 34 && g_dElapsedTime <= 35)
	{
		g_gaster2.m_cLocation.Y = 19 - 9 * (g_dElapsedTime - 34);
		g_gaster2.m_bFire = true;
	}
	else if (g_dElapsedTime > 35 && g_dElapsedTime <= 36)
	{
		g_gaster2.m_cLocation.Y = 10;
		g_gaster2.m_cLocation.X = 14 - 14 * (g_dElapsedTime - 35);
		g_gaster2.m_bFire = true;
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
	}
	else if (g_dElapsedTime > 40 && g_dElapsedTime <= 43)
	{
		g_gaster4.m_cLocation.X = g_sChar.m_cLocation.X;
		g_gaster1.m_bFire = true;
		g_gaster1.m_cLocation.X = 20 + 10 * (g_dElapsedTime - 40);
	}
	else if (g_dElapsedTime > 43 && g_dElapsedTime <= 45)
	{
		g_gaster4.m_cLocation.X = g_sChar.m_cLocation.X;
		g_gaster1.m_bFire = true;
		g_gaster1.m_cLocation.X = 50 - 30 * (g_dElapsedTime - 43);
	}
	else if (g_dElapsedTime > 45 && g_dElapsedTime <= 46)
	{
		g_gaster4.m_cLocation.Y = 10;
		g_gaster2.m_cLocation.Y = 16 - 3 * (g_dElapsedTime - 45);
		g_gaster3.m_cLocation.Y = 19 + 3 * (g_dElapsedTime - 45);
	}
	else if (g_dElapsedTime > 46 && g_dElapsedTime <= 47)
	{
		g_gaster4.m_cLocation.Y = 10 - 10 * (g_dElapsedTime - 46);
		g_gaster4.m_bFire = true;
		g_gaster2.m_cLocation.X = 15 - 15 * (g_dElapsedTime - 46);
		g_gaster3.m_cLocation.X = 66 + 15 * (g_dElapsedTime - 46);
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
	}
	else if (g_dElapsedTime > 52 && g_dElapsedTime <= 53)
	{
		g_gaster1.m_bFire = true;
		g_gaster4.m_bFire = true;
	}
	else if (g_dElapsedTime > 53 && g_dElapsedTime <= 54)
	{
		g_gaster1.m_cLocation.X = 37 - 10 * (g_dElapsedTime - 53);
	}
	else if (g_dElapsedTime > 54 && g_dElapsedTime <= 55)
	{
		g_gaster4.m_cLocation.X = 43 - 10 * (g_dElapsedTime - 54);
	}
	else if (g_dElapsedTime > 55 && g_dElapsedTime <= 56)
	{
		g_gaster2.m_cLocation.Y = 17 + 3 * (g_dElapsedTime - 55);
		g_gaster3.m_bActive = true;
		g_gaster3.m_cLocation.Y = 10;
		g_gaster3.m_cLocation.X = 81 - 15 * (g_dElapsedTime - 55);
	}
	else if (g_dElapsedTime > 56 && g_dElapsedTime <= 57)
	{
		g_gaster2.m_cLocation.Y = 20;
		g_gaster3.m_bFire = true;
		g_gaster3.m_cLocation.Y = 10 + 5 * (g_dElapsedTime - 56);
		g_gaster3.m_cLocation.X = 66;
	}
	else if (g_dElapsedTime > 57 && g_dElapsedTime <= 57.5)
	{
		g_gaster4.m_cLocation.X = 34;
		g_gaster1.m_cLocation.X = 26;
		g_gaster2.m_cLocation.Y = 21;
		g_gaster3.m_cLocation.Y = 14;
	}
	else if (g_dElapsedTime > 57.5 && g_dElapsedTime <= 58.5)
	{
		g_gaster4.m_cLocation.X = 34 + 5 * (g_dElapsedTime - 57.5);
		g_gaster1.m_cLocation.X = 26 + 5 * (g_dElapsedTime - 57.5);
	}
	else if (g_dElapsedTime > 58.5 && g_dElapsedTime <= 59.5)
	{
		g_gaster4.m_cLocation.X = 39 + 5 * (g_dElapsedTime - 58.5);
		g_gaster1.m_cLocation.X = 31 + 5 * (g_dElapsedTime - 58.5);
		g_gaster2.m_cLocation.Y = 21 + 3 * (g_dElapsedTime - 58.5);
		g_gaster3.m_cLocation.Y = 14 + 3 * (g_dElapsedTime - 58.5);
	}
	else if (g_dElapsedTime > 59.5 && g_dElapsedTime <= 60.5)
	{
		g_gaster4.m_cLocation.X = 44;
		g_gaster1.m_cLocation.X = 36;
		g_gaster2.m_cLocation.Y = 24 - 3 * (g_dElapsedTime - 59.5);
		g_gaster3.m_cLocation.Y = 17 - 3 * (g_dElapsedTime - 59.5);
	}
	else if (g_dElapsedTime > 60.5 && g_dElapsedTime <= 61.5)
	{
		g_gaster2.m_cLocation.Y = 21 + 4 * (g_dElapsedTime - 60.5);
		g_gaster3.m_cLocation.Y = 14 + 4 * (g_dElapsedTime - 60.5);
	}
	else if (g_dElapsedTime > 61.5 && g_dElapsedTime <= 62.5)
	{
		g_gaster2.m_cLocation.Y = 25 - 5 * (g_dElapsedTime - 61.5);
		g_gaster3.m_cLocation.Y = 18 - 5 * (g_dElapsedTime - 61.5);
	}
	else if (g_dElapsedTime > 62.5 && g_dElapsedTime <= 63.5)
	{
		g_gaster2.m_cLocation.X = 15 - 15 * (g_dElapsedTime - 62.5);
		g_gaster3.m_cLocation.X = 66 + 15 * (g_dElapsedTime - 62.5);
		g_gaster1.m_cLocation.Y = 10 - 10 * (g_dElapsedTime - 62.5);
		g_gaster4.m_cLocation.Y = 10 - 10 * (g_dElapsedTime - 62.5);
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


	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
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
	if ((g_abKeyPressed[K_UP] || g_abKeyPressed[K_DOWN] || g_abKeyPressed[K_LEFT] || g_abKeyPressed[K_RIGHT]) && (g_eWeaponState != Hold || Weapons[currentWeapon].Clip == 0))
	{
		shootfailsound = 1;
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
		reload();
	}
	if (g_sChar.m_cLocation.X == g_enemy2.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy2.m_cLocation.Y)
	{
		g_enemy2.m_bActive = false;
		g_enemy2.m_cLocation.X = 0;
		g_enemy2.m_cLocation.Y = 0;
		reload();
	}
	if (g_sChar.m_cLocation.X == g_enemy3.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy3.m_cLocation.Y)
	{
		g_enemy3.m_bActive = false;
		g_enemy3.m_cLocation.X = 0;
		g_enemy3.m_cLocation.Y = 0;
		reload();
	}
	if (g_sChar.m_cLocation.X == g_enemy4.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy4.m_cLocation.Y)
	{
		g_enemy4.m_bActive = false;
		g_enemy4.m_cLocation.X = 0;
		g_enemy4.m_cLocation.Y = 0;
		reload();
	}
	if (g_sChar.m_cLocation.X == g_enemy5.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy5.m_cLocation.Y)
	{
		g_enemy5.m_bActive = false;
		g_enemy5.m_cLocation.X = 0;
		g_enemy5.m_cLocation.Y = 0;
		reload();
	}
	if (g_sChar.m_cLocation.X == g_enemy6.m_cLocation.X && g_sChar.m_cLocation.Y == g_enemy6.m_cLocation.Y)
	{
		g_enemy6.m_bActive = false;
		g_enemy6.m_cLocation.X = 0;
		g_enemy6.m_cLocation.Y = 0;
		reload();
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
	if (g_abKeyPressed[K_ENTER] && StageType == EBossBattle && g_dElapsedTime < 20)
		g_dElapsedTime = 20;
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
		StageType == EStage)
		g_door.m_bActive = true;
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
				StageType = EMinigame2;
			else
			{
				if (StageType == EBossBattle)
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
			save();
			if (Lives != 99)
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
	{
		std::vector<char>::iterator it = Scene1.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}
	}
	if (g_dElapsedTime > 7 && g_dElapsedTime <= 14)
	{
		std::vector<char>::iterator it = Scene2.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}
	}
	if (g_dElapsedTime > 14 && g_dElapsedTime <= 21)
	{
		std::vector<char>::iterator it = Scene3.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}
	}
	if (g_dElapsedTime > 21 && g_dElapsedTime <= 28)
	{
		std::vector<char>::iterator it = Scene4.begin();
		for (short i = 0; i < 80 * 24; ++i)
		{
			g_Console.writeToBuffer(COORD{ i % 80, i / 80 }, it[i], 0x0F);
		}
	}
	if (g_dElapsedTime > 28 && g_dElapsedTime <= 35)
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
		m.X = 34;
		g_Console.writeToBuffer(m, "Start", 0x0E);
		m.X = 40;
		g_Console.writeToBuffer(m, "Continue", 0x03);
		m.Y += 1;
		m.X = g_Console.getConsoleSize().X / 2 - 6;
		g_Console.writeToBuffer(m, "Instructions", 0x03);
		m.Y += 1;
		m.X = g_Console.getConsoleSize().X / 2 - 2;
		g_Console.writeToBuffer(m, "Exit", 0x03);
		break;

	case MMInstructions:
		m.Y = 20;
		m.X = 34;
		g_Console.writeToBuffer(m, "Start", 0x03);
		m.X = 40;
		g_Console.writeToBuffer(m, "Continue", 0x03);
		m.Y += 1;
		m.X = g_Console.getConsoleSize().X / 2 - 6;
		g_Console.writeToBuffer(m, "Instructions", 0x0E);
		m.Y += 1;
		m.X = g_Console.getConsoleSize().X / 2 - 2;
		g_Console.writeToBuffer(m, "Exit", 0x03);
		break;

	case MMExit:
		m.Y = 20;
		m.X = 34;
		g_Console.writeToBuffer(m, "Start", 0x03);
		m.X = 40;
		g_Console.writeToBuffer(m, "Continue", 0x03);
		m.Y += 1;
		m.X = g_Console.getConsoleSize().X / 2 - 6;
		g_Console.writeToBuffer(m, "Instructions", 0x03);
		m.Y += 1;
		m.X = g_Console.getConsoleSize().X / 2 - 2;
		g_Console.writeToBuffer(m, "Exit", 0x0E);
		break;

	case MMContinue:
		m.Y = 20;
		m.X = 34;
		g_Console.writeToBuffer(m, "Start", 0x03);
		m.X = 40;
		g_Console.writeToBuffer(m, "Continue", 0x0E);
		m.Y += 1;
		m.X = g_Console.getConsoleSize().X / 2 - 6;
		g_Console.writeToBuffer(m, "Instructions", 0x03);
		m.Y += 1;
		m.X = g_Console.getConsoleSize().X / 2 - 2;
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
	}
	if (StageType == EBossBattle)
	{
		renderBossSpeech();
		renderGaster1();
		renderGaster2();
		renderGaster3();
		renderGaster4();
		renderWeapon();
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
	renderCharacter();  // renders the character into the buffer
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
	UI.X = g_Console.getConsoleSize().X / 3 + 1;
	g_Console.writeToBuffer(UI, "Weapon : ", 0x9f);
	UI.X = UI.X + 9;
	g_Console.writeToBuffer(UI, Weapons[currentWeapon].Name, 0x9f); // Display Equipped Weapon
	UI.X = UI.X + Weapons[currentWeapon].Name.length() + 3; // Increases UI.X by text length of weapon 1's name
	g_Console.writeToBuffer(UI, "Ammo : ", 0x9f);
	UI.X = UI.X + 7;
	display = std::to_string(Weapons[currentWeapon].Clip);
	g_Console.writeToBuffer(UI, display, 0x9f); // Display Current Clip
	UI.X += 5;
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
		g_eGameState = S_GAME;
		init();
		Lives = 3;
		stages = 0;
		for (size_t i = 0; i < 4; i++)
			Weapons[i].Clip = 0;
	}
	if (g_abKeyPressed[K_SPACE] && MMSelect == MMStart && g_eGameState == S_GAMEOVER) // CONTINUE_GAME
	{
		StageType = EStage;
		PlaySound(TEXT("sound/damage.wav"), NULL, SND_FILENAME);
		b_play = false;
		g_eGameState = S_CONTINUE;
	}
	if (bSomethingHappened)
	{
		g_dBounceTime = g_dElapsedTime + 0.125;
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
		g_eGameState = S_TITLE;
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
	if (StageType == EMainMenu)
		PlaySound(TEXT("sound/menu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // play sound while in menu
	else if (StageType == EStage)
		PlaySound(TEXT("sound/cave.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // change 'cave' to whatever
	else if (StageType == EBoss)
		PlaySound(TEXT("sound/boss.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // play sound while in stage
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
}
void save()
{
	std::ofstream stats("map/stats.txt");
	for (int currentWeapon = 0; currentWeapon < 4; currentWeapon++)
	{
		stats << Weapons[currentWeapon].Name << std::endl;
		stats << Weapons[currentWeapon].Clip << std::endl;
	}
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
	stats >> Lives;
	stats >> int_stages;
	if (int_stages % 5 == 0)
	{
		stages = 0.000 + int_stages - 1;
		int_stages--;
	}
	else
		stages = 0.000 + int_stages;
	MMSelect = MMStart;
	g_eGameState = S_GAME;
	StageType = EStage;
}