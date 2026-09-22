// This project aims to educate the user on how to control a 2WD car using an
// Ultrasonic Sensor as well as an catapult mechanism using finite servos.
// Include libraries
#include <Servo.h>
#include <SnappyXOShield.h>

// Initialize servo objects
Servo armR;
Servo armL;

// ULTRASONIC SENSOR PINS
const int trig = 13;
const int echo = 12;

// Function to catapult ball and return to default position
void CATAPULT() {
	armR.write(50);
	armL.write(0);
	delay(1000);
	armR.write(10);
	armL.write(40);
	delay(5000);
}

// Configures the motor controller to stop the motors.
void PAUSE() { pause(); }

// Configures the motor controller to have the robot move forward.
void FORWARD() { forward(); }

// Configures the motor controller to have the robot move backwards.
void REVERSE() { reverse(); }

/* TURN LEFT */
void TURN_LEFT() { turnLeft(); }

/* TURN RIGHT */
void TURN_RIGHT() { turnRight(); }

// Functions to convert ultrasonic reading to a distance
long microsecondsToInches(long microseconds) { return microseconds / 74 / 2; }
long microsecondsToCentimeters(long microseconds) {
	return microseconds / 29 / 2;
}

void setup() {
	// Begin serial communication
	Serial.begin(9600);

	// attach servo objects to pins
	armL.attach(A0);
	armR.attach(A1);

	// Initialize motor driver (left motor inverted to match original wiring)
	initMotors(true, false, false);

	// Reset Catapult to start position
	armR.write(10);
	armL.write(40);
}

void loop() {
	FORWARD();
	delay(200);

	// generate random integer of 0 or 1
	int randint = random(0, 2);

	// get ultrasonic reading
	long duration, inches, cm;
	pinMode(trig, OUTPUT);
	digitalWrite(trig, LOW);
	delayMicroseconds(2);
	digitalWrite(trig, HIGH);
	delayMicroseconds(5);
	digitalWrite(trig, LOW);
	pinMode(echo, INPUT);

	// convert ultrasonic reading to a distance
	duration = pulseIn(echo, HIGH);
	inches = microsecondsToInches(duration);
	cm = microsecondsToCentimeters(duration);
	delay(10);

	/* check for distance from object and random integer to do the following:
	   reverse -> pause -> trigger catapult -> turn left/right based on randint
	   -> go forward -> restart loop
	*/
	if ((cm < 18) && (randint == 0)) {
		REVERSE();
		delay(500);
		PAUSE();
		delay(500);
		CATAPULT();
		delay(500);
		TURN_LEFT();
		delay(800);
		FORWARD();
		delay(200);
	}
	if ((cm < 18) && (randint == 1)) {
		REVERSE();
		delay(500);
		PAUSE();
		delay(500);
		CATAPULT();
		delay(800);
		TURN_RIGHT();
		delay(800);
		FORWARD();
		delay(200);
	}
}
