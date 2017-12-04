
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
