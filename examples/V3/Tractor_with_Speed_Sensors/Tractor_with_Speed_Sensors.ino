// Shape-Drawing Encoder Bot This project aims to create a dual-motor driven
// wheeled robot that uses the encoders to guage the robot's distance, allowing
// shape paths to be defined. Pin Definitions
#define rightEncoder \
	2  // Right in this case signifies the right wheel when observed from back
	   // of robot
#define leftEncoder 3
#include <SnappyXOShield.h>

// For Tachiomter
float pulsePerRev = 15.0;
float R_wheel = 3.0;  // [cm]
float R_car = 16.0;	  // [cm]
float cmPerPulse = 2.0 * PI * R_wheel / (4.0 * pulsePerRev);
float rightPulse = 0;
float leftPulse = 0;

// For Motor
int LPWM = 185;
int RPWM = 155;

// Other parameters
bool is_Running = 1;
float slipFactor = 1.075;

// Functions for tracking left and right pulses
void rightPulseAdd() {
	rightPulse++;
	delay(1);
}

void leftPulseAdd() {
	leftPulse++;
	delay(1);
}

// Path Actions

void stopBot() {  // This function sets all motors to off
	pause();
}

void goForward(
	float DISTANCE) {  // This function causes the robot to move DISTANCE in cm

	while (leftPulse * cmPerPulse < DISTANCE) {
		_motorWrite(LPWM, RPWM);
		Serial.println(leftPulse * cmPerPulse);
	}
	leftPulse = 0;
}

void turnRight(float ANGLE) {  // This function causes the robot to turn right
							   // "ANGLE" degrees
	float angleInRad = slipFactor * ANGLE * (PI / 180.0);
	float dis = angleInRad * R_car;

	while (leftPulse * cmPerPulse < dis) {
		_motorWrite(LPWM, 0);
		Serial.println(leftPulse * cmPerPulse);
	}

	leftPulse = 0;
}

void square(float sideLength,
			int delayTime) {  // This function causes the robot to drive in the
							  // shape of a square
	for (int ii = 0; ii < 4; ii++) {  // with sides of legnth "sideLength" (cm)
									  // and with delays of "delayTime" (ms)
		goForward(sideLength);
		stopBot();
		delay(delayTime);
		turnRight(90);
		stopBot();
		delay(delayTime);
	}
}

void triangle(float sideLength,
			  int delayTime) {	// This function causes the robot to drive in
								// the shape of a triangle
	for (int ii = 0; ii < 3; ii++) {  // with sides of legnth "sideLength" and
									  // with delays of "delayTime"
		goForward(sideLength);
		stopBot();
		delay(500);
		turnRight(120);
		stopBot();
		delay(500);
	}
}

void polygon(float sideLength, int delayTime,
			 int numOfSides) {	// This function causes the robot to drive in
								// the shape of a polygon
	for (int ii = 0; ii < numOfSides;
		 ii++) {  // with sides of legnth "sideLength", with delays of
				  // "delayTime" and
		goForward(
			sideLength);  // with a given number of sides called "numOfSides"
		stopBot();
		delay(delayTime);
		turnRight(360.0 / numOfSides);
		stopBot();
		delay(delayTime);
	}
}

void setup() {
	// put your setup code here, to run once:

	// Begin serial communication
	Serial.begin(9600);

	// Set pinModes
	pinMode(rightEncoder, INPUT);
	pinMode(leftEncoder, INPUT);

	// Initialize motor driver
	initMotors(true, false);

	// Attach interrupts to the pins connected to encoders
	attachInterrupt(digitalPinToInterrupt(leftEncoder), leftPulseAdd, FALLING);
	attachInterrupt(digitalPinToInterrupt(rightEncoder), rightPulseAdd,
					FALLING);
}

void loop() {
	// This if statement causes the code below to only be ran once
	if (is_Running == 1) {
		square(30, 500);
		delay(2000);
		triangle(30, 500);
		delay(2000);
		polygon(30, 500, 6);
		is_Running = 0;
	}
}