// This code lights up two LEDs while a two wheel drive robot car moves.
//
// Developed by A+ Mobile Solutions Inc
// Licensed under the MIT License. See LICENSE for details.
#include <SnappyXOShield.h>

SnappyXOShield shield(SnappyXOShield::V3);  // the shield version printed on the board: V3 or V2

// Pin Definitions
int PIN_LED_GREEN = 3;
int PIN_LED_RED = 2;

void setup() {
	// Define pinModes
	pinMode(PIN_LED_GREEN, OUTPUT);
	pinMode(PIN_LED_RED, OUTPUT);

	shield.begin();
	// Begin serial communication
	Serial.begin(9600);
}

void loop() {
	digitalWrite(PIN_LED_GREEN, HIGH);	// green for forward
	Serial.println("Forward");
	shield.forward();
	delay(1000);

	digitalWrite(PIN_LED_GREEN, LOW);  // red for stoping
	digitalWrite(PIN_LED_RED, HIGH);
	Serial.println("Pause");
	shield.stop();
	delay(1000);

	digitalWrite(PIN_LED_RED, LOW);
	Serial.println("Turn Left");
	shield.spinLeft();
	delay(1000);
	Serial.println("Turn Right");
	shield.spinRight();
	delay(1000);

	shield.reverse();	// flashing green for reverse
	for (int i = 0; i <= 1000; i += 500) {
		digitalWrite(PIN_LED_GREEN, HIGH);
		delay(250);
		digitalWrite(PIN_LED_GREEN, LOW);
		delay(250);
	}
}
