#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <Windows.h>
#include <vector>

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_ESCAPE,
	K_SPACE,
	K_W,
	K_A,
	K_S,
	K_D,
	K_C,
	K_E,
	K_M,
	K_1,
	K_2,
	K_3,
	K_4,
	K_5,
	K_6,
	K_7,
	K_8,
	K_9,
	K_ENTER,
	K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
	S_INTRO,
	S_TITLE,
	S_GAME,
	S_GAMEOVER,
	S_INSTRUCTIONS,
	S_COUNT,
	S_CONTINUE
};
enum EWEAPONSTATES
{
	Hold,
	FireUp,
	FireDown,
	FireLeft,
	FireRight
};

enum ESTAGETYPE
{
	EMainMenu,
	EStage,
	EBoss,
	EBossBattle,
	EMinigame1,
	ETicTacToe
};

enum EMAINMENU
{
	MMStart,
	MMInstructions,
	MMExit,
	MMContinue
};

// struct for the game character
struct SGameChar
{
	COORD m_cLocation;
	bool  m_bActive;
};

struct SMinigame1
{
	COORD m_cLocation;
	bool  m_bActive;
	bool  m_bLeft;
};

struct SBossGaster
{
	COORD m_cLocation;
	bool  m_bActive;
	bool  m_bFire;
};

struct WeaponParameters
{
	std::string Name;
	int Clip; // Ammo in Clip
	int ClipMax; // Max size of Clip
	int AmmoTotal; // Total Ammo
	int Reload; // Reload Speed
	int ProjectileSpeed; // Projectile Speed
	int Range; // Range
};

void init(void);      // initialize your variables, allocate memory, etc
void boss_init();
void boss_battle_init();
void getInput(void);      // get input from player
void update(double dt); // update the game and the state of the game
void render(void);      // renders the current state of the game to the console
void shutdown(void);      // do clean up, free memory
void intro();
void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void minigame1_moveCharacter();
void moveCharacter();       // moves the character, collision detection, physics, etc
void boss_moveCharacter();
void bossbattle_moveCharacter();
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderIntro();
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderUI();			// renders the ui to the buffer
void renderCharacter();     // renders the character into the buffer
void renderGaster1();
void renderGaster2();
void renderGaster3();
void renderGaster4();
void renderEnemy1();
void renderEnemy2();
void renderEnemy3();
void renderEnemy4();
void renderEnemy5();
void renderEnemy6();
void renderbeat1();
void renderbeat2();
void renderbeat3();
void renderbeat4();
void renderDoor();
void renderWeapon();
void renderBossSpeech();
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void generate();
void sound();
void weapdata();
void reload();
void ost();
void gameOver();
void instructions();
void convertToString();
void save();
void continueSave();
void tictactoePlay();
void renderTicTacToe();
void tictactoeWin();
#endif // _GAME_H
