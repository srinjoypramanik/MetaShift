#include "MetaShiftShared.hpp"

void drawBoostHUD() {
	if (!boostAvailableForThisLevel()) return;

	int boostBarX = HUD_FUEL_BAR_X;
	int boostBarY = HUD_FUEL_BAR_Y - BOOST_BAR_GAP_Y;

	int boostIconX = HUD_FUEL_BAR_X - HUD_BOOST_ICON_W - HUD_ICON_GAP;
	int boostIconY = boostBarY + (FUEL_BAR_H - HUD_BOOST_ICON_H) / 2;

	iShowImage(boostIconX, boostIconY, HUD_BOOST_ICON_W, HUD_BOOST_ICON_H, boostLabelImg);

	iSetColor(0, 0, 0);
	iRectangle(boostBarX, boostBarY, FUEL_BAR_W, FUEL_BAR_H);

	double r = boostBar / 100.0;
	if (r < 0) r = 0;
	if (r > 1) r = 1;

	int fw = (int)(FUEL_BAR_W * r);

	iSetColor(255, 150, 0);
	if (fw > 4) {
		iFilledRectangle(boostBarX + 2, boostBarY + 2, fw - 4, FUEL_BAR_H - 4);
	}

	if (boostBar >= 100.0) {
		iSetColor(0, 120, 0);
		iText(boostBarX + FUEL_BAR_W + 14, boostBarY + 6, (char*)"Press B", GLUT_BITMAP_HELVETICA_18);
	}
}

void drawHUD() {
	int fuelIconX = HUD_FUEL_BAR_X - HUD_FUEL_ICON_W - HUD_ICON_GAP;
	int fuelIconY = HUD_FUEL_BAR_Y + (FUEL_BAR_H - HUD_FUEL_ICON_H) / 2;

	iShowImage(fuelIconX, fuelIconY, HUD_FUEL_ICON_W, HUD_FUEL_ICON_H, fuelLabelImg);

	iSetColor(0, 0, 0);
	iRectangle(HUD_FUEL_BAR_X, HUD_FUEL_BAR_Y, FUEL_BAR_W, FUEL_BAR_H);

	double r = fuelLevel / MAX_FUEL;
	if (r < 0) r = 0;
	if (r > 1) r = 1;

	int fw = (int)(FUEL_BAR_W * r);

	if (!gameOver && fuelLevel <= MAX_FUEL * LOW_FUEL_RATIO) iSetColor(255, 0, 0);
	else iSetColor(20, 160, 40);

	if (fw > 4) {
		iFilledRectangle(HUD_FUEL_BAR_X + 2, HUD_FUEL_BAR_Y + 2, fw - 4, FUEL_BAR_H - 4);
	}

	char buf[200];
	sprintf_s(buf, sizeof(buf), "%.0f / %.0f", fuelLevel, MAX_FUEL);

	iSetColor(0, 0, 0);
	iText(HUD_FUEL_NUM_X, HUD_FUEL_BAR_Y + 6, buf, GLUT_BITMAP_HELVETICA_18);

	if (!gameOver && fuelLevel <= MAX_FUEL * LOW_FUEL_RATIO) {
		if ((fuelBlink / 18) % 2 == 0) {
			iSetColor(255, 0, 0);
			iText(HUD_FUEL_NUM_X + 120, HUD_FUEL_BAR_Y + 6, (char*)"LOW FUEL!", GLUT_BITMAP_HELVETICA_18);
		}
	}

	drawBoostHUD();

	int zombiesOnScreen = 0;
	for (size_t i = 0; i < zombies.size(); i++) {
		if (zombies[i].alive) zombiesOnScreen++;
	}

	if (currentLevel == LEVEL_04)
		sprintf_s(buf, sizeof(buf), "Level 04 | Coins: %d / %d | Zombies: %d", collectedCoins, currentTargetCoins(), zombiesOnScreen);
	else
		sprintf_s(buf, sizeof(buf), "Level %02d | Coins: %d / %d | Zombies: %d", (int)currentLevel, collectedCoins, currentTargetCoins(), zombiesOnScreen);

	iSetColor(0, 0, 0);
	iText(HUD_TEXT_X, HUD_TOP_Y - 2, buf, GLUT_BITMAP_HELVETICA_18);

	if (levelComplete && currentLevel != LEVEL_04) {
		int w = 650, h = 260;
		int x = (SCREEN_WIDTH - w) / 2;
		int y = (SCREEN_HEIGHT - h) / 2;
		iShowImage(x, y, w, h, levelCompleteImg);
	}

	if (gameOver) {
		int w = 650, h = 260;
		int x = (SCREEN_WIDTH - w) / 2;
		int y = (SCREEN_HEIGHT - h) / 2;
		iShowImage(x, y, w, h, gameOverImg);
	}
}

void drawUnderground() {
	const int STEP = 4;
	for (int x = 0; x < SCREEN_WIDTH; x += STEP) {
		int gy = (int)terrainY(playerWorldX + x);

		if (currentLevel == LEVEL_02) {
			int rockTop = gy - L2_ROAD_SURFACE_THICK;
			int deepTop = rockTop - L2_ROCK_LAYER_THICK;
			setLevelUndergroundDeepColor();
			iFilledRectangle(x, 0, STEP, deepTop);
			setLevelUndergroundMidColor();
			iFilledRectangle(x, deepTop, STEP, rockTop - deepTop);
			setLevelRoadMainColor();
			iFilledRectangle(x, rockTop, STEP, L2_ROAD_SURFACE_THICK);
			setLevelRoadHighlightColor();
			iFilledRectangle(x, gy - L2_ROAD_HIGHLIGHT_THICK, STEP, L2_ROAD_HIGHLIGHT_THICK);
		}
		else {
			setLevelUndergroundDeepColor();
			iFilledRectangle(x, 0, STEP, gy - 12);
			setLevelUndergroundMidColor();
			iFilledRectangle(x, gy - 12, STEP, 12);
		}
	}
}

void drawRoad() {
	if (currentLevel == LEVEL_02) return;

	int step = 10;
	int thickness = (currentLevel == LEVEL_01) ? 6 : ((currentLevel == LEVEL_03) ? 4 : ((currentLevel == LEVEL_04) ? 3 : 2));
	int px = 0, py = (int)terrainY(playerWorldX);

	for (int x = step; x <= SCREEN_WIDTH; x += step) {
		int y = (int)terrainY(playerWorldX + x);

		setLevelRoadMainColor();
		for (int t = -thickness; t <= thickness; t++) iLine(px, py + t, x, y + t);

		setLevelRoadHighlightColor();
		iLine(px, py + thickness + 1, x, y + thickness + 1);
		iLine(px, py + thickness + 2, x, y + thickness + 2);

		px = x;
		py = y;
	}
}

void drawCoins() {
	for (size_t i = 0; i < coins.size(); i++) {
		if (coins[i].taken) continue;
		int sx = (int)(coins[i].x - playerWorldX);
		if (sx < -60 || sx > SCREEN_WIDTH + 60) continue;
		int cy = (int)(terrainY(coins[i].x) + coins[i].yOffset);
		iShowImage(sx, cy, COIN_W, COIN_H, coinImg);
	}
}

void drawFuel() {
	for (size_t i = 0; i < fuels.size(); i++) {
		if (fuels[i].taken) continue;
		int sx = (int)(fuels[i].x - playerWorldX);
		if (sx < -80 || sx > SCREEN_WIDTH + 80) continue;
		int fy = (int)(terrainY(fuels[i].x) + fuels[i].yOffset);
		iShowImage(sx, fy, FUEL_W, FUEL_H, fuelImg);
	}
}

void drawBullets() {
	if (currentLevel != LEVEL_02 && currentLevel != LEVEL_03 && currentLevel != LEVEL_04) return;

	int bulletW = getCurrentBulletWidth();
	int bulletH = getCurrentBulletHeight();

	for (size_t i = 0; i < bullets.size(); i++) {
		if (!bullets[i].active) continue;
		int sx = (int)(bullets[i].x - playerWorldX);
		if (sx < -100 || sx > SCREEN_WIDTH + 200) continue;
		iShowImage(sx, (int)bullets[i].y, bulletW, bulletH, bulletImg);
	}
}

void drawZombieHealthBar(const Zombie& z, int drawX, int drawY, int zw, int zh) {
	if (!z.alive) return;
	if (z.maxHealth <= 0) return;

	int barW = ZOMBIE_HEALTH_BAR_W;
	int barH = ZOMBIE_HEALTH_BAR_H;
	int barX = drawX + (zw - barW) / 2;
	int barY = drawY + zh + ZOMBIE_HEALTH_BAR_GAP;

	iSetColor(20, 20, 20);
	iFilledRectangle(barX - 1, barY - 1, barW + 2, barH + 2);

	iSetColor(80, 0, 0);
	iFilledRectangle(barX, barY, barW, barH);

	int fillW = (int)((double)barW * z.health / z.maxHealth);
	if (fillW < 0) fillW = 0;
	if (fillW > barW) fillW = barW;

	if (z.health >= z.maxHealth * 0.6) iSetColor(0, 220, 0);
	else if (z.health >= z.maxHealth * 0.3) iSetColor(255, 200, 0);
	else iSetColor(255, 50, 50);

	if (fillW > 0) {
		iFilledRectangle(barX, barY, fillW, barH);
	}
}

void drawZombies() {
	for (size_t i = 0; i < zombies.size(); i++) {
		if (!zombies[i].alive) continue;

		int sx = (int)(zombies[i].x - playerWorldX);
		if (sx < -200 || sx > SCREEN_WIDTH + 200) continue;

		int zy = (int)terrainY(zombies[i].x);
		int zw = zombieWidth(zombies[i].type);
		int zh = zombieHeight(zombies[i].type);
		int img = getZombieImage(zombies[i].type, zombies[i].frame);

		int dx = sx - (zw - 50) / 2;

		iShowImage(dx, zy, zw, zh, img);
		drawZombieHealthBar(zombies[i], dx, zy, zw, zh);
	}
}

void drawPlay() {
	int bg = bgL1Img;
	if (currentLevel == LEVEL_02) bg = bgL2Img;
	else if (currentLevel == LEVEL_03) bg = bgL3Img;
	else if (currentLevel == LEVEL_04) bg = getLevel04Background();

	iShowImage(bgX, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg);
	iShowImage(bgX + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg);

	drawUnderground();
	drawRoad();
	drawZombies();
	drawCoins();
	drawFuel();
	drawBullets();

	int y = playerDrawY();
	bool moving = (rightHeld || leftHeld || jumpActive);
	int carW = getCurrentCarWidth();
	int carH = getCurrentCarHeight();

	if (currentLevel == LEVEL_01) {
		int carImage = getCarImage(carL1Img, carL1AnimTick, moving, isUphill(), isDownhill());
		if (carImage != 0) {
			iShowImage(playerScreenX, y, carW, carH, carImage);
		}
	}
	else if (currentLevel == LEVEL_02) {
		int carImage = getCarImage(carL2Img, carL2AnimTick, moving, isUphill(), isDownhill());
		if (carImage != 0) {
			iShowImage(playerScreenX, y, carW, carH, carImage);
		}
	}
	else if (currentLevel == LEVEL_03) {
		int carImage = getCarImage(carL3Img, carL3AnimTick, moving, isUphill(), isDownhill());
		if (carImage != 0) {
			iShowImage(playerScreenX, y, carW, carH, carImage);
		}
	}
	else if (currentLevel == LEVEL_04) {
		iShowImage(playerScreenX, y, ROBOT_W, ROBOT_H, getLevel04CharacterImage(moving));
	}

	drawHUD();
}

void drawMenu() { iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, menuBgImg); }
void drawAbout() { iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, aboutPanelImg); }

void drawOptions() {
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, menuBgImg);
	iShowImage(180, 350, 300, 220, optSoundBoxImg);
	iShowImage(720, 350, 300, 220, optControlsBoxImg);
	iShowImage(btnMusicToggle.x, btnMusicToggle.y, btnMusicToggle.w, btnMusicToggle.h, musicOn ? musicOnImg : musicOffImg);
	iShowImage(btnSfxToggle.x, btnSfxToggle.y, btnSfxToggle.w, btnSfxToggle.h, sfxOn ? sfxOnImg : sfxOffImg);
}

void drawSkipBox() {
	iSetColor(0, 0, 0);
	iFilledRectangle(btnSkip.x, btnSkip.y, btnSkip.w, btnSkip.h);
	iSetColor(255, 200, 0);
	iRectangle(btnSkip.x, btnSkip.y, btnSkip.w, btnSkip.h);
	iSetColor(255, 255, 255);
	iText(btnSkip.x + 15, btnSkip.y + 18, (char*)"SKIP (S)", GLUT_BITMAP_HELVETICA_18);
	iSetColor(255, 255, 255);
	iText(20, 20, (char*)"Press S to Skip", GLUT_BITMAP_HELVETICA_18);
}

void drawBootIntro() { iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bootIntroImg); drawSkipBox(); }
void drawStartIntro() { iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, startIntroImg); drawSkipBox(); }
void drawL1ToL2Intro() { iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, l1ToL2Img); drawSkipBox(); }
void drawL2ToL3Intro() { iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, l2ToL3Img); drawSkipBox(); }
void drawL3ToL4Intro() { iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, l3ToL4Img); drawSkipBox(); }

void drawL4CompleteScreen() {
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, levelCompleteImg);
	drawSkipBox();
}

void drawL4EndScreen() {
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, l4EndImg);
	drawSkipBox();
}

void iDraw() {
	iClear();
	if (appState == STATE_BOOT_INTRO) drawBootIntro();
	else if (appState == STATE_START_INTRO) drawStartIntro();
	else if (appState == STATE_L1_TO_L2_INTRO) drawL1ToL2Intro();
	else if (appState == STATE_L2_TO_L3_INTRO) drawL2ToL3Intro();
	else if (appState == STATE_L3_TO_L4_INTRO) drawL3ToL4Intro();
	else if (appState == STATE_L4_COMPLETE_SCREEN) drawL4CompleteScreen();
	else if (appState == STATE_L4_END_SCREEN) drawL4EndScreen();
	else if (appState == STATE_MENU) drawMenu();
	else if (appState == STATE_OPTIONS) drawOptions();
	else if (appState == STATE_ABOUT) drawAbout();
	else if (appState == STATE_PLAY) drawPlay();
}

void iMouse(int button, int state, int mx, int my) {
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

	if (appState == STATE_L1_TO_L2_INTRO) {
		if (pointInRect(mx, my, btnSkip)) {
			playMenuClickSound();
			l1ToL2ElapsedMs = 0;
			startLevel02(fuelLevel);
			appState = STATE_PLAY;
		}
		return;
	}
	if (appState == STATE_L2_TO_L3_INTRO) {
		if (pointInRect(mx, my, btnSkip)) {
			playMenuClickSound();
			l2ToL3ElapsedMs = 0;
			startLevel03(fuelLevel);
			appState = STATE_PLAY;
		}
		return;
	}
	if (appState == STATE_L3_TO_L4_INTRO) {
		if (pointInRect(mx, my, btnSkip)) {
			playMenuClickSound();
			l3ToL4ElapsedMs = 0;
			startLevel04(fuelLevel);
			appState = STATE_PLAY;
		}
		return;
	}
	if (appState == STATE_L4_COMPLETE_SCREEN) {
		if (pointInRect(mx, my, btnSkip)) {
			playMenuClickSound();
			l4CompleteScreenElapsedMs = 0;
			appState = STATE_L4_END_SCREEN;
			l4EndElapsedMs = 0;
		}
		return;
	}
	if (appState == STATE_L4_END_SCREEN) {
		if (pointInRect(mx, my, btnSkip)) {
			playMenuClickSound();
			l4EndElapsedMs = 0;
			appState = STATE_MENU;
		}
		return;
	}
	if (appState == STATE_BOOT_INTRO) {
		if (pointInRect(mx, my, btnSkip)) {
			playMenuClickSound();
			bootElapsedMs = 0;
			appState = STATE_MENU;
		}
		return;
	}
	if (appState == STATE_START_INTRO) {
		if (pointInRect(mx, my, btnSkip)) {
			playMenuClickSound();
			startElapsedMs = 0;
			startLevel01();
			appState = STATE_PLAY;
		}
		return;
	}

	if (appState == STATE_MENU) {
		if (pointInRect(mx, my, btnStart)) {
			playMenuClickSound();
			startElapsedMs = 0;
			appState = STATE_START_INTRO;
			return;
		}
		if (pointInRect(mx, my, btnOptions)) {
			playMenuClickSound();
			appState = STATE_OPTIONS;
			return;
		}
		if (pointInRect(mx, my, btnAbout)) {
			playMenuClickSound();
			appState = STATE_ABOUT;
			return;
		}
		if (pointInRect(mx, my, btnExit)) {
			playMenuClickSound();
			stopGameplayBgm();
			exit(0);
		}
	}
	else if (appState == STATE_OPTIONS) {
		if (pointInRect(mx, my, btnMusicToggle)) {
			musicOn = !musicOn;
			updateGameplayBgm();
			return;
		}
		if (pointInRect(mx, my, btnSfxToggle)) {
			sfxOn = !sfxOn;
			if (!sfxOn) stopEffectSound();
			return;
		}
	}
	else if (appState == STATE_ABOUT) {
		if (pointInRect(mx, my, btnAboutExit)) {
			playMenuClickSound();
			appState = STATE_MENU;
		}
	}
}

void iMouseMove(int mx, int my) {}
void iPassiveMouseMove(int mx, int my) {}

void iKeyboard(unsigned char key) {
	if (appState == STATE_L1_TO_L2_INTRO) {
		if (key == 's' || key == 'S') {
			playMenuClickSound();
			l1ToL2ElapsedMs = 0;
			startLevel02(fuelLevel);
			appState = STATE_PLAY;
		}
		return;
	}
	if (appState == STATE_L2_TO_L3_INTRO) {
		if (key == 's' || key == 'S') {
			playMenuClickSound();
			l2ToL3ElapsedMs = 0;
			startLevel03(fuelLevel);
			appState = STATE_PLAY;
		}
		return;
	}
	if (appState == STATE_L3_TO_L4_INTRO) {
		if (key == 's' || key == 'S') {
			playMenuClickSound();
			l3ToL4ElapsedMs = 0;
			startLevel04(fuelLevel);
			appState = STATE_PLAY;
		}
		return;
	}
	if (appState == STATE_L4_COMPLETE_SCREEN) {
		if (key == 's' || key == 'S') {
			playMenuClickSound();
			l4CompleteScreenElapsedMs = 0;
			appState = STATE_L4_END_SCREEN;
			l4EndElapsedMs = 0;
		}
		return;
	}
	if (appState == STATE_L4_END_SCREEN) {
		if (key == 's' || key == 'S') {
			playMenuClickSound();
			l4EndElapsedMs = 0;
			appState = STATE_MENU;
		}
		return;
	}
	if (appState == STATE_BOOT_INTRO) {
		if (key == 's' || key == 'S') {
			playMenuClickSound();
			bootElapsedMs = 0;
			appState = STATE_MENU;
		}
		return;
	}
	if (appState == STATE_START_INTRO) {
		if (key == 's' || key == 'S') {
			playMenuClickSound();
			startElapsedMs = 0;
			startLevel01();
			appState = STATE_PLAY;
		}
		return;
	}

	if (appState == STATE_PLAY && !levelComplete && !gameOver) {
		if (key == 'b' || key == 'B') { applyBoostJump(); return; }
		if (key == ' ') { shoot(); return; }
	}

	if (appState == STATE_PLAY && gameOver) {
		if (key == 'r' || key == 'R') {
			if (currentLevel == LEVEL_01) startLevel01();
			else if (currentLevel == LEVEL_02) startLevel02(MAX_FUEL);
			else if (currentLevel == LEVEL_03) startLevel03(MAX_FUEL);
			else startLevel04(MAX_FUEL);
			return;
		}
		if (key == 27) {
			appState = STATE_MENU;
			gameOver = false;
			rightHeld = leftHeld = false;
			return;
		}
	}

	if (appState == STATE_PLAY && levelComplete) {
		if (key == 'n' || key == 'N') {
			if (currentLevel == LEVEL_01) { l1ToL2ElapsedMs = 0; appState = STATE_L1_TO_L2_INTRO; return; }
			if (currentLevel == LEVEL_02) { l2ToL3ElapsedMs = 0; appState = STATE_L2_TO_L3_INTRO; return; }
			if (currentLevel == LEVEL_03) { l3ToL4ElapsedMs = 0; levelComplete = false; appState = STATE_L3_TO_L4_INTRO; return; }
			if (currentLevel == LEVEL_04) {
				levelComplete = false;
				l4CompleteScreenElapsedMs = 0;
				appState = STATE_L4_COMPLETE_SCREEN;
				return;
			}
		}
		if (key == 'r' || key == 'R') {
			if (currentLevel == LEVEL_01) startLevel01();
			else if (currentLevel == LEVEL_02) startLevel02(MAX_FUEL);
			else if (currentLevel == LEVEL_03) startLevel03(MAX_FUEL);
			else startLevel04(MAX_FUEL);
			return;
		}
		if (key == 27) {
			appState = STATE_MENU;
			levelComplete = false;
			rightHeld = leftHeld = false;
			return;
		}
	}

	if (key == 27) {
		if (appState == STATE_PLAY) {
			appState = STATE_MENU;
			rightHeld = leftHeld = false;
			return;
		}
		if (appState == STATE_OPTIONS || appState == STATE_ABOUT) {
			playMenuClickSound();
			appState = STATE_MENU;
			return;
		}
	}
}

void iSpecialKeyboard(unsigned char key) {}