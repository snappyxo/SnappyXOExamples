// This project aims to educate the user on how two motors can generate the
// motion needed to create a robot dog
#include <SnappyXOShield.h>

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

	initMotors(true, false);
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
		forward(255);
	} else {
		Serial.println("Object Detected");
		pause();
		delay(200);
	}
}

long microsecondsToInches(long microseconds) { return microseconds / 74 / 2; }
