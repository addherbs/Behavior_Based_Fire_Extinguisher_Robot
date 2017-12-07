#include <string>
#include <ev3.h>
#include <stdio.h>
#include <stdlib.h>
#define goalColor 5

void moveForward(int speed, int time) {
    OnFwdSync(OUT_AB, speed * 2);
    Wait(time);
}
void moveBackward(int speed, int time) {
    OnRevSync(OUT_AB, speed);
    Wait(time * 2);
}
void rotateClockwise(int inputTime) {
    RotateMotor(OUT_A, 10, inputTime);
    Wait(1000);
}
void rotateAntiClockwise(int inputTime) {
    RotateMotor(OUT_B, 10, inputTime);
    Wait(1000);
}
int generateRandom(int range) {
    return rand() % range;
}


int main() {
    int count = 0;
    InitEV3();
    setAllSensorMode(TOUCH_PRESS, TOUCH_PRESS, US_DIST_MM, COL_COLOR);
    int currentUltraRange = 0;
    int currentRandom = 0;
    int color = 0;
    color = readSensor(IN_4);
    while (color != goalColor) {
        LcdClean();
        // Checking for candle
        color = readSensor(IN_4);
        // Checking for IR sensor
        currentUltraRange = (int) readSensor(IN_3);
        // Check for fire(GOAL)
        if (color == goalColor) {
            //Goal Reached
            std::string goal("G");
            LcdPrintf(1, "%s ", goal.c_str());
            Off(OUT_A);
            Off(OUT_B);
            for (int lol = 0; lol < 5; lol++) {
                OnFwdReg(OUT_D, 199);
                Wait(300);
            }
            break;
        } else {
            //If both touch sensor
            // Obstacle in US Range
            if ((readSensor(IN_1) == 1) && (readSensor(IN_2) == 1)
                    && (currentUltraRange < 200)) {
                moveBackward(10, 1100);
                rotateClockwise((generateRandom(45) + 30) * 4);
                std::string bothInRange("BI");
                LcdPrintf(1, "%s ", bothInRange.c_str());
                Wait(2000);
            } else {
                //If both touch sensor
                // Obstacle not in US Range
                if ((readSensor(IN_1) == 1) && (readSensor(IN_2) == 1)
                        && (currentUltraRange > 200)) {
                    moveBackward(10, 1100);
                    rotateAntiClockwise((generateRandom(45) + 30) * 4);
                    std::string bothNotInRange("BO");
                    LcdPrintf(1, "%s ", bothNotInRange.c_str());
                    Wait(2000);
			}
		}
	}
	
	FreeEV3();
}
