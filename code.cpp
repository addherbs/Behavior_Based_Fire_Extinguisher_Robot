#include <string>
#include <ev3.h>
#include <stdio.h>
#include <stdlib.h>
#define goalColor

// Move Forward Function
// Parameters Speed and time
void moveForward(int speed, int time) {
    OnFwdSync(OUT_AB, speed * 2); // To double the speed entered we do *2
    Wait(time); // Wait for time input
}

// Move Backward Function
// Parameters Speed and time
void moveBackward(int speed, int time) {
    OnRevSync(OUT_AB, speed); // To double the speed entered we do *2
    Wait(time * 2); // Wait for time input
}

// Rotate Clockwise Function
// Parameters time
void rotateClockwise(int inputTime) {
    RotateMotor(OUT_A, 10, inputTime);
    Wait(1000); // Wait for time input
}

// Rotate Anticlockwise Function
// Parameters time
void rotateAntiClockwise(int inputTime) {
    RotateMotor(OUT_B, 10, inputTime);
    Wait(1000); // Wait for time input
}

// Generates Random withing 0 - range
// If range = 10
// A random value between 0-9
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
                } else {
                    //If left touch
                    if ((readSensor(IN_1) == 1)) {
                        moveBackward(10, 1100);
                        //rotate clockwise 10-45
                        //    currentRandom = rand() % 10 + 35;
                        rotateClockwise((generateRandom(45) + 30) * 4);
                        std::string left("BTL");
                        LcdPrintf(1, "%s ", left.c_str());
                        Wait(2000);
                    } else {
                        //If right touch
                        // Obstacle not in US Range
                        currentUltraRange = (int) readSensor(IN_3);
                        if ((readSensor(IN_2) == 1)
                                && (currentUltraRange > 150)) {
                            //move backwards
                            moveBackward(10, 1100);
                            //rotate anticlockwise 10-45
                            rotateAntiClockwise((generateRandom(45) + 30) * 4);
                            std::string right("BTR N");
                            LcdPrintf(1, "%s ", right.c_str());
                            Wait(2000);
                        }
                        //If right touch
                        // Obstacle in US Range
                        else if ((readSensor(IN_2) == 1)
                                && (currentUltraRange < 150)) {
                            //move backwards
                            moveBackward(10, 1100);
                            //rotate clockwise 10-45
                            rotateClockwise((generateRandom(45) + 30) * 4);
                            std::string right("BTR R");
                            LcdPrintf(1, "%s ", right.c_str());
                            Wait(2000);
                        } else {
                            // Final state Move forward
							// If no other cases are true. The robot will move forward
                            if ((readSensor(IN_1) == 0)
                                    && (readSensor(IN_2) == 0)
                                    && color != goalColor) {
										
                                std::string goal("G");
                                std::string forward("FW");
                                LcdPrintf(1, "%s ", forward.c_str());
                                currentUltraRange = (int) readSensor(IN_3);
								
								//Checks if the obstacle is there withing sonar range
								//If there, the robot will rotate in clockwise direction
                                if (currentUltraRange < 30) {
                                    rotateClockwise((5) * 4);
                                }
								
								//Move forward
                                moveForward(10, 150);
								
								//Check goal state
                                if (readSensor(IN_4) == goalColor) {
                                    LcdPrintf(1, "%s ", goal.c_str());
                                    Off(OUT_A);
                                    Off(OUT_B);
                                    for (int lol = 0; lol < 5; lol++) {
                                        OnFwdReg(OUT_D, 199);
                                        Wait(300);
                                    }
                                    break;
                                }
                            }
							
							// 25 times forward move for the next random calculation
                            if (count < 25) {
                                count++;
                            } else {
                                count = 0;
                                //generate random number between 20-140
                                currentRandom = generateRandom(140) + 20;
                                LcdPrintf(1, "%d ", currentRandom);
                                //Randomly Clockwise direction
                                if (currentRandom > 80) {
                                    rotateClockwise((160 - currentRandom) * 4);
                                } else {
                                    //Randomly Anti-clockwise direction
                                    rotateAntiClockwise(currentRandom * 4);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    FreeEV3();
}