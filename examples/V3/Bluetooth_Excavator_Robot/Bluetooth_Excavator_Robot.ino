// This project aims to educate the user on how to control a 2WD car using
// bluetooth as well as an excavator mechanism using finite servos.
#include <MicroBlue.h>
#include <Servo.h>
#include <SnappyXOShield.h>
MicroBlueManager manager;

Servo arm;
Servo sweeper;

int armpos = 0;
int angle;

void setup() {
	initMotors();
	arm.attach(A0);
	sweeper.attach(A1);
	manager.begin("My BLE Module");
}

void loop() {
	MicroBlueMessage msg = manager.read();

	if (msg.id == "d0" || msg.id == "d1") {
		int throttle, steering;
		sscanf(msg.value.c_str(), "%d,%d", &steering, &throttle);
		throttle -= 512;
		steering -= 512;
		drive(throttle, steering);
	} else if (msg.id == "sl0") {
		armpos = map(msg.value.toInt(), 0, 180, 0, 100);
		arm.write(armpos);
	} else if (msg.id == "sl1") {
		angle = map(msg.value.toInt(), 0, 180, 0, 100);
		sweeper.write(angle);
	}
}
