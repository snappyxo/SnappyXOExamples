// This project aims to educate the user on how to control a 2WD car using an
// Ultrasonic Sensor as well as an "punching" mechanism using finite servos.
// Include libraries

#include <Servo.h>
#include <SnappyXOShield.h>

// Pin Declarations

const int trig = 13;
const int echo = 12;

// Initialize Objects

Servo armTOP;
Servo armBOTTOM;

// Function to stop motor movement
void PAUSE() { pause(); }

// Function to move forward
void FORWARD() { forward(); }

// Function to move in reverse
void REVERSE() { reverse(); }

// Function to turn left
void TURN_LEFT() { turnLeft(); }

// Function to turn right
void TURN_RIGHT() { turnRight(); }

// Functions to convert ultrasonic readings to distance
long microsecondsToInches(long microseconds) { return microseconds / 74 / 2; }
long microsecondsToCentimeters(long microseconds) {
	return microseconds / 29 / 2;
}

void setup() {
	// Begin serial communication
	Serial.begin(9600);

	// Attach and setup servo positions
	armTOP.attach(A0);
	armBOTTOM.attach(A1);
	armTOP.write(179);
	armBOTTOM.write(0);

	// Initialize motors (invertL=true to match original wiring polarity)
	initMotors(true, false);
}

void loop() {
	FORWARD();

	// check for nearest object
	long duration, inches, cm;
	pinMode(trig, OUTPUT);
	digitalWrite(trig, LOW);
	delayMicroseconds(2);
	digitalWrite(trig, HIGH);
	delayMicroseconds(5);
	digitalWrite(trig, LOW);
	pinMode(echo, INPUT);

	// convert ultrasonic reading to distance
	duration = pulseIn(echo, HIGH);
	inches = microsecondsToInches(duration);
	cm = microsecondsToCentimeters(duration);
	delay(10);

	// generate random integer
	int randint = random(0, 2);

	/* check distance and follow instructions:
	   stop -> punch -> retract arm -> reverse -> turn -> restart loop
	*/
	if (cm < 20) {
		PAUSE();
		armTOP.write(179);
		armBOTTOM.write(0);
		delay(500);
		armTOP.write(0);
		armBOTTOM.write(179);
		REVERSE();
		delay(500);
		if (randint == 0) {
			TURN_LEFT();
		} else {
			TURN_RIGHT();
		}
		delay(200);
	}
}
