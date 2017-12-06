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
		if (color == 5) {

			//Goal Reached
			std::string goal("G");
			LcdPrintf(1, "%s ", goal.c_str());
			Wait(2000);
			break;
		} else {

			//If both touch sensor
			// Obstacle in US Range
			if ((readSensor(IN_1) == 1) && (readSensor(IN_2) == 1)
					&& (currentUltraRange < 50)) {

				moveBackward(10, 1100);

				//Rotate 90 degrees Clockwise
				//OnRevSync(OUT_AB, 10);
				rotateClockwise(800);

				std::string bothInRange("BI");
				LcdPrintf(1, "%s ", bothInRange.c_str());
				Wait(2000);

			} 
		}
	}
	
	FreeEV3();
}
