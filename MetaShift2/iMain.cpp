#include <cstdio>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "iGraphics.h"
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif




//CONFIG

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define SCROLL_SPEED 12




//APP STATES

enum AppState { STATE_MENU, STATE_PLAY, STATE_OPTIONS, STATE_ABOUT };
AppState appState = STATE_MENU;



//RECT / HIT TEST

struct BtnRect { int x, y, w, h; };

bool pointInRect(int mx, int my, const BtnRect& r)
{
    return (mx >= r.x && mx <= r.x + r.w &&
            my >= r.y && my <= r.y + r.h);
}




//ASSETS + BUTTONS (MENU/OPTIONS/ABOUT)

int menuBgImg;
int optSoundBoxImg, optControlsBoxImg;
int musicOnImg, musicOffImg, sfxOnImg, sfxOffImg;   // These are just images for UI, not sound
int aboutPanelImg;

BtnRect btnStart, btnOptions, btnAbout, btnExit;
BtnRect btnMusicToggle, btnSfxToggle;
BtnRect btnAboutExit;

bool musicOn = true;                               // UI toggle only
bool sfxOn = true;                                




//LEVEL 01 SETTINGS

const int CAR_W = 140;  //Car Size
const int CAR_H = 100;  

const int COIN_W = 40;   //Coin Size
const int COIN_H = 40;

const int TARGET_COINS_L1 = 100;   //Target Coin

int bg3;
int bgX = 0;

int carImg[3];
int carFrame = 0;
int coinImg;





//FUEL SYSTEM

const int FUEL_W = 60;       //Fuel Tank Size
const int FUEL_H = 40;

int fuelImg;

struct Fuel
{
    double x;
    double yOffset;
    bool taken;
};
std::vector<Fuel> fuels;        //Fuel vector

const double MAX_FUEL = 100.0;
double fuelLevel = MAX_FUEL;

const double FUEL_DEC_PER_TICK = 0.18;   //Fuel decreases while moving
const double FUEL_ADD_PER_PICK = 22.0;

const double FUEL_HALF = MAX_FUEL / 2.0;
const double FUEL_REFILL_PER_TICK = 0.12;





//HUD (ONE LINE)              // Fuel bar

const int HUD_TOP_Y = SCREEN_HEIGHT - 30;

// Left side fuel section
const int HUD_FUEL_LABEL_X = 20;
const int HUD_FUEL_BAR_X = 70;
const int HUD_FUEL_BAR_Y = HUD_TOP_Y - 12;

const int FUEL_BAR_W = 180;
const int FUEL_BAR_H = 14;

const int HUD_FUEL_NUM_X = HUD_FUEL_BAR_X + FUEL_BAR_W + 12;

// Right side level/coins
const int HUD_TEXT_X = 520;







//GAME GLOBALS               //Real world position of car

double playerWorldX = 0;
int playerScreenX = 120;

bool rightHeld = false;
bool leftHeld = false;

bool levelComplete = false;
bool gameOver = false;
int collectedCoins = 0;

struct Coin { double x; double yOffset; bool taken; };
std::vector<Coin> coins;





//ZOMBIE SETTINGS

const int ZOMBIE_W = 50;    //Zombie size
const int ZOMBIE_H = 50;   

const double ZOMBIE_SPEED = 4.0;    //Zombie speed
const int ZOMBIE_SPAWN_MIN = 170;
const int ZOMBIE_SPAWN_MAX = 450;

int zombieImg[4];

struct Zombie
{
    double x;
    int frame;
    bool alive;
};

std::vector<Zombie> zombies;
int zombieSpawnCounter = 0;





//TERRAIN            //Hills by sine waves.

double terrainY(double worldX)
{
    double base = 135.0;
    double y = base
        + 20.0 * sin(worldX * 0.010)
        + 10.0 * sin(worldX * 0.022);

    if (y < 90)  y = 90;
    if (y > 190) y = 190;
    return y;
}




//CAR GROUND CONTACT FIX

const int REAR_WHEEL_X = 30;
const int FRONT_WHEEL_X = CAR_W - 30;
const int WHEEL_CONTACT_FROM_BOTTOM = 12;

// Extra drop to move the car slightly lower on the road
const int CAR_EXTRA_DROP = 10; // Increase to move the car more down

int carDrawY()
{
    double rearWheelWorldX = playerWorldX + playerScreenX + REAR_WHEEL_X;
    double frontWheelWorldX = playerWorldX + playerScreenX + FRONT_WHEEL_X;

    int groundRear = (int)terrainY(rearWheelWorldX);
    int groundFront = (int)terrainY(frontWheelWorldX);

    int groundY = (groundRear > groundFront) ? groundRear : groundFront;

    // Base alignment
    int drawY = groundY - WHEEL_CONTACT_FROM_BOTTOM;

    // Move car a bit lower
    drawY -= CAR_EXTRA_DROP;

    return drawY;
}





//COINS

void initCoins()
{
    coins.clear();
    collectedCoins = 0;
    levelComplete = false;
    gameOver = false;

    double startX = 220;
    double spacing = 170;

    int totalCoins = TARGET_COINS_L1 + 120;

    for (int i = 0; i < totalCoins; i++)
    {
        Coin c;
        c.x = startX + i * spacing;      
		c.yOffset = (i % 6 == 0) ? 85 : 45;         
        c.taken = false;
        coins.push_back(c);
    }
}

bool anyCoinVisible()
{
    for (auto& c : coins)
    {
        if (c.taken) continue;
        int sx = (int)(c.x - playerWorldX);
		if (sx >= -50 && sx <= SCREEN_WIDTH + 50) {
			return true;
		}
			
    }
    return false;
}

void checkCoinCollect()
{
	if (levelComplete || gameOver){
		return;
       }
	if (collectedCoins >= TARGET_COINS_L1) {
		return;
	}
    double carFrontX = playerWorldX + 90;
    double carCenterY = carDrawY() + (CAR_H * 0.5);

    for (auto& c : coins)
    {
        if (c.taken) continue;

        double coinY = terrainY(c.x) + c.yOffset;
        double coinCenterY = coinY + (COIN_H * 0.5);

        if (fabs(c.x - carFrontX) < 55 && fabs(coinCenterY - carCenterY) < 60)
        {
            c.taken = true;
            collectedCoins++;

            if (collectedCoins >= TARGET_COINS_L1)
            {
                levelComplete = true;
                rightHeld = leftHeld = false;
            }
            return;
        }
    }
}





//FUEL

void initFuel()
{
    fuels.clear();
    fuelLevel = MAX_FUEL;

    const double FUEL_START_X = 900;
    const double FUEL_SPACING = 1600;
    const int TOTAL_FUELS = 8;

    for (int i = 0; i < TOTAL_FUELS; i++)
    {
        Fuel f;
        f.x = FUEL_START_X + i * FUEL_SPACING;
        f.yOffset = (i % 2 == 0) ? 35 : 25;
        f.taken = false;
        fuels.push_back(f);
    }
}

void checkFuelCollect()
{
    if (levelComplete || gameOver) return;

    double carFrontX = playerWorldX + 90;
    double carCenterY = carDrawY() + (CAR_H * 0.5);

    for (auto& f : fuels)
    {
        if (f.taken) continue;

        double fuelY = terrainY(f.x) + f.yOffset;
        double fuelCenterY = fuelY + (FUEL_H * 0.5);

        if (fabs(f.x - carFrontX) < 70 && fabs(fuelCenterY - carCenterY) < 75)
        {
            f.taken = true;

            fuelLevel += FUEL_ADD_PER_PICK;
            if (fuelLevel > MAX_FUEL) fuelLevel = MAX_FUEL;
            return;
        }
    }
}






//ZOMBIE HELPERS

int randInt(int a, int b)
{
    return a + (rand() % (b - a + 1));
}

void clearZombies()
{
    zombies.clear();
    zombieSpawnCounter = 0;
}

void spawnZombieAhead()
{
    double cameraRightWorldX = playerWorldX + SCREEN_WIDTH;
    int gap = randInt(ZOMBIE_SPAWN_MIN, ZOMBIE_SPAWN_MAX);

    Zombie z;
    z.x = cameraRightWorldX + gap;
    z.frame = randInt(0, 3);
    z.alive = true;
    zombies.push_back(z);
}

bool aabbOverlap(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh)    // Zombie collision
{
    return (ax < bx + bw && ax + aw > bx &&
            ay < by + bh && ay + ah > by);
}

void updateZombies()
{
    if (appState != STATE_PLAY) return;
    if (levelComplete || gameOver) return;

    zombieSpawnCounter++;
    if (zombieSpawnCounter >= 60)
    {
        zombieSpawnCounter = 0;
        if ((rand() % 100) < 90)
            spawnZombieAhead();
    }

    bool carMoving = (rightHeld || leftHeld);

    int carX = playerScreenX;
    int carY = carDrawY();
    int carWorldX = (int)(playerWorldX + carX);

    int carHitX = carWorldX + 20;
    int carHitY = carY + 10;
    int carHitW = CAR_W - 40;
    int carHitH = CAR_H - 20;

    for (auto& z : zombies)
    {
        if (!z.alive) continue;


		// Zombies move left meaning right to left
        z.x -= ZOMBIE_SPEED;
        z.frame = (z.frame + 1) % 4;

        int zy = (int)terrainY(z.x);
        int zx = (int)z.x;

        int zHitX = zx + 15;
        int zHitY = zy + 10;
        int zHitW = ZOMBIE_W - 30;
        int zHitH = ZOMBIE_H - 20;

        if (aabbOverlap(carHitX, carHitY, carHitW, carHitH, zHitX, zHitY, zHitW, zHitH))
        {
            if (carMoving)
            {
                z.alive = false;				// Zombie is killed if the car is moving
            }
            else
            {
                gameOver = true;			    // Game over if the car is not moving
                rightHeld = leftHeld = false;
                return;
            }
        }
    }


  // Remove zombies that are dead 
    for (int i = (int)zombies.size() - 1; i >= 0; --i)
    {
        double sx = zombies[i].x - playerWorldX;
        if (!zombies[i].alive || sx < -300)
            zombies.erase(zombies.begin() + i);
    }
}

void drawZombies()
{
    for (auto& z : zombies)
    {
        if (!z.alive) continue;

        int sx = (int)(z.x - playerWorldX);
        if (sx < -200 || sx > SCREEN_WIDTH + 200) continue;

        int zy = (int)terrainY(z.x);
        iShowImage(sx, zy, ZOMBIE_W, ZOMBIE_H, zombieImg[z.frame]);
    }
}







//LEVEL 01 - START/RESET

void startLevel01()
{
    playerWorldX = 0;
    bgX = 0;
    carFrame = 0;
    rightHeld = leftHeld = false;

    initCoins();
    initFuel();
    clearZombies();
}






//LEVEL 01 - UPDATE          //Main engine that update everything

void updateLevel01()
{
    if (appState != STATE_PLAY) return;
    if (levelComplete || gameOver) return;

#ifdef _WIN32
    rightHeld = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
    leftHeld  = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
#else
    rightHeld = leftHeld = false;
#endif

    bool carMoving = false;

    if (rightHeld && !leftHeld)
    {
        playerWorldX += SCROLL_SPEED;
        bgX -= (SCROLL_SPEED / 2);
        carFrame = (carFrame + 1) % 3;
        carMoving = true;

        checkCoinCollect();
        checkFuelCollect();
    }
    else if (leftHeld && !rightHeld)
    {
        playerWorldX -= SCROLL_SPEED;
        if (playerWorldX < 0) playerWorldX = 0;

        bgX += (SCROLL_SPEED / 2);
        carFrame = (carFrame + 1) % 3;
        carMoving = true;

        checkCoinCollect();
        checkFuelCollect();
    }

    if (carMoving)
    {
        fuelLevel -= FUEL_DEC_PER_TICK;
        if (fuelLevel < 0) fuelLevel = 0;
    }

    // Auto-refill a bit when fuel is low (your existing design)
    if (fuelLevel <= FUEL_HALF)
    {
        fuelLevel += FUEL_REFILL_PER_TICK;
        if (fuelLevel > MAX_FUEL) fuelLevel = MAX_FUEL;
    }

    if (fuelLevel <= 0.0)
    {
        gameOver = true;
        rightHeld = leftHeld = false;
    }

    // Background wrapping
    if (bgX <= -SCREEN_WIDTH) bgX = 0;
    if (bgX > 0) bgX = 0;

    updateZombies();

    // If the player did not reach target coins and there are no visible coins, end the game
    if (!levelComplete && collectedCoins < TARGET_COINS_L1 && !anyCoinVisible())
    {
        gameOver = true;
        rightHeld = leftHeld = false;
    }
}






//DRAW HELPERS         //It implements every image

void drawRoad()        //Draws terrain line
{
    int prevX = 0;
    int prevY = (int)terrainY(playerWorldX);

    for (int sx = 10; sx <= SCREEN_WIDTH; sx += 10)
    {
        int sy = (int)terrainY(playerWorldX + sx);

        iSetColor(20, 20, 20);
        iLine(prevX, prevY, sx, sy);
        iLine(prevX, prevY + 1, sx, sy + 1);
        iLine(prevX, prevY - 1, sx, sy - 1);

        prevX = sx;
        prevY = sy;
    }
}

void drawUnderground()
{
    for (int sx = 0; sx < SCREEN_WIDTH; sx += 10)
    {
        int groundY = (int)terrainY(playerWorldX + sx);
        iSetColor(130, 80, 35);
        iFilledRectangle(sx, 0, 10, groundY);
    }
}

void drawCoins()
{
    for (auto& c : coins)
    {
        if (c.taken) continue;

        int sx = (int)(c.x - playerWorldX);
        if (sx < -60 || sx > SCREEN_WIDTH + 60) continue;

        int coinY = (int)(terrainY(c.x) + c.yOffset);
        iShowImage(sx, coinY, COIN_W, COIN_H, coinImg);
    }
}

void drawFuel()
{
    for (auto& f : fuels)
    {
        if (f.taken) continue;

        int sx = (int)(f.x - playerWorldX);
        if (sx < -80 || sx > SCREEN_WIDTH + 80) continue;

        int fy = (int)(terrainY(f.x) + f.yOffset);
        iShowImage(sx, fy, FUEL_W, FUEL_H, fuelImg);
    }
}

void drawHUD()
{
    // Fuel label
    iSetColor(0, 0, 0);
    iText(HUD_FUEL_LABEL_X, HUD_TOP_Y, "FUEL", GLUT_BITMAP_HELVETICA_18);

    // Fuel bar border
    iSetColor(0, 0, 0);
    iRectangle(HUD_FUEL_BAR_X, HUD_FUEL_BAR_Y, FUEL_BAR_W, FUEL_BAR_H);

    // Fuel fill
    double ratio = fuelLevel / MAX_FUEL;
    if (ratio < 0) ratio = 0;
    if (ratio > 1) ratio = 1;

    int fillW = (int)(FUEL_BAR_W * ratio);

    iSetColor(20, 160, 40);
    if (fillW > 2)
        iFilledRectangle(HUD_FUEL_BAR_X + 1, HUD_FUEL_BAR_Y + 1, fillW - 2, FUEL_BAR_H - 2);

    // Fuel numbers
    char ft[64];
    sprintf_s(ft, sizeof(ft), "%.0f / %.0f", fuelLevel, MAX_FUEL);
    iSetColor(0, 0, 0);
    iText(HUD_FUEL_NUM_X, HUD_TOP_Y - 2, ft, GLUT_BITMAP_HELVETICA_12);

    // Level + Coins (same line, right side)
    char hud[160];
    sprintf_s(hud, sizeof(hud), "Level 01 | Coins: %d / %d", collectedCoins, TARGET_COINS_L1);
    iSetColor(0, 0, 0);
    iText(HUD_TEXT_X, HUD_TOP_Y, hud, GLUT_BITMAP_HELVETICA_18);

    // Messages
    if (levelComplete)
    {
        iSetColor(255, 0, 0);
        iText(170, 420, "LEVEL 01 COMPLETE!", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(185, 395, "Press ESC to go Menu   |   Press R to Restart", GLUT_BITMAP_HELVETICA_18);
    }

    if (gameOver)
    {
        iSetColor(255, 0, 0);
        iText(305, 430, "GAME OVER!", GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0, 0, 0);
        iText(185, 375, "Press ESC to go Menu   |   Press R to Restart", GLUT_BITMAP_HELVETICA_18);
    }
}

void drawLevel01()
{
    // Draw scrolling background
    iShowImage(bgX, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg3);
    iShowImage(bgX + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg3);

    drawUnderground();
    drawRoad();

    // Draw gameplay objects
    drawZombies();
    drawCoins();
    drawFuel();

    // Draw player car
    iShowImage(playerScreenX, carDrawY(), CAR_W, CAR_H, carImg[carFrame]);

    // Draw UI
    drawHUD();
}







//SCREENS DRAW

void drawMenu()  { iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, menuBgImg); }
void drawAbout() { iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, aboutPanelImg); }

void drawOptions()
{
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, menuBgImg);
    iShowImage(80, 410, 300, 260, optSoundBoxImg);
    iShowImage(420, 410, 300, 260, optControlsBoxImg);

    // These toggles are only visual in this version (no sound system)
    iShowImage(btnMusicToggle.x, btnMusicToggle.y, btnMusicToggle.w, btnMusicToggle.h,
               musicOn ? musicOnImg : musicOffImg);

    iShowImage(btnSfxToggle.x, btnSfxToggle.y, btnSfxToggle.w, btnSfxToggle.h,
               sfxOn ? sfxOnImg : sfxOffImg);

    iSetColor(255, 255, 255);
    iText(250, 80, "Press B or ESC to go back", GLUT_BITMAP_HELVETICA_18);
}






//MAIN DRAW

void iDraw()
{
    iClear();

    if (appState == STATE_MENU)    
		{ drawMenu(); 
			return; 
	  }
    if (appState == STATE_OPTIONS) 
		{ drawOptions(); 
			return; 
	  }
    if (appState == STATE_ABOUT)   
		{ drawAbout(); 
			return; 
	  }
    if (appState == STATE_PLAY)    
		{ drawLevel01(); 
			return; 
	  }
}





//MOUSE

void iMouse(int button, int state, int mx, int my)
{
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

    if (appState == STATE_MENU)
    {
        if (pointInRect(mx, my, btnStart))   { startLevel01(); appState = STATE_PLAY; return; }
        if (pointInRect(mx, my, btnOptions)) { appState = STATE_OPTIONS; return; }
        if (pointInRect(mx, my, btnAbout))   { appState = STATE_ABOUT; return; }
        if (pointInRect(mx, my, btnExit))    { exit(0); return; }
    }
    else if (appState == STATE_OPTIONS)
    {
        // Toggles are kept for UI only (no sound logic here)
        if (pointInRect(mx, my, btnMusicToggle)) { musicOn = !musicOn; return; }
        if (pointInRect(mx, my, btnSfxToggle))   { sfxOn = !sfxOn; return; }
    }
    else if (appState == STATE_ABOUT)
    {
        if (pointInRect(mx, my, btnAboutExit)) { appState = STATE_MENU; return; }
    }
}

void iMouseMove(int mx, int my) {}
void iPassiveMouseMove(int mx, int my) {}





//KEYBOARD

void iKeyboard(unsigned char key)
{
    if (appState == STATE_OPTIONS || appState == STATE_ABOUT)
    {
        if (key == 'b' || key == 'B' || key == 27) appState = STATE_MENU;
        return;
    }

    if (appState == STATE_PLAY)
    {
        if (key == 27)
        {
            appState = STATE_MENU;
            rightHeld = leftHeld = false;
            return;
        }

        if (key == 'r' || key == 'R')
        {
            if (levelComplete || gameOver)
            {
                startLevel01();
                return;
            }
        }
    }
}

void iSpecialKeyboard(unsigned char key) {}






//LOAD ASSETS + BUTTONS

void loadZombieAssets()
{
    zombieImg[0] = iLoadImage("Images//Zombie1.png");
    zombieImg[1] = iLoadImage("Images//Zombie2.png");
    zombieImg[2] = iLoadImage("Images//Zombie3.png");
    zombieImg[3] = iLoadImage("Images//Zombie4.png");
}

void initUI()
{
    menuBgImg = iLoadImage("Images//menu_bg.png");
    aboutPanelImg = iLoadImage("Images//about_panel.png");

    btnStart   = { 270, 345, 260, 75 };
    btnOptions = { 305, 270, 190, 55 };
    btnAbout   = { 305, 205, 190, 55 };
    btnExit    = { 305, 140, 190, 55 };

    optSoundBoxImg    = iLoadImage("Images//opt_sound_box.png");
    optControlsBoxImg = iLoadImage("Images//opt_controls_box.png");

    musicOnImg  = iLoadImage("Images//music_on.png");
    musicOffImg = iLoadImage("Images//music_off.png");
    sfxOnImg    = iLoadImage("Images//sfx_on.png");
    sfxOffImg   = iLoadImage("Images//sfx_off.png");

    btnMusicToggle = { 220, 555, 120, 45 };
    btnSfxToggle   = { 220, 485, 120, 45 };

    btnAboutExit = { 345, 40, 110, 55 };
}





//MAIN

int main()
{
    srand((unsigned)time(0));
    iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "MetaShift");

    initUI();

    bg3 = iLoadImage("Images//bg3.jpg");
    coinImg = iLoadImage("Images//coin.png");
    fuelImg = iLoadImage("Images//fuel.png");

    for (int i = 0; i < 3; i++)
    {
        char path[100];
        sprintf_s(path, sizeof(path), "Images//Car%d.png", i + 1);
        carImg[i] = iLoadImage(path);
    }

    loadZombieAssets();

    iSetTimer(16, updateLevel01);
    iStart();
    return 0;
}
