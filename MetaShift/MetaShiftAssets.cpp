#include "MetaShiftShared.hpp"

void loadZombieAssets() {
	for (int i = 0; i < 8; i++) {
		char path[100] = { 0 };
		sprintf_s(path, sizeof(path), "Images//Zombie%d.png", i + 1);
		normalZombieImg[i] = iLoadImage(path);
	}

	for (int i = 0; i < 4; i++) {
		char path[100] = { 0 };
		sprintf_s(path, sizeof(path), "Images//ArmoredZombie%d.png", i + 1);
		armoredZombieImg[i] = iLoadImage(path);
	}

	for (int i = 0; i < 4; i++) {
		char path[100] = { 0 };
		sprintf_s(path, sizeof(path), "Images//FastZombie%d.png", i + 1);
		fastZombieImg[i] = iLoadImage(path);
	}

	for (int i = 0; i < 7; i++) {
		char path[100] = { 0 };
		sprintf_s(path, sizeof(path), "Images//MonsterZombie%d.png", i + 1);
		monsterZombieImg[i] = iLoadImage(path);
	}
}

void loadLevel1CarImages() {
	carL1Img[0] = iLoadImage("Images//Car-1-1.png");
	carL1Img[1] = iLoadImage("Images//Car-1-2.png");
	carL1Img[2] = iLoadImage("Images//Car-1-3.png");
	carL1Img[3] = iLoadImage("Images//Car-1-4.png");
	carL1Img[4] = iLoadImage("Images//Car-1-5.png");
	carL1Img[5] = iLoadImage("Images//Car-1-6.png");
	carL1Img[6] = iLoadImage("Images//Car-1-7.png");

	for (int i = 0; i < 7; i++) {
		if (carL1Img[i] == 0) {
			for (int j = 0; j < 7; j++) {
				if (carL1Img[j] != 0) {
					carL1Img[i] = carL1Img[j];
					break;
				}
			}
		}
	}
}

void loadLevel2CarImages() {
	carL2Img[0] = iLoadImage("Images//Car2-1.png");
	carL2Img[1] = iLoadImage("Images//Car2-2.png");
	carL2Img[2] = iLoadImage("Images//Car2-3.png");
	carL2Img[3] = iLoadImage("Images//Car2-4.png");
	carL2Img[4] = iLoadImage("Images//Car2-5.png");
	carL2Img[5] = iLoadImage("Images//Car2-6.png");
	carL2Img[6] = iLoadImage("Images//Car2-7.png");

	for (int i = 0; i < 7; i++) {
		if (carL2Img[i] == 0) {
			for (int j = 0; j < 7; j++) {
				if (carL2Img[j] != 0) {
					carL2Img[i] = carL2Img[j];
					break;
				}
			}
		}
	}
}

void loadLevel3CarImages() {
	carL3Img[0] = iLoadImage("Images//Car3-1.png");
	carL3Img[1] = iLoadImage("Images//Car3-2.png");
	carL3Img[2] = iLoadImage("Images//Car3-3.png");
	carL3Img[3] = iLoadImage("Images//Car3-4.png");
	carL3Img[4] = iLoadImage("Images//Car3-5.png");
	carL3Img[5] = iLoadImage("Images//Car3-6.png");
	carL3Img[6] = iLoadImage("Images//Car3-7.png");

	for (int i = 0; i < 7; i++) {
		if (carL3Img[i] == 0) {
			for (int j = 0; j < 7; j++) {
				if (carL3Img[j] != 0) {
					carL3Img[i] = carL3Img[j];
					break;
				}
			}
		}
	}
}

void loadLevel04Background() {
	bgL4Img = iLoadImage("Images//bg_level4.png");
}

void loadLevel04CharacterImages() {
	l4RobotIdleImg = iLoadImage("Images//L4_Robot_Idle.png");
	for (int i = 0; i < 4; i++) {
		char path[100] = { 0 };
		sprintf_s(path, sizeof(path), "Images//L4_Robot_Walk_%d.png", i + 1);
		l4RobotWalkImg[i] = iLoadImage(path);
	}
	l4RobotJumpImg = iLoadImage("Images//L4_Robot_Jump.png");

	if (l4RobotIdleImg == 0) l4RobotIdleImg = carL3Img[3];
	for (int i = 0; i < 4; i++) {
		if (l4RobotWalkImg[i] == 0) l4RobotWalkImg[i] = l4RobotIdleImg;
	}
	if (l4RobotJumpImg == 0) l4RobotJumpImg = l4RobotIdleImg;
}

void initUI() {
	menuBgImg = iLoadImage("Images//menu_bg.png");
	aboutPanelImg = iLoadImage("Images//about_panel.png");
	bootIntroImg = iLoadImage("Images//intro_story.png");
	startIntroImg = iLoadImage("Images//levle_01.png");
	optSoundBoxImg = iLoadImage("Images//opt_sound_box.png");
	optControlsBoxImg = iLoadImage("Images//opt_controls_box.png");
	musicOnImg = iLoadImage("Images//music_on.png");
	musicOffImg = iLoadImage("Images//music_off.png");
	sfxOnImg = iLoadImage("Images//sfx_on.png");
	sfxOffImg = iLoadImage("Images//sfx_off.png");
	levelCompleteImg = iLoadImage("Images//level_complete.png");
	gameOverImg = iLoadImage("Images//game_over.png");
	l1ToL2Img = iLoadImage("Images//level_02.png");
	l2ToL3Img = iLoadImage("Images//level_03.png");
	l3ToL4Img = iLoadImage("Images//level_04.png");
	l4EndImg = iLoadImage("Images//l4_complete.png");

	btnStart = { 470, 300, 260, 75 };
	btnOptions = { 505, 220, 190, 55 };
	btnAbout = { 505, 155, 190, 55 };
	btnExit = { 505, 90, 190, 55 };
	btnMusicToggle = { 285, 470, 120, 45 };
	btnSfxToggle = { 285, 400, 120, 45 };
	btnAboutExit = { 545, 30, 110, 55 };
	btnSkip = { SCREEN_WIDTH - 160, 10, 140, 45 };
}

void loadGameAssets() {
	bgL1Img = iLoadImage("Images//bg_level1.png");
	bgL2Img = iLoadImage("Images//bg_level2.png");
	bgL3Img = iLoadImage("Images//bg_level3.png");
	bgL4Img = iLoadImage("Images//bg_level4.png");

	coinImg = iLoadImage("Images//coin.png");
	fuelImg = iLoadImage("Images//fuel.png");
	bulletImg = iLoadImage("Images//bullet.png");
	fuelLabelImg = iLoadImage("Images//fuel_label.png");
	boostLabelImg = iLoadImage("Images//boost_label.png");

	loadLevel1CarImages();
	loadLevel2CarImages();
	loadLevel3CarImages();
	loadZombieAssets();
	loadLevel04CharacterImages();

	if (bgL4Img == 0) loadLevel04Background();
	if (bgL1Img == 0) bgL1Img = menuBgImg;
	if (bgL2Img == 0) bgL2Img = bgL1Img;
	if (bgL3Img == 0) bgL3Img = bgL2Img;
	if (bgL4Img == 0) bgL4Img = bgL3Img;
}