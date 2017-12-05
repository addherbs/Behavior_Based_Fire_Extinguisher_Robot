#include <string>
#include <ev3.h>
#include <stdio.h>
#include <stdlib.h>

void moveForward(int speed, int time) {
	OnFwdSync(OUT_AB, speed);
	Wait(time);
}

void moveBackward(int speed, int time) {
	OnRevSync(OUT_AB, speed);
	Wait(time);
}

void rotateClockwise(int time) {
	OnFwdReg(OUT_A, 20);
	OnRevReg(OUT_B, 20);
	Wait(time);

}
void rotateAntiClockwise(int time) {
	OnFwdReg(OUT_B, 20);
	OnRevReg(OUT_A, 20);
	Wait(time);
}

int generateRandom(int range) {
	return rand() % range;
}

int main() {

	InitEV3();
	setAllSensorMode(TOUCH_PRESS, TOUCH_PRESS, US_DIST_MM, COL_COLOR);
	int currentUltraRange = 0;
	int currentRandom = 0;
	int color = 0;
	color = readSensor(IN_4);
	
	while (color != 5) {

		LcdClean();
		// Checking for candle
		color = readSensor(IN_4);
		Wait(2000);
		currentUltraRange = (int) readSensor(IN_3);

	}
	
	FreeEV3();
}
