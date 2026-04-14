#pragma once

#include <cstdio>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#endif

#include "glut.h"

#ifndef _MSC_VER
#define sprintf_s snprintf
#endif

void iClear();
void iSetColor(double r, double g, double b);
void iRectangle(double left, double bottom, double dx, double dy);
void iFilledRectangle(double left, double bottom, double dx, double dy);
void iText(GLdouble x, GLdouble y, char* str, void* font);
void iLine(double x1, double y1, double x2, double y2);
unsigned int iLoadImage(char filename[]);
void iShowImage(int x, int y, int width, int height, unsigned int texture);
void iInitialize(int width, int height, char* title);
int iSetTimer(int msec, void (*f)(void));
void iStart();

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;
const double SCROLL_SPEED = 12.0;

enum AppState {
	STATE_BOOT_INTRO,
	STATE_MENU,
	STATE_START_INTRO,
	STATE_PLAY,
	STATE_OPTIONS,
	STATE_ABOUT,
	STATE_L1_TO_L2_INTRO,
	STATE_L2_TO_L3_INTRO,
	STATE_L3_TO_L4_INTRO,
	STATE_L4_COMPLETE_SCREEN,
	STATE_L4_END_SCREEN
};

enum GameLevel { LEVEL_01 = 1, LEVEL_02 = 2, LEVEL_03 = 3, LEVEL_04 = 4 };
enum ZombieType { ZOMBIE_NORMAL, ZOMBIE_ARMORED, ZOMBIE_FAST, ZOMBIE_MONSTER };

struct BtnRect { int x, y, w, h; };

struct Coin {
	double x;
	double yOffset;
	bool taken;
};

struct Fuel {
	double x;
	double yOffset;
	bool taken;
};

struct Bullet {
	double x;
	double y;
	bool active;
};

struct Zombie {
	double x;
	int frame;
	bool alive;
	ZombieType type;
	int health;
	int maxHealth;
};

extern AppState appState;
extern GameLevel currentLevel;
extern bool levelComplete;
extern bool gameOver;

extern int bootElapsedMs;
extern int startElapsedMs;
extern int l1ToL2ElapsedMs;
extern int l2ToL3ElapsedMs;
extern int l3ToL4ElapsedMs;
extern int l4EndElapsedMs;
extern int l4CompleteScreenElapsedMs;

extern int menuBgImg;
extern int optSoundBoxImg;
extern int optControlsBoxImg;
extern int musicOnImg;
extern int musicOffImg;
extern int sfxOnImg;
extern int sfxOffImg;
extern int aboutPanelImg;
extern int bootIntroImg;
extern int startIntroImg;
extern int levelCompleteImg;
extern int gameOverImg;
extern int l1ToL2Img;
extern int l2ToL3Img;
extern int l3ToL4Img;
extern int l4EndImg;

extern BtnRect btnStart;
extern BtnRect btnOptions;
extern BtnRect btnAbout;
extern BtnRect btnExit;
extern BtnRect btnMusicToggle;
extern BtnRect btnSfxToggle;
extern BtnRect btnAboutExit;
extern BtnRect btnSkip;

extern bool musicOn;
extern bool sfxOn;

extern bool levelCompleteSoundPlayed;
extern bool gameOverSoundPlayed;
extern bool gameplayBgmPlaying;

extern const char* SND_COIN_COLLECT;
extern const char* SND_FUEL_COLLECT;
extern const char* SND_GAME_OVER;
extern const char* SND_LEVEL_COMPLETE;
extern const char* SND_MENU_CLICK;
extern const char* SND_ZOMBIE_HIT;
extern const char* SND_GAMEPLAY_BGM;

extern int bgL1Img;
extern int bgL2Img;
extern int bgL3Img;
extern int bgL4Img;
extern int coinImg;
extern int fuelImg;
extern int bulletImg;
extern int fuelLabelImg;
extern int boostLabelImg;

extern int carL1Img[7];
extern int carL1AnimTick;
extern int carL2Img[7];
extern int carL2AnimTick;
extern int carL3Img[7];
extern int carL3AnimTick;

extern int l4RobotIdleImg;
extern int l4RobotWalkImg[4];
extern int l4RobotJumpImg;
extern int l4RobotAnimTick;

extern int normalZombieImg[8];
extern int armoredZombieImg[4];
extern int fastZombieImg[4];
extern int monsterZombieImg[7];

extern const int CAR_L1_W;
extern const int CAR_L1_H;
extern const int CAR_L2_W;
extern const int CAR_L2_H;
extern const int CAR_L3_W;
extern const int CAR_L3_H;
extern const int ROBOT_W;
extern const int ROBOT_H;
extern const int COIN_W;
extern const int COIN_H;
extern const int FUEL_W;
extern const int FUEL_H;
extern const int BULLET_W_L2;
extern const int BULLET_H_L2;
extern const int BULLET_W_L3;
extern const int BULLET_H_L3;
extern const int BULLET_W_L4;
extern const int BULLET_H_L4;

extern const double BULLET_SPEED_L2;
extern const double BULLET_SPEED_L3;
extern const double BULLET_SPEED_L4;
extern const int TARGET_COINS_L1;
extern const int TARGET_COINS_L2;
extern const int TARGET_COINS_L3;
extern const int TARGET_COINS_L4;
extern const int EXTRA_COINS_L1;
extern const int EXTRA_COINS_L2;
extern const int EXTRA_COINS_L3;
extern const int EXTRA_COINS_L4;
extern const double MAX_FUEL;
extern double fuelLevel;
extern const double FUEL_DEC_L1;
extern const double FUEL_DEC_L2;
extern const double FUEL_DEC_L3;
extern const double FUEL_DEC_L4;
extern const double FUEL_ADD_L1;
extern const double FUEL_ADD_L2;
extern const double FUEL_ADD_L3;
extern const double FUEL_ADD_L4;
extern const double SHOOT_COST_L2;
extern const double SHOOT_COST_L3;
extern const double SHOOT_COST_L4;

extern const int FUEL_COUNT_L1;
extern const int FUEL_COUNT_L2;
extern const int FUEL_COUNT_L3;
extern const int FUEL_COUNT_L4;
extern const double FUEL_START_X_L1;
extern const double FUEL_START_X_L2;
extern const double FUEL_START_X_L3;
extern const double FUEL_START_X_L4;
extern const double FUEL_GAP_L1;
extern const double FUEL_GAP_L2;
extern const double FUEL_GAP_L3;
extern const double FUEL_GAP_L4;

extern const int HUD_TOP_Y;
extern const int HUD_FUEL_BAR_X;
extern const int HUD_FUEL_BAR_Y;
extern const int FUEL_BAR_W;
extern const int FUEL_BAR_H;
extern const int HUD_FUEL_ICON_W;
extern const int HUD_FUEL_ICON_H;
extern const int HUD_BOOST_ICON_W;
extern const int HUD_BOOST_ICON_H;
extern const int HUD_ICON_GAP;
extern const int BOOST_BAR_GAP_Y;
extern const int HUD_FUEL_NUM_X;
extern const int HUD_TEXT_X;
extern const double LOW_FUEL_RATIO;
extern int fuelBlink;

extern double boostBar;
extern const double BOOST_PER_COIN;
extern const double BOOST_AFTER_USE;
extern bool jumpActive;
extern double jumpY;
extern double jumpVx;
extern double jumpVy;
extern double l4JumpBaseY;
extern const double JUMP_SPEED;
extern const double JUMP_ANGLE_DEG;
extern const double GRAVITY_PER_TICK;

extern double playerWorldX;
extern int playerScreenX;
extern bool rightHeld;
extern bool leftHeld;
extern int bgX;
extern int collectedCoins;

extern std::vector<Coin> coins;
extern std::vector<Fuel> fuels;
extern std::vector<Bullet> bullets;
extern int shootCooldown;
extern const int SHOOT_COOLDOWN_TICKS;
extern std::vector<Zombie> zombies;
extern int zombieSpawnCounter;

extern const double ZOMBIE_SPEED_NORMAL;
extern const double ZOMBIE_SPEED_FAST;
extern const int ZOMBIE_SPAWN_MIN;
extern const int ZOMBIE_SPAWN_MAX;
extern const int ZOMBIE_SPAWN_DELAY_L1;
extern const int ZOMBIE_SPAWN_CHANCE_L1;
extern const int ZOMBIE_EXTRA_SPAWN_CHANCE_L1;
extern const int MAX_ZOMBIES_ON_SCREEN_L1;
extern const int ZOMBIE_SPAWN_DELAY_L2;
extern const int ZOMBIE_SPAWN_CHANCE_L2;
extern const int ZOMBIE_EXTRA_SPAWN_CHANCE_L2;
extern const int MAX_ZOMBIES_ON_SCREEN_L2;
extern const int ZOMBIE_SPAWN_DELAY_L3;
extern const int ZOMBIE_SPAWN_CHANCE_L3;
extern const int ZOMBIE_EXTRA_SPAWN_CHANCE_L3;
extern const int MAX_ZOMBIES_ON_SCREEN_L3;
extern const int ZOMBIE_SPAWN_DELAY_L4;
extern const int ZOMBIE_SPAWN_CHANCE_L4;
extern const int ZOMBIE_EXTRA_SPAWN_CHANCE_L4;
extern const int MAX_ZOMBIES_ON_SCREEN_L4;

extern const int L1_NORMAL_ZOMBIE_HEALTH;
extern const int L2_NORMAL_ZOMBIE_HEALTH;
extern const int L2_ARMORED_ZOMBIE_HEALTH;
extern const int L3_ARMORED_ZOMBIE_HEALTH;
extern const int L3_FAST_ZOMBIE_HEALTH;
extern const int L4_FAST_ZOMBIE_HEALTH;
extern const int L4_MONSTER_ZOMBIE_HEALTH;
extern const int ZOMBIE_HEALTH_BAR_W;
extern const int ZOMBIE_HEALTH_BAR_H;
extern const int ZOMBIE_HEALTH_BAR_GAP;

extern const int ZOMBIE_NORMAL_W_L1;
extern const int ZOMBIE_NORMAL_H_L1;
extern const int ZOMBIE_NORMAL_W_L2;
extern const int ZOMBIE_NORMAL_H_L2;
extern const int ZOMBIE_ARMORED_W_L2;
extern const int ZOMBIE_ARMORED_H_L2;
extern const int ZOMBIE_ARMORED_W_L3;
extern const int ZOMBIE_ARMORED_H_L3;
extern const int ZOMBIE_FAST_W_L3;
extern const int ZOMBIE_FAST_H_L3;
extern const int ZOMBIE_FAST_W_L4;
extern const int ZOMBIE_FAST_H_L4;
extern const int ZOMBIE_MONSTER_W_L4;
extern const int ZOMBIE_MONSTER_H_L4;

extern const int L2_ROAD_SURFACE_THICK;
extern const int L2_ROAD_HIGHLIGHT_THICK;
extern const int L2_ROCK_LAYER_THICK;
extern const int REAR_WHEEL_X;
extern const int WHEEL_CONTACT_FROM_BOTTOM;
extern const int CAR_EXTRA_DROP;
extern const int ROBOT_ROAD_GAP;
extern int gGroundRear;
extern int gGroundFront;
extern double gCarRotationAngle;

bool pointInRect(int mx, int my, const BtnRect& r);
int getCurrentCarWidth();
int getCurrentCarHeight();
int getFrontWheelOffset();
double getCurrentBulletSpeed();
int getCurrentZombieSpawnDelay();
int getCurrentZombieSpawnChance();
int getCurrentZombieExtraSpawnChance();
int getCurrentMaxZombiesOnScreen();
double terrainY_Common(double x);
double terrainY(double worldX);
double terrainSlopeAngle(double worldX);
bool isRobotLevel();
int carBaseDrawY();
int robotBaseDrawY();
int playerDrawY();
bool isUphill();
bool isDownhill();
bool isFlatRoad();
int getCarImage(int* carImages, int animTick, bool moving, bool uphill, bool downhill);
void setLevel01RoadMainColor();
void setLevel01RoadHighlightColor();
void setLevel01UndergroundDeepColor();
void setLevel01UndergroundMidColor();
void setLevel02RoadMainColor();
void setLevel02RoadHighlightColor();
void setLevel02UndergroundDeepColor();
void setLevel02UndergroundMidColor();
void setLevel03RoadMainColor();
void setLevel03RoadHighlightColor();
void setLevel03UndergroundDeepColor();
void setLevel03UndergroundMidColor();
void setLevel04RoadMainColor();
void setLevel04RoadHighlightColor();
void setLevel04UndergroundDeepColor();
void setLevel04UndergroundMidColor();
void setLevelRoadMainColor();
void setLevelRoadHighlightColor();
void setLevelUndergroundDeepColor();
void setLevelUndergroundMidColor();
int randInt(int a, int b);
bool aabbOverlap(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh);
int currentTargetCoins();
int currentTotalCoinsSpawn();
double currentFuelDecPerTick();
double currentFuelAddPerPick();
double currentShootCost();
int currentFuelCount();
double currentFuelStartX();
double currentFuelGap();
bool boostAvailableForThisLevel();
double zombieSpeed(ZombieType t);
int zombieWidthForCurrentLevel(ZombieType t);
int zombieHeightForCurrentLevel(ZombieType t);
int zombieWidth(ZombieType t);
int zombieHeight(ZombieType t);
int zombieMaxHealthForCurrentLevel(ZombieType t);
ZombieType rollZombieType();
int getZombieFrameCount(ZombieType type);
int getLevel04Background();
int getLevel04CharacterImage(bool moving);
int getZombieImage(ZombieType type, int frame);
void playRawSound(const char* path);
void stopEffectSound();
void startGameplayBgm();
void stopGameplayBgm();
void updateGameplayBgm();
void playMenuClickSound();
void playCoinCollectSound();
void playFuelCollectSound();
void playGameOverSound();
void playLevelCompleteSound();
void playZombieHitSound();
void setGameOver();
void setLevelComplete();
void checkFuelEmptyGameOver();
void resetBoostForLevel();
void addBoostFromCoin();
void applyBoostJump();
void updateJumpPhysics();
void spawnFuelDropAt(double worldX);
void initCoins();
void checkCoinCollect();
void initFuel();
void checkFuelCollect();
int getCurrentBulletWidth();
int getCurrentBulletHeight();
void shoot();
bool bulletHitsTerrain(const Bullet& b);
void updateBullets();
void clearZombies();
void spawnZombieAhead();
bool bulletHitsZombie(const Bullet& b, const Zombie& z);
void handleZombieDeath(const Zombie& z);
void damageZombie(Zombie& z, int dmg);
void updateZombies();
void commonLevelStart(double carriedFuel);
void startLevel01();
void startLevel02(double carriedFuel);
void startLevel03(double carriedFuel);
void startLevel04(double carriedFuel);
void updateGame();
void drawBoostHUD();
void drawHUD();
void drawUnderground();
void drawRoad();
void drawCoins();
void drawFuel();
void drawBullets();
void drawZombieHealthBar(const Zombie& z, int drawX, int drawY, int zw, int zh);
void drawZombies();
void drawPlay();
void drawMenu();
void drawAbout();
void drawOptions();
void drawSkipBox();
void drawBootIntro();
void drawStartIntro();
void drawL1ToL2Intro();
void drawL2ToL3Intro();
void drawL3ToL4Intro();
void drawL4CompleteScreen();
void drawL4EndScreen();
void iDraw();
void iMouse(int button, int state, int mx, int my);
void iMouseMove(int mx, int my);
void iPassiveMouseMove(int mx, int my);
void iKeyboard(unsigned char key);
void iSpecialKeyboard(unsigned char key);
void loadZombieAssets();
void loadLevel1CarImages();
void loadLevel2CarImages();
void loadLevel3CarImages();
void loadLevel04Background();
void loadLevel04CharacterImages();
void initUI();
void loadGameAssets();