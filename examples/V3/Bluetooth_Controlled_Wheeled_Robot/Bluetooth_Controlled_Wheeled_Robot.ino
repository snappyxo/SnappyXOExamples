// This project aims to educate the user on how to control a differential drive
// robot with two motors using a bluetooth module and the MicroBlue app.
#include <MicroBlue.h>
#include <SnappyXOShield.h>
MicroBlueManager manager;

void setup() {
	initMotors();
	manager.begin("My BLE Module");
	Serial.begin(9600);
}

void loop() {
	MicroBlueMessage msg = manager.read();

	if (msg.id == "d0" || msg.id == "d1") {
		int throttle, steering;
		sscanf(msg.value.c_str(), "%d,%d", &steering, &throttle);
		throttle -= 512;
		steering -= 512;
		drive(throttle, steering);
		Serial.println(throttle, steering);
	}
}
