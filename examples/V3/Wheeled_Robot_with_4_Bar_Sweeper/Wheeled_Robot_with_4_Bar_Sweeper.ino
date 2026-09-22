// This project aims to educate the user on how to control a differential drive
// robot with two DC motors and induce a sweeping motion with a 4 bar mechanism
// and finite servo.
#include <MicroBlue.h>
#include <Servo.h>
#include <SnappyXOShield.h>
MicroBlueManager manager;

Servo arm;

int angle;

void setup() {
	initMotors();
	arm.attach(A0);
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
	} else if (msg.id == "b0") {
		if (msg.value == "1") {
			arm.write(180);
			delay(1000);
			arm.write(0);
			delay(1000);
		}
	}
}
