#include "MetaShiftShared.hpp"
#include "iGraphics.h"

int main() {
	srand((unsigned)time(0));
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "MetaShift");
	initUI();
	loadGameAssets();
	iSetTimer(16, updateGame);
	iStart();
	stopGameplayBgm();
	return 0;
}