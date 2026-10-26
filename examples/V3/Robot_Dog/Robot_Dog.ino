// This project aims to educate the user on how two motors can generate the
// motion needed to create a robot dog
//
// Developed by A+ Mobile Solutions Inc
// Licensed under the MIT License. See LICENSE for details.
#include <SnappyXOShield.h>

SnappyXOShield shield(SnappyXOShield::V3);  // the shield version printed on the board: V3 or V2

// Pin Definitions
const int trig = A0;
const int echo = A1;

int speed;
int outputPins[] = {A0};

void setup() {
	Serial.begin(9600);

	for (int i = 0; i < 1; i++)	 // Assigns pinModes to the above pins
	{
		pinMode(outputPins[i], OUTPUT);
	}
	pinMode(echo, INPUT);

	shield.begin();
	shield.invertLeft();
}

void loop() {
	long duration, distance;
	pulseIn(echo, LOW);

	digitalWrite(trig, LOW);
	delayMicroseconds(2);
	digitalWrite(trig, HIGH);
	delayMicroseconds(5);
	digitalWrite(trig, LOW);

	duration = pulseIn(echo, HIGH);
	distance = microsecondsToInches(duration);

	if (distance > 3) {
		shield.forward(255);
	} else {
		Serial.println("Object Detected");
		shield.stop();
		delay(200);
	}
}

long microsecondsToInches(long microseconds) { return microseconds / 74 / 2; }
