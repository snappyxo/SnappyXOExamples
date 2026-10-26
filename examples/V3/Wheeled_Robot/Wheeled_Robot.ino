// This project aims to educate the user on how to connect the motors of a 2WD
// car and program it through Arduino.
//
// Developed by A+ Mobile Solutions Inc
// Licensed under the MIT License. See LICENSE for details.
#include <SnappyXOShield.h>

SnappyXOShield shield(SnappyXOShield::V3);  // the shield version printed on the board: V3 or V2

void setup() {
	// Initialize motors
	shield.begin();
	// If a wheel turns backward when it should go forward, uncomment its line:
	// shield.invertLeft();   // left wheel
	// shield.invertRight();  // right wheel

	// Begin serial communication
	Serial.begin(9600);
}

// This is the main loop the code will follow
void loop() {
	Serial.println("Forward");
	shield.forward();
	delay(1000);
	Serial.println("Turn Right");
	shield.spinRight();
	delay(1000);
	Serial.println("Turn Left");
	shield.spinLeft();
	delay(1000);
	Serial.println("Reverse");
	shield.reverse();
	delay(1000);
}
