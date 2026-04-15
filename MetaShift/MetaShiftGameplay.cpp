#include "MetaShiftShared.hpp"

AppState appState = STATE_BOOT_INTRO;
GameLevel currentLevel = LEVEL_01;
bool levelComplete = false;
bool gameOver = false;

int bootElapsedMs = 0;
int startElapsedMs = 0;
int l1ToL2ElapsedMs = 0;
int l2ToL3ElapsedMs = 0;
int l3ToL4ElapsedMs = 0;
int l4EndElapsedMs = 0;
int l4CompleteScreenElapsedMs = 0;

bool musicOn = true;
bool sfxOn = true;

bool levelCompleteSoundPlayed = false;
bool gameOverSoundPlayed = false;
bool gameplayBgmPlaying = false;

const char* SND_COIN_COLLECT = "Sounds//coin_collect.wav";
const char* SND_FUEL_COLLECT = "Sounds//fuel_collect.wav";
const char* SND_GAME_OVER = "Sounds//game_over.wav";
const char* SND_LEVEL_COMPLETE = "Sounds//level_complete.wav";
const char* SND_MENU_CLICK = "Sounds//menu_click.wav";
const char* SND_ZOMBIE_HIT = "Sounds//zombie_hit.wav";
const char* SND_GAMEPLAY_BGM = "Sounds//gameplay.wav";

int menuBgImg = 0;
int optSoundBoxImg = 0;
int optControlsBoxImg = 0;
int musicOnImg = 0;
int musicOffImg = 0;
int sfxOnImg = 0;
int sfxOffImg = 0;
int aboutPanelImg = 0;
int bootIntroImg = 0;
int startIntroImg = 0;
int levelCompleteImg = 0;
int gameOverImg = 0;
int l1ToL2Img = 0;
int l2ToL3Img = 0;
int l3ToL4Img = 0;
int l4EndImg = 0;

BtnRect btnStart = { 0, 0, 0, 0 };
BtnRect btnOptions = { 0, 0, 0, 0 };
BtnRect btnAbout = { 0, 0, 0, 0 };
BtnRect btnExit = { 0, 0, 0, 0 };
BtnRect btnMusicToggle = { 0, 0, 0, 0 };
BtnRect btnSfxToggle = { 0, 0, 0, 0 };
BtnRect btnAboutExit = { 0, 0, 0, 0 };
BtnRect btnSkip = { 0, 0, 0, 0 };

int bgL1Img = 0, bgL2Img = 0, bgL3Img = 0, bgL4Img = 0;
int coinImg = 0, fuelImg = 0, bulletImg = 0;
int fuelLabelImg = 0, boostLabelImg = 0;

int carL1Img[7] = { 0, 0, 0, 0, 0, 0, 0 };
int carL1AnimTick = 0;
int carL2Img[7] = { 0, 0, 0, 0, 0, 0, 0 };
int carL2AnimTick = 0;
int carL3Img[7] = { 0, 0, 0, 0, 0, 0, 0 };
int carL3AnimTick = 0;

int l4RobotIdleImg = 0;
int l4RobotWalkImg[4] = { 0, 0, 0, 0 };
int l4RobotJumpImg = 0;
int l4RobotAnimTick = 0;

int normalZombieImg[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int armoredZombieImg[4] = { 0, 0, 0, 0 };
int fastZombieImg[4] = { 0, 0, 0, 0 };
int monsterZombieImg[7] = { 0, 0, 0, 0, 0, 0, 0 };


// Car & Robot Size

const int CAR_L1_W = 140;
const int CAR_L1_H = 120;

const int CAR_L2_W = 160;
const int CAR_L2_H = 110;

const int CAR_L3_W = 190;
const int CAR_L3_H = 160;

const int ROBOT_W = 110;
const int ROBOT_H = 130;


// Coin, Fuel, Bullet Size

const int COIN_W = 40;
const int COIN_H = 40;

const int FUEL_W = 60;
const int FUEL_H = 40;

const int BULLET_W_L2 = 20;
const int BULLET_H_L2 = 20;

const int BULLET_W_L3 = 24;
const int BULLET_H_L3 = 24;

const int BULLET_W_L4 = 32;
const int BULLET_H_L4 = 32;


// Bullet Speed in Level

const double BULLET_SPEED_L2 = 14.0;
const double BULLET_SPEED_L3 = 25.0;
const double BULLET_SPEED_L4 = 30.0;


// Coin Target in Level

const int TARGET_COINS_L1 = 10;
const int TARGET_COINS_L2 = 10;
const int TARGET_COINS_L3 = 50;
const int TARGET_COINS_L4 = 100;


// Extra Coin in Level

const int EXTRA_COINS_L1 = 40;
const int EXTRA_COINS_L2 = 80;
const int EXTRA_COINS_L3 = 120;
const int EXTRA_COINS_L4 = 140;


// Max Fuel Level

const double MAX_FUEL = 100.0;
double fuelLevel = MAX_FUEL;


// Fuel Reduction in Level

const double FUEL_DEC_L1 = 0.18;
const double FUEL_DEC_L2 = 0.18;
const double FUEL_DEC_L3 = 0.22;
const double FUEL_DEC_L4 = 0.25;


// Fuel Addition in Level

const double FUEL_ADD_L1 = 22.0;
const double FUEL_ADD_L2 = 22.0;
const double FUEL_ADD_L3 = 35.0;
const double FUEL_ADD_L4 = 30.0;


// Shooting Cost in Level

const double SHOOT_COST_L2 = 2;
const double SHOOT_COST_L3 = 2;
const double SHOOT_COST_L4 = 1;


// Fuel Number in Level

const int FUEL_COUNT_L1 = 13;
const int FUEL_COUNT_L2 = 15;
const int FUEL_COUNT_L3 = 70;
const int FUEL_COUNT_L4 = 5;


// Fuel Start in Level

const double FUEL_START_X_L1 = 900;
const double FUEL_START_X_L2 = 900;
const double FUEL_START_X_L3 = 900;
const double FUEL_START_X_L4 = 900;


// Fuel Gap in Level

const double FUEL_GAP_L1 = 1200;
const double FUEL_GAP_L2 = 1400;
const double FUEL_GAP_L3 = 1600;
const double FUEL_GAP_L4 = 1800;


// Fuel & Boost Bar & Icon 

const int HUD_TOP_Y = SCREEN_HEIGHT - 30;
const int HUD_FUEL_BAR_X = 95;
const int HUD_FUEL_BAR_Y = HUD_TOP_Y - 24;
const int FUEL_BAR_W = 280;
const int FUEL_BAR_H = 24;
const int HUD_FUEL_ICON_W = 60;
const int HUD_FUEL_ICON_H = 42;
const int HUD_BOOST_ICON_W = 65;
const int HUD_BOOST_ICON_H = 46;
const int HUD_ICON_GAP = 16;
const int BOOST_BAR_GAP_Y = 38;
const int HUD_FUEL_NUM_X = HUD_FUEL_BAR_X + FUEL_BAR_W + 18;
const int HUD_TEXT_X = 780;
const double LOW_FUEL_RATIO = 0.30;
int fuelBlink = 0;


// Boost 

double boostBar = 0.0;
const double BOOST_PER_COIN = 10.0;
const double BOOST_AFTER_USE = 30.0;
bool jumpActive = false;
double jumpY = 0.0;
double jumpVx = 0.0;
double jumpVy = 0.0;
double l4JumpBaseY = 0.0;
const double JUMP_SPEED = 25.0;
const double JUMP_ANGLE_DEG = 80.0;
const double GRAVITY_PER_TICK = 1.8;

double playerWorldX = 0;
int playerScreenX = 120;
bool rightHeld = false;
bool leftHeld = false;
int bgX = 0;
int collectedCoins = 0;

std::vector<Coin> coins;
std::vector<Fuel> fuels;
std::vector<Bullet> bullets;
int shootCooldown = 0;
const int SHOOT_COOLDOWN_TICKS = 10;


const double ZOMBIE_SPEED_NORMAL = 4.0;
const double ZOMBIE_SPEED_FAST = 6.5;
const int ZOMBIE_SPAWN_MIN = 170;
const int ZOMBIE_SPAWN_MAX = 450;


// Zombie in Levels

const int ZOMBIE_SPAWN_DELAY_L1 = 90;
const int ZOMBIE_SPAWN_CHANCE_L1 = 50;
const int ZOMBIE_EXTRA_SPAWN_CHANCE_L1 = 0;
const int MAX_ZOMBIES_ON_SCREEN_L1 = 4;

const int ZOMBIE_SPAWN_DELAY_L2 = 70;
const int ZOMBIE_SPAWN_CHANCE_L2 = 65;
const int ZOMBIE_EXTRA_SPAWN_CHANCE_L2 = 0;
const int MAX_ZOMBIES_ON_SCREEN_L2 = 6;

const int ZOMBIE_SPAWN_DELAY_L3 = 100;
const int ZOMBIE_SPAWN_CHANCE_L3 = 90;
const int ZOMBIE_EXTRA_SPAWN_CHANCE_L3 = 0;
const int MAX_ZOMBIES_ON_SCREEN_L3 = 8;

const int ZOMBIE_SPAWN_DELAY_L4 = 70;
const int ZOMBIE_SPAWN_CHANCE_L4 = 100;
const int ZOMBIE_EXTRA_SPAWN_CHANCE_L4 = 35;
const int MAX_ZOMBIES_ON_SCREEN_L4 = 10;


// Zombie Health in Levels

const int L1_NORMAL_ZOMBIE_HEALTH = 1;

const int L2_NORMAL_ZOMBIE_HEALTH = 1;
const int L2_ARMORED_ZOMBIE_HEALTH = 2;

const int L3_ARMORED_ZOMBIE_HEALTH = 2;
const int L3_FAST_ZOMBIE_HEALTH = 3;

const int L4_FAST_ZOMBIE_HEALTH = 3;
const int L4_MONSTER_ZOMBIE_HEALTH = 4;


// Zombie Health Bar

const int ZOMBIE_HEALTH_BAR_W = 52;
const int ZOMBIE_HEALTH_BAR_H = 6;
const int ZOMBIE_HEALTH_BAR_GAP = 10;


// Zombie Size in Levels

const int ZOMBIE_NORMAL_W_L1 = 70;
const int ZOMBIE_NORMAL_H_L1 = 70;

const int ZOMBIE_NORMAL_W_L2 = 70;
const int ZOMBIE_NORMAL_H_L2 = 70;
const int ZOMBIE_ARMORED_W_L2 = 85;
const int ZOMBIE_ARMORED_H_L2 = 85;

const int ZOMBIE_ARMORED_W_L3 = 110;
const int ZOMBIE_ARMORED_H_L3 = 110;
const int ZOMBIE_FAST_W_L3 = 160;
const int ZOMBIE_FAST_H_L3 = 160;

const int ZOMBIE_FAST_W_L4 = 160;
const int ZOMBIE_FAST_H_L4 = 160;
const int ZOMBIE_MONSTER_W_L4 = 200;
const int ZOMBIE_MONSTER_H_L4 = 200;


// Terrain 

const int L2_ROAD_SURFACE_THICK = 22;
const int L2_ROAD_HIGHLIGHT_THICK = 6;
const int L2_ROCK_LAYER_THICK = 34;
const int REAR_WHEEL_X = 30;
const int WHEEL_CONTACT_FROM_BOTTOM = 12;
const int CAR_EXTRA_DROP = 10;
const int ROBOT_ROAD_GAP = 28;

std::vector<Zombie> zombies;
int zombieSpawnCounter = 0;

int gGroundRear = 0;
int gGroundFront = 0;
double gCarRotationAngle = 0.0;

bool pointInRect(int mx, int my, const BtnRect& r) {
	return (mx >= r.x && mx <= r.x + r.w && my >= r.y && my <= r.y + r.h);
}

void playRawSound(const char* path) {
#ifdef _WIN32
	PlaySoundA(path, NULL, SND_FILENAME | SND_ASYNC);
#else
	(void)path;
#endif
}

void stopEffectSound() {
#ifdef _WIN32
	PlaySoundA(NULL, NULL, 0);
#endif
}

void startGameplayBgm() {
#ifdef _WIN32
	if (gameplayBgmPlaying) return;
	PlaySoundA(SND_GAMEPLAY_BGM, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	gameplayBgmPlaying = true;
#endif
}

void stopGameplayBgm() {
#ifdef _WIN32
	if (!gameplayBgmPlaying) return;
	PlaySoundA(NULL, NULL, 0);
	gameplayBgmPlaying = false;
#endif
}

void updateGameplayBgm() {
	if (appState == STATE_PLAY && musicOn) startGameplayBgm();
	else stopGameplayBgm();
}

void playMenuClickSound() {
	if (!sfxOn) return;
	if (appState == STATE_PLAY) return;
	playRawSound(SND_MENU_CLICK);
}

void playCoinCollectSound() {
	if (!sfxOn) return;
	playRawSound(SND_COIN_COLLECT);
}

void playFuelCollectSound() {
	if (!sfxOn) return;
	playRawSound(SND_FUEL_COLLECT);
}

void playGameOverSound() {
	if (!sfxOn) return;
	if (gameOverSoundPlayed) return;
	gameOverSoundPlayed = true;
	playRawSound(SND_GAME_OVER);
}

void playLevelCompleteSound() {
	if (!sfxOn) return;
	if (levelCompleteSoundPlayed) return;
	levelCompleteSoundPlayed = true;
	playRawSound(SND_LEVEL_COMPLETE);
}

void playZombieHitSound() {
	if (!sfxOn) return;
	playRawSound(SND_ZOMBIE_HIT);
}

int getCurrentCarWidth() {
	if (currentLevel == LEVEL_01) return CAR_L1_W;
	if (currentLevel == LEVEL_02) return CAR_L2_W;
	if (currentLevel == LEVEL_03) return CAR_L3_W;
	return CAR_L1_W;
}

int getCurrentCarHeight() {
	if (currentLevel == LEVEL_01) return CAR_L1_H;
	if (currentLevel == LEVEL_02) return CAR_L2_H;
	if (currentLevel == LEVEL_03) return CAR_L3_H;
	return CAR_L1_H;
}

int getFrontWheelOffset() {
	int carW = getCurrentCarWidth();
	return carW - 30;
}

double getCurrentBulletSpeed() {
	if (currentLevel == LEVEL_02) return BULLET_SPEED_L2;
	if (currentLevel == LEVEL_03) return BULLET_SPEED_L3;
	if (currentLevel == LEVEL_04) return BULLET_SPEED_L4;
	return 0;
}

int getCurrentZombieSpawnDelay() {
	if (currentLevel == LEVEL_01) return ZOMBIE_SPAWN_DELAY_L1;
	if (currentLevel == LEVEL_02) return ZOMBIE_SPAWN_DELAY_L2;
	if (currentLevel == LEVEL_03) return ZOMBIE_SPAWN_DELAY_L3;
	return ZOMBIE_SPAWN_DELAY_L4;
}

int getCurrentZombieSpawnChance() {
	if (currentLevel == LEVEL_01) return ZOMBIE_SPAWN_CHANCE_L1;
	if (currentLevel == LEVEL_02) return ZOMBIE_SPAWN_CHANCE_L2;
	if (currentLevel == LEVEL_03) return ZOMBIE_SPAWN_CHANCE_L3;
	return ZOMBIE_SPAWN_CHANCE_L4;
}

int getCurrentZombieExtraSpawnChance() {
	if (currentLevel == LEVEL_01) return ZOMBIE_EXTRA_SPAWN_CHANCE_L1;
	if (currentLevel == LEVEL_02) return ZOMBIE_EXTRA_SPAWN_CHANCE_L2;
	if (currentLevel == LEVEL_03) return ZOMBIE_EXTRA_SPAWN_CHANCE_L3;
	return ZOMBIE_EXTRA_SPAWN_CHANCE_L4;
}

int getCurrentMaxZombiesOnScreen() {
	if (currentLevel == LEVEL_01) return MAX_ZOMBIES_ON_SCREEN_L1;
	if (currentLevel == LEVEL_02) return MAX_ZOMBIES_ON_SCREEN_L2;
	if (currentLevel == LEVEL_03) return MAX_ZOMBIES_ON_SCREEN_L3;
	return MAX_ZOMBIES_ON_SCREEN_L4;
}

double terrainY_Common(double x) {
	double base = 145.0;
	double y = base
		+ 22.0 * sin(x * 0.010)
		+ 10.0 * sin(x * 0.022)
		+ 6.0 * sin(x * 0.045);

	if (currentLevel == LEVEL_04) {
		y += 8.0 * sin(x * 0.006);
	}

	if (y < 105) y = 105;
	if (y > 220) y = 220;
	return y;
}

double terrainY(double worldX) {
	return terrainY_Common(worldX);
}

double terrainSlopeAngle(double worldX) {
	double delta = 5.0;
	double y1 = terrainY(worldX - delta);
	double y2 = terrainY(worldX + delta);
	double slope = (y2 - y1) / (2.0 * delta);
	double angleRad = atan(slope);
	return angleRad * 180.0 / 3.14159265358979323846;
}

bool isRobotLevel() {
	return currentLevel == LEVEL_04;
}

int carBaseDrawY() {
	int carW = getCurrentCarWidth();
	int rearX = (int)(playerWorldX + playerScreenX + REAR_WHEEL_X);
	int frontX = (int)(playerWorldX + playerScreenX + getFrontWheelOffset());

	gGroundRear = (int)terrainY(rearX);
	gGroundFront = (int)terrainY(frontX);

	double angleRear = terrainSlopeAngle(rearX);
	double angleFront = terrainSlopeAngle(frontX);
	gCarRotationAngle = (angleRear + angleFront) / 2.0;

	int groundY = (gGroundRear > gGroundFront) ? gGroundRear : gGroundFront;
	(void)carW;
	return groundY - WHEEL_CONTACT_FROM_BOTTOM - CAR_EXTRA_DROP;
}

int robotBaseDrawY() {
	double footX = playerWorldX + playerScreenX + 55;
	int groundY = (int)terrainY(footX);
	return groundY + ROBOT_ROAD_GAP;
}

int playerDrawY() {
	if (isRobotLevel()) {
		if (jumpActive) return (int)(l4JumpBaseY + jumpY);
		return robotBaseDrawY();
	}
	return carBaseDrawY() + (int)jumpY;
}

bool isUphill() {
	double angleDiff = terrainSlopeAngle(playerWorldX + playerScreenX + getCurrentCarWidth() / 2);
	return angleDiff > 5.0;
}

bool isDownhill() {
	double angleDiff = terrainSlopeAngle(playerWorldX + playerScreenX + getCurrentCarWidth() / 2);
	return angleDiff < -5.0;
}

bool isFlatRoad() {
	double angleDiff = terrainSlopeAngle(playerWorldX + playerScreenX + getCurrentCarWidth() / 2);
	return angleDiff >= -5.0 && angleDiff <= 5.0;
}

int getCarImage(int* carImages, int animTick, bool moving, bool uphill, bool downhill) {
	if (!moving) {
		return carImages[3];
	}

	if (uphill) {
		int frame = (animTick / 6) % 3;
		return carImages[frame];
	}

	if (downhill) {
		int frame = 4 + ((animTick / 6) % 3);
		return carImages[frame];
	}

	return carImages[3];
}


// Road Colors

void setLevel01RoadMainColor() { iSetColor(118, 168, 62); }
void setLevel01RoadHighlightColor() { iSetColor(170, 220, 95); }
void setLevel01UndergroundDeepColor() { iSetColor(130, 80, 35); }
void setLevel01UndergroundMidColor() { iSetColor(160, 105, 50); }

void setLevel02RoadMainColor() { iSetColor(205, 165, 65); }
void setLevel02RoadHighlightColor() { iSetColor(235, 200, 90); }
void setLevel02UndergroundDeepColor() { iSetColor(90, 60, 35); }
void setLevel02UndergroundMidColor() { iSetColor(120, 85, 55); }

void setLevel03RoadMainColor() { iSetColor(134, 110, 106); }
void setLevel03RoadHighlightColor() { iSetColor(185, 155, 145); }
void setLevel03UndergroundDeepColor() { iSetColor(48, 44, 59); }
void setLevel03UndergroundMidColor() { iSetColor(78, 70, 88); }

void setLevel04RoadMainColor() { iSetColor(92, 50, 48); }
void setLevel04RoadHighlightColor() { iSetColor(92, 50, 48); }
void setLevel04UndergroundDeepColor() { iSetColor(44, 29, 31); }
void setLevel04UndergroundMidColor() { iSetColor(44, 29, 31); }



void setLevelRoadMainColor() {
	if (currentLevel == LEVEL_01) setLevel01RoadMainColor();
	else if (currentLevel == LEVEL_02) setLevel02RoadMainColor();
	else if (currentLevel == LEVEL_03) setLevel03RoadMainColor();
	else if (currentLevel == LEVEL_04) setLevel04RoadMainColor();
}

void setLevelRoadHighlightColor() {
	if (currentLevel == LEVEL_01) setLevel01RoadHighlightColor();
	else if (currentLevel == LEVEL_02) setLevel02RoadHighlightColor();
	else if (currentLevel == LEVEL_03) setLevel03RoadHighlightColor();
	else if (currentLevel == LEVEL_04) setLevel04RoadHighlightColor();
}

void setLevelUndergroundDeepColor() {
	if (currentLevel == LEVEL_01) setLevel01UndergroundDeepColor();
	else if (currentLevel == LEVEL_02) setLevel02UndergroundDeepColor();
	else if (currentLevel == LEVEL_03) setLevel03UndergroundDeepColor();
	else if (currentLevel == LEVEL_04) setLevel04UndergroundDeepColor();
}

void setLevelUndergroundMidColor() {
	if (currentLevel == LEVEL_01) setLevel01UndergroundMidColor();
	else if (currentLevel == LEVEL_02) setLevel02UndergroundMidColor();
	else if (currentLevel == LEVEL_03) setLevel03UndergroundMidColor();
	else if (currentLevel == LEVEL_04) setLevel04UndergroundMidColor();
}

int randInt(int a, int b) { return a + (rand() % (b - a + 1)); }

bool aabbOverlap(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh) {
	return ax < bx + bw && ax + aw > bx && ay < by + bh && ay + ah > by;
}

int currentTargetCoins() {
	if (currentLevel == LEVEL_01) return TARGET_COINS_L1;
	if (currentLevel == LEVEL_02) return TARGET_COINS_L2;
	if (currentLevel == LEVEL_03) return TARGET_COINS_L3;
	return TARGET_COINS_L4;
}

int currentTotalCoinsSpawn() {
	if (currentLevel == LEVEL_01) return TARGET_COINS_L1 + EXTRA_COINS_L1;
	if (currentLevel == LEVEL_02) return TARGET_COINS_L2 + EXTRA_COINS_L2;
	if (currentLevel == LEVEL_03) return TARGET_COINS_L3 + EXTRA_COINS_L3;
	return TARGET_COINS_L4 + EXTRA_COINS_L4;
}

double currentFuelDecPerTick() {
	if (currentLevel == LEVEL_01) return FUEL_DEC_L1;
	if (currentLevel == LEVEL_02) return FUEL_DEC_L2;
	if (currentLevel == LEVEL_03) return FUEL_DEC_L3;
	return FUEL_DEC_L4;
}

double currentFuelAddPerPick() {
	if (currentLevel == LEVEL_01) return FUEL_ADD_L1;
	if (currentLevel == LEVEL_02) return FUEL_ADD_L2;
	if (currentLevel == LEVEL_03) return FUEL_ADD_L3;
	return FUEL_ADD_L4;
}

double currentShootCost() {
	if (currentLevel == LEVEL_02) return SHOOT_COST_L2;
	if (currentLevel == LEVEL_03) return SHOOT_COST_L3;
	if (currentLevel == LEVEL_04) return SHOOT_COST_L4;
	return 9999.0;
}

int currentFuelCount() {
	if (currentLevel == LEVEL_01) return FUEL_COUNT_L1;
	if (currentLevel == LEVEL_02) return FUEL_COUNT_L2;
	if (currentLevel == LEVEL_03) return FUEL_COUNT_L3;
	return FUEL_COUNT_L4;
}

double currentFuelStartX() {
	if (currentLevel == LEVEL_01) return FUEL_START_X_L1;
	if (currentLevel == LEVEL_02) return FUEL_START_X_L2;
	if (currentLevel == LEVEL_03) return FUEL_START_X_L3;
	return FUEL_START_X_L4;
}

double currentFuelGap() {
	if (currentLevel == LEVEL_01) return FUEL_GAP_L1;
	if (currentLevel == LEVEL_02) return FUEL_GAP_L2;
	if (currentLevel == LEVEL_03) return FUEL_GAP_L3;
	return FUEL_GAP_L4;
}

bool boostAvailableForThisLevel() {
	return (currentLevel == LEVEL_02 || currentLevel == LEVEL_03 || currentLevel == LEVEL_04);
}

double zombieSpeed(ZombieType t) {
	if (t == ZOMBIE_FAST) return ZOMBIE_SPEED_FAST;
	return ZOMBIE_SPEED_NORMAL;
}

int zombieWidthForCurrentLevel(ZombieType t) {
	if (currentLevel == LEVEL_01) {
		return ZOMBIE_NORMAL_W_L1;
	}
	else if (currentLevel == LEVEL_02) {
		if (t == ZOMBIE_ARMORED) return ZOMBIE_ARMORED_W_L2;
		return ZOMBIE_NORMAL_W_L2;
	}
	else if (currentLevel == LEVEL_03) {
		if (t == ZOMBIE_FAST) return ZOMBIE_FAST_W_L3;
		return ZOMBIE_ARMORED_W_L3;
	}
	else {
		if (t == ZOMBIE_FAST) return ZOMBIE_FAST_W_L4;
		return ZOMBIE_MONSTER_W_L4;
	}
}

int zombieHeightForCurrentLevel(ZombieType t) {
	if (currentLevel == LEVEL_01) {
		return ZOMBIE_NORMAL_H_L1;
	}
	else if (currentLevel == LEVEL_02) {
		if (t == ZOMBIE_ARMORED) return ZOMBIE_ARMORED_H_L2;
		return ZOMBIE_NORMAL_H_L2;
	}
	else if (currentLevel == LEVEL_03) {
		if (t == ZOMBIE_FAST) return ZOMBIE_FAST_H_L3;
		return ZOMBIE_ARMORED_H_L3;
	}
	else {
		if (t == ZOMBIE_FAST) return ZOMBIE_FAST_H_L4;
		return ZOMBIE_MONSTER_H_L4;
	}
}

int zombieWidth(ZombieType t) {
	return zombieWidthForCurrentLevel(t);
}

int zombieHeight(ZombieType t) {
	return zombieHeightForCurrentLevel(t);
}

int zombieMaxHealthForCurrentLevel(ZombieType t) {
	if (currentLevel == LEVEL_01) {
		return L1_NORMAL_ZOMBIE_HEALTH;
	}
	else if (currentLevel == LEVEL_02) {
		if (t == ZOMBIE_ARMORED) return L2_ARMORED_ZOMBIE_HEALTH;
		return L2_NORMAL_ZOMBIE_HEALTH;
	}
	else if (currentLevel == LEVEL_03) {
		if (t == ZOMBIE_FAST) return L3_FAST_ZOMBIE_HEALTH;
		return L3_ARMORED_ZOMBIE_HEALTH;
	}
	else {
		if (t == ZOMBIE_FAST) return L4_FAST_ZOMBIE_HEALTH;
		return L4_MONSTER_ZOMBIE_HEALTH;
	}
}

ZombieType rollZombieType() {
	if (currentLevel == LEVEL_01) {
		return ZOMBIE_NORMAL;
	}
	else if (currentLevel == LEVEL_02) {
		return (rand() % 100 < 40) ? ZOMBIE_ARMORED : ZOMBIE_NORMAL;
	}
	else if (currentLevel == LEVEL_03) {
		return (rand() % 100 < 50) ? ZOMBIE_FAST : ZOMBIE_ARMORED;
	}
	else {
		return (rand() % 100 < 45) ? ZOMBIE_FAST : ZOMBIE_MONSTER;
	}
}

int getZombieFrameCount(ZombieType type) {
	if (type == ZOMBIE_MONSTER) {
		return 7;
	}
	return 4;
}

int getLevel04Background() {
	return bgL4Img;
}

int getLevel04CharacterImage(bool moving) {
	if (jumpActive && l4RobotJumpImg != 0) return l4RobotJumpImg;
	if (!moving) {
		if (l4RobotIdleImg != 0) return l4RobotIdleImg;
		return l4RobotWalkImg[0];
	}
	int idx = (l4RobotAnimTick / 6) % 4;
	if (l4RobotWalkImg[idx] != 0) return l4RobotWalkImg[idx];
	return l4RobotIdleImg;
}

int getZombieImage(ZombieType type, int frame) {
	if (type == ZOMBIE_NORMAL) {
		return normalZombieImg[frame % 4];
	}
	else if (type == ZOMBIE_ARMORED) {
		return armoredZombieImg[frame % 4];
	}
	else if (type == ZOMBIE_FAST) {
		return fastZombieImg[frame % 4];
	}
	else {
		return monsterZombieImg[frame % 7];
	}
}

void setGameOver() {
	if (gameOver) return;
	gameOver = true;
	rightHeld = leftHeld = false;
	playGameOverSound();
}

void setLevelComplete() {
	if (levelComplete) return;
	levelComplete = true;
	rightHeld = leftHeld = false;
	jumpActive = false;
	jumpY = 0.0;
	jumpVx = 0.0;
	jumpVy = 0.0;
	l4JumpBaseY = 0.0;
	playLevelCompleteSound();
}

void checkFuelEmptyGameOver() {
	if (gameOver) return;
	if (fuelLevel <= 0.0) {
		fuelLevel = 0.0;
		setGameOver();
	}
}

void resetBoostForLevel() {
	boostBar = 0.0;
	jumpActive = false;
	jumpY = 0.0;
	jumpVx = 0.0;
	jumpVy = 0.0;
	l4JumpBaseY = 0.0;
}

void addBoostFromCoin() {
	if (!boostAvailableForThisLevel()) return;
	boostBar += BOOST_PER_COIN;
	if (boostBar > 100.0) boostBar = 100.0;
}

void applyBoostJump() {
	if (!boostAvailableForThisLevel()) return;
	if (levelComplete || gameOver) return;
	if (boostBar < 100.0) return;
	if (jumpActive) return;

	boostBar = BOOST_AFTER_USE;

	if (currentLevel == LEVEL_04) {
		l4JumpBaseY = robotBaseDrawY();
	}

	double rad = (JUMP_ANGLE_DEG * 3.14159265358979323846) / 180.0;
	jumpVx = JUMP_SPEED * cos(rad);
	jumpVy = JUMP_SPEED * sin(rad);
	jumpActive = true;
}

void updateJumpPhysics() {
	if (!jumpActive) return;
	jumpY += jumpVy;
	jumpVy -= GRAVITY_PER_TICK;
	if (jumpY <= 0.0) {
		jumpY = 0.0;
		jumpActive = false;
		jumpVx = 0.0;
		jumpVy = 0.0;
	}
}

void spawnFuelDropAt(double worldX) {
	Fuel f;
	f.x = worldX;
	f.yOffset = 35;
	f.taken = false;
	fuels.push_back(f);
}

void initCoins() {
	coins.clear();
	collectedCoins = 0;
	levelComplete = false;
	gameOver = false;
	levelCompleteSoundPlayed = false;
	gameOverSoundPlayed = false;
	resetBoostForLevel();

	double startX = 220;
	double spacing = 170;
	int total = currentTotalCoinsSpawn();

	for (int i = 0; i < total; i++) {
		Coin c;
		c.x = startX + i * spacing;
		if (currentLevel == LEVEL_03) c.yOffset = (i % 2 == 0) ? 45 : 85;
		else if (currentLevel == LEVEL_04) {
			if (i % 5 == 0) c.yOffset = 115;
			else if (i % 2 == 0) c.yOffset = 70;
			else c.yOffset = 40;
		}
		else c.yOffset = (i % 6 == 0) ? 85 : 45;
		c.taken = false;
		coins.push_back(c);
	}
}

void checkCoinCollect() {
	if (levelComplete || gameOver) return;
	int target = currentTargetCoins();
	if (collectedCoins >= target) return;

	double playerFrontX = isRobotLevel() ? (playerWorldX + 70) : (playerWorldX + 90);
	double playerCenterY = playerDrawY() + (isRobotLevel() ? ROBOT_H * 0.55 : getCurrentCarHeight() * 0.5);
	double xTol = jumpActive ? 85.0 : 55.0;
	double yTol = jumpActive ? 120.0 : 60.0;

	if (isRobotLevel()) {
		xTol = jumpActive ? 95.0 : 65.0;
		yTol = jumpActive ? 130.0 : 85.0;
	}

	for (size_t i = 0; i < coins.size(); i++) {
		if (coins[i].taken) continue;
		double cy = terrainY(coins[i].x) + coins[i].yOffset;
		double coinCenterY = cy + COIN_H * 0.5;
		if (fabs(coins[i].x - playerFrontX) < xTol && fabs(coinCenterY - playerCenterY) < yTol) {
			coins[i].taken = true;
			collectedCoins++;
			addBoostFromCoin();
			playCoinCollectSound();

			if (collectedCoins >= target) {
				setLevelComplete();
			}
			return;
		}
	}
}

void initFuel() {
	fuels.clear();

	double startX = currentFuelStartX();
	double gap = currentFuelGap();
	int count = currentFuelCount();

	for (int i = 0; i < count; i++) {
		Fuel f;
		f.x = startX + i * gap;

		if (currentLevel == LEVEL_03) f.yOffset = (i % 2 == 0) ? 25 : 85;
		else if (currentLevel == LEVEL_04) f.yOffset = (i % 3 == 0) ? 95 : 35;
		else f.yOffset = (i % 2 == 0) ? 35 : 25;

		f.taken = false;
		fuels.push_back(f);
	}
}

void checkFuelCollect() {
	if (levelComplete || gameOver) return;
	double playerFrontX = isRobotLevel() ? (playerWorldX + 70) : (playerWorldX + 90);
	double playerCenterY = playerDrawY() + (isRobotLevel() ? ROBOT_H * 0.55 : getCurrentCarHeight() * 0.5);
	double xTol = isRobotLevel() ? 80.0 : 70.0;
	double yTol = isRobotLevel() ? 90.0 : 75.0;

	for (size_t i = 0; i < fuels.size(); i++) {
		if (fuels[i].taken) continue;
		double fy = terrainY(fuels[i].x) + fuels[i].yOffset;
		double fcy = fy + FUEL_H * 0.5;
		if (fabs(fuels[i].x - playerFrontX) < xTol && fabs(fcy - playerCenterY) < yTol) {
			fuels[i].taken = true;
			fuelLevel += currentFuelAddPerPick();
			if (fuelLevel > MAX_FUEL) fuelLevel = MAX_FUEL;
			playFuelCollectSound();
			return;
		}
	}
}

int getCurrentBulletWidth() {
	if (currentLevel == LEVEL_02) return BULLET_W_L2;
	if (currentLevel == LEVEL_03) return BULLET_W_L3;
	if (currentLevel == LEVEL_04) return BULLET_W_L4;
	return 20;
}

int getCurrentBulletHeight() {
	if (currentLevel == LEVEL_02) return BULLET_H_L2;
	if (currentLevel == LEVEL_03) return BULLET_H_L3;
	if (currentLevel == LEVEL_04) return BULLET_H_L4;
	return 20;
}

void shoot() {
	if (currentLevel != LEVEL_02 && currentLevel != LEVEL_03 && currentLevel != LEVEL_04) return;
	if (levelComplete || gameOver || shootCooldown > 0) return;

	double cost = currentShootCost();
	if (currentLevel == LEVEL_03) {
		cost *= 2.0;
	}

	if (fuelLevel < cost) return;
	fuelLevel -= cost;
	if (fuelLevel < 0) fuelLevel = 0;
	checkFuelEmptyGameOver();
	if (gameOver) return;

	int carW = getCurrentCarWidth();
	int carH = getCurrentCarHeight();

	if (currentLevel == LEVEL_03) {
		Bullet b1, b2;

		b1.x = playerWorldX + playerScreenX + carW - 10;
		b1.y = playerDrawY() + carH * 0.65;
		b1.active = true;

		b2.x = playerWorldX + playerScreenX + carW - 10;
		b2.y = playerDrawY() + carH * 0.45;
		b2.active = true;

		bullets.push_back(b1);
		bullets.push_back(b2);
	}
	else if (currentLevel == LEVEL_04) {
		Bullet b1, b2;

		b1.x = playerWorldX + playerScreenX + ROBOT_W - 5;
		b1.y = playerDrawY() + ROBOT_H * 0.68;
		b1.active = true;

		b2.x = playerWorldX + playerScreenX + ROBOT_W - 5;
		b2.y = playerDrawY() + ROBOT_H * 0.48;
		b2.active = true;

		bullets.push_back(b1);
		bullets.push_back(b2);
	}
	else {
		Bullet b;
		b.x = playerWorldX + playerScreenX + carW - 10;
		b.y = playerDrawY() + carH * 0.55;
		b.active = true;
		bullets.push_back(b);
	}

	shootCooldown = SHOOT_COOLDOWN_TICKS;
}

bool bulletHitsTerrain(const Bullet& b) {
	if (currentLevel == LEVEL_04) return false;

	double bulletBottomY = b.y;
	double bulletFrontX = b.x + getCurrentBulletWidth() * 0.5;
	double groundY = terrainY(bulletFrontX);

	return bulletBottomY <= groundY + 2.0;
}

void updateBullets() {
	if (currentLevel != LEVEL_02 && currentLevel != LEVEL_03 && currentLevel != LEVEL_04) return;

	double bulletSpeed = getCurrentBulletSpeed();

	for (size_t i = 0; i < bullets.size(); i++) {
		if (!bullets[i].active) continue;

		bullets[i].x += bulletSpeed;

		if (bulletHitsTerrain(bullets[i])) {
			bullets[i].active = false;
			continue;
		}

		if (bullets[i].x - playerWorldX > SCREEN_WIDTH + 200) bullets[i].active = false;
	}

	for (int i = (int)bullets.size() - 1; i >= 0; --i) {
		if (!bullets[i].active) bullets.erase(bullets.begin() + i);
	}
}

void clearZombies() {
	zombies.clear();
	zombieSpawnCounter = 0;
}

void spawnZombieAhead() {
	double rightEdge = playerWorldX + SCREEN_WIDTH;
	int gap = randInt(ZOMBIE_SPAWN_MIN, ZOMBIE_SPAWN_MAX);
	Zombie z;
	z.x = rightEdge + gap;
	z.type = rollZombieType();
	z.frame = randInt(0, getZombieFrameCount(z.type) - 1);
	z.alive = true;
	z.maxHealth = zombieMaxHealthForCurrentLevel(z.type);
	z.health = z.maxHealth;
	zombies.push_back(z);
}

bool bulletHitsZombie(const Bullet& b, const Zombie& z) {
	int bx = (int)b.x, by = (int)b.y;
	int zx = (int)z.x, zy = (int)terrainY(z.x);
	int zw = zombieWidth(z.type), zh = zombieHeight(z.type);
	int bw = getCurrentBulletWidth();
	int bh = getCurrentBulletHeight();
	return aabbOverlap(bx, by, bw, bh, zx, zy, zw, zh);
}

void handleZombieDeath(const Zombie& z) {
	if (currentLevel == LEVEL_04 && z.type == ZOMBIE_FAST) {
		spawnFuelDropAt(z.x);
	}
	playZombieHitSound();
}

void damageZombie(Zombie& z, int dmg) {
	if (!z.alive) return;
	z.health -= dmg;
	playZombieHitSound();
	if (z.health <= 0) {
		z.health = 0;
		handleZombieDeath(z);
		z.alive = false;
	}
}

void updateZombies() {
	if (appState != STATE_PLAY || levelComplete || gameOver) return;

	zombieSpawnCounter++;

	int spawnDelay = getCurrentZombieSpawnDelay();
	int spawnChance = getCurrentZombieSpawnChance();
	int extraSpawnChance = getCurrentZombieExtraSpawnChance();
	int maxZombies = getCurrentMaxZombiesOnScreen();

	if (zombieSpawnCounter >= spawnDelay) {
		zombieSpawnCounter = 0;

		if ((int)zombies.size() < maxZombies && rand() % 100 < spawnChance) {
			spawnZombieAhead();

			if ((int)zombies.size() < maxZombies && extraSpawnChance > 0 && rand() % 100 < extraSpawnChance) {
				spawnZombieAhead();
			}
		}
	}

	bool moving = rightHeld || leftHeld || jumpActive;
	int py = playerDrawY();
	int px = (int)(playerWorldX + playerScreenX);
	int carW = getCurrentCarWidth();
	int carH = getCurrentCarHeight();
	int hitX, hitY, hitW, hitH;

	if (currentLevel == LEVEL_04) {
		hitX = px + 20;
		hitY = py + 10;
		hitW = 70;
		hitH = 110;
	}
	else {
		hitX = px + 20;
		hitY = py + 10;
		hitW = carW - 40;
		hitH = carH - 20;
	}

	for (size_t i = 0; i < zombies.size(); i++) {
		if (!zombies[i].alive) continue;
		zombies[i].x -= zombieSpeed(zombies[i].type);
		zombies[i].frame = (zombies[i].frame + 1) % getZombieFrameCount(zombies[i].type);

		if (currentLevel == LEVEL_02 || currentLevel == LEVEL_03 || currentLevel == LEVEL_04) {
			for (size_t j = 0; j < bullets.size(); j++) {
				if (bullets[j].active && bulletHitsZombie(bullets[j], zombies[i])) {
					damageZombie(zombies[i], 1);
					bullets[j].active = false;
					break;
				}
			}
		}

		if (!zombies[i].alive) continue;

		int zy = (int)terrainY(zombies[i].x);
		int zx = (int)zombies[i].x;
		int zw = zombieWidth(zombies[i].type);
		int zh = zombieHeight(zombies[i].type);
		int zHitX = zx + zw / 10;
		int zHitY = zy + zh / 8;
		int zHitW = zw - zw / 5;
		int zHitH = zh - zh / 6;

		if (aabbOverlap(hitX, hitY, hitW, hitH, zHitX, zHitY, zHitW, zHitH)) {
			if (currentLevel == LEVEL_04 || currentLevel == LEVEL_03 ||
				(currentLevel == LEVEL_02 && zombies[i].type == ZOMBIE_ARMORED)) {
				setGameOver();
				return;
			}

			if (moving) {
				handleZombieDeath(zombies[i]);
				zombies[i].alive = false;
			}
			else {
				setGameOver();
				return;
			}
		}
	}

	for (int i = (int)zombies.size() - 1; i >= 0; --i) {
		if (!zombies[i].alive || zombies[i].x - playerWorldX < -300)
			zombies.erase(zombies.begin() + i);
	}
}

void commonLevelStart(double carriedFuel) {
	playerWorldX = 0;
	bgX = 0;
	carL1AnimTick = 0;
	carL2AnimTick = 0;
	carL3AnimTick = 0;
	l4RobotAnimTick = 0;
	rightHeld = leftHeld = false;
	bullets.clear();
	shootCooldown = 0;
	levelComplete = false;
	gameOver = false;
	levelCompleteSoundPlayed = false;
	gameOverSoundPlayed = false;
	initCoins();
	initFuel();
	clearZombies();
	fuelLevel = carriedFuel;
	if (fuelLevel > MAX_FUEL) fuelLevel = MAX_FUEL;
	if (fuelLevel < 0) fuelLevel = 0;
}

void startLevel01() { currentLevel = LEVEL_01; commonLevelStart(MAX_FUEL); }
void startLevel02(double carriedFuel) { currentLevel = LEVEL_02; commonLevelStart(carriedFuel); resetBoostForLevel(); }
void startLevel03(double carriedFuel) { currentLevel = LEVEL_03; commonLevelStart(carriedFuel); resetBoostForLevel(); }
void startLevel04(double carriedFuel) { currentLevel = LEVEL_04; commonLevelStart(carriedFuel); resetBoostForLevel(); }

void updateGame() {
	updateGameplayBgm();

	if (appState == STATE_L1_TO_L2_INTRO) {
		l1ToL2ElapsedMs += 16;
		if (l1ToL2ElapsedMs >= 12000) {
			l1ToL2ElapsedMs = 0;
			startLevel02(fuelLevel);
			appState = STATE_PLAY;
		}
		return;
	}

	if (appState == STATE_L2_TO_L3_INTRO) {
		l2ToL3ElapsedMs += 16;
		if (l2ToL3ElapsedMs >= 12000) {
			l2ToL3ElapsedMs = 0;
			startLevel03(fuelLevel);
			appState = STATE_PLAY;
		}
		return;
	}

	if (appState == STATE_L3_TO_L4_INTRO) {
		l3ToL4ElapsedMs += 16;
		if (l3ToL4ElapsedMs >= 12000) {
			l3ToL4ElapsedMs = 0;
			startLevel04(fuelLevel);
			appState = STATE_PLAY;
		}
		return;
	}

	if (appState == STATE_L4_COMPLETE_SCREEN) {
		l4CompleteScreenElapsedMs += 16;
		if (l4CompleteScreenElapsedMs >= 3000) {
			l4CompleteScreenElapsedMs = 0;
			appState = STATE_L4_END_SCREEN;
			l4EndElapsedMs = 0;
		}
		return;
	}

	if (appState == STATE_L4_END_SCREEN) {
		l4EndElapsedMs += 16;
		if (l4EndElapsedMs >= 5000) {
			l4EndElapsedMs = 0;
			appState = STATE_MENU;
		}
		return;
	}

	if (appState == STATE_BOOT_INTRO) {
		bootElapsedMs += 16;
		if (bootElapsedMs >= 12000) {
			bootElapsedMs = 0;
			appState = STATE_MENU;
		}
		return;
	}

	if (appState == STATE_START_INTRO) {
		startElapsedMs += 16;
		if (startElapsedMs >= 12000) {
			startElapsedMs = 0;
			startLevel01();
			appState = STATE_PLAY;
		}
		return;
	}

	if (appState == STATE_PLAY) fuelBlink++;
	if (appState != STATE_PLAY) return;

	if (levelComplete && currentLevel == LEVEL_04) {
		levelComplete = false;
		l4CompleteScreenElapsedMs = 0;
		appState = STATE_L4_COMPLETE_SCREEN;
		return;
	}

	if (levelComplete || gameOver) return;

#ifdef _WIN32
	rightHeld = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
	leftHeld = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
#else
	rightHeld = leftHeld = false;
#endif

	if (jumpActive) leftHeld = false;
	if (shootCooldown > 0) shootCooldown--;

	updateJumpPhysics();

	double deltaX = 0.0;
	if (rightHeld && !leftHeld) deltaX += SCROLL_SPEED;
	else if (leftHeld && !rightHeld) deltaX -= SCROLL_SPEED;
	if (jumpActive) deltaX += jumpVx;

	if (deltaX != 0.0) {
		playerWorldX += deltaX;
		if (playerWorldX < 0) playerWorldX = 0;
		bgX -= (int)(deltaX / 2.0);

		if (currentLevel == LEVEL_01) {
			carL1AnimTick++;
		}
		else if (currentLevel == LEVEL_02) {
			carL2AnimTick++;
		}
		else if (currentLevel == LEVEL_03) {
			carL3AnimTick++;
		}
		else if (currentLevel == LEVEL_04) {
			l4RobotAnimTick++;
		}

		checkCoinCollect();
		checkFuelCollect();

		fuelLevel -= currentFuelDecPerTick();
		if (fuelLevel < 0) fuelLevel = 0;
	}

	checkFuelEmptyGameOver();
	if (bgX <= -SCREEN_WIDTH) bgX = 0;
	if (bgX > 0) bgX = 0;
	updateBullets();
	updateZombies();
}