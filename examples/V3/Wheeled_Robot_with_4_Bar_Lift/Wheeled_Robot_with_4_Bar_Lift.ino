// This project aims to educate the user on how to hook up a bluetooth module to
// control a 2WD car with and toggle 4 bar linkage that perfoms a lifting
// motion.
#include <MicroBlue.h>
#include <Servo.h>
#include <SnappyXOShield.h>
MicroBlueManager manager;

Servo arm;

int angle;

void setup() {
	initMotors();
	arm.attach(A2);
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
			arm.write(180)
		}; else if (msg.value == "0") {
			arm.write(0)
		};
		delay(300);
	}
}
