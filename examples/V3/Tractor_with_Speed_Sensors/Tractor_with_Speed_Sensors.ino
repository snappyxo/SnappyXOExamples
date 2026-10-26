// Shape-Drawing Encoder Bot: this project aims to create a dual-motor driven
// wheeled robot that uses the encoders to gauge the robot's distance, allowing
// shape paths to be defined.
//
// Developed by A+ Mobile Solutions Inc
// Licensed under the MIT License. See LICENSE for details.
#include <SnappyXOShield.h>

SnappyXOShield shield(SnappyXOShield::V3);  // the shield version printed on the board: V3 or V2

// Pin Definitions
const int rightEncoder = 2;  // the right wheel, seen from behind the robot
const int leftEncoder = 3;

// For Tachometer
float pulsePerRev = 15.0;
float R_wheel = 3.0;  // [cm]
float R_car = 16.0;	  // [cm]
float cmPerPulse = 2.0 * PI * R_wheel / (4.0 * pulsePerRev);

// Pulses counted by the encoders. volatile, because the interrupt functions
// below change them while the rest of the sketch is running.
volatile unsigned long rightPulses = 0;
volatile unsigned long leftPulses = 0;
volatile unsigned long lastRightPulseAt = 0;  // micros() of the last pulse counted
volatile unsigned long lastLeftPulseAt = 0;

// Pulses closer together than this (in microseconds) are the sensor
// flickering at the edge of a slot, not a new slot
const unsigned long DEBOUNCE_US = 1000;

// For Motor
int LPWM = 185;
int RPWM = 155;

// Other parameters
bool is_Running = 1;
float slipFactor = 1.075;

// Interrupt functions: they run every time an encoder pulses, so they must be
// quick. No delay() or Serial in here.
void rightPulseAdd() {
	unsigned long now = micros();
	if (now - lastRightPulseAt >= DEBOUNCE_US) {
		rightPulses++;
		lastRightPulseAt = now;
	}
}

void leftPulseAdd() {
	unsigned long now = micros();
	if (now - lastLeftPulseAt >= DEBOUNCE_US) {
		leftPulses++;
		lastLeftPulseAt = now;
	}
}

// How far the left wheel has gone, in cm. Interrupts are paused while the
// count is copied, so it can't change halfway through being read.
float leftDistance() {
	noInterrupts();
	unsigned long pulses = leftPulses;
	interrupts();
	return pulses * cmPerPulse;
}

void resetDistance() {
	noInterrupts();
	leftPulses = 0;
	rightPulses = 0;
	interrupts();
}

// Path Actions

void stopBot() {  // This function sets all motors to off
	shield.stop();
}

void goForward(float distance) {  // This function moves the robot "distance" cm
	resetDistance();
	shield.setMotors(LPWM, RPWM);
	while (leftDistance() < distance) {
		// keep driving until the left wheel has gone far enough
	}
	Serial.print("Forward ");
	Serial.print(leftDistance());
	Serial.println(" cm");
}

void turnRightDegrees(float angle) {  // This function turns the robot right
									  // "angle" degrees
	// Only the left wheel drives, so the robot pivots on its right wheel
	float angleInRad = slipFactor * angle * (PI / 180.0);
	float dis = angleInRad * R_car;

	resetDistance();
	shield.setMotors(LPWM, 0);
	while (leftDistance() < dis) {
		// keep turning until the left wheel has gone far enough
	}
	Serial.print("Turned ");
	Serial.print(angle);
	Serial.println(" degrees");
}

void square(float sideLength,
			int delayTime) {  // This function causes the robot to drive in the
							  // shape of a square
	for (int ii = 0; ii < 4; ii++) {  // with sides of length "sideLength" (cm)
									  // and with delays of "delayTime" (ms)
		goForward(sideLength);
		stopBot();
		delay(delayTime);
		turnRightDegrees(90);
		stopBot();
		delay(delayTime);
	}
}

void triangle(float sideLength,
			  int delayTime) {	// This function causes the robot to drive in
								// the shape of a triangle
	for (int ii = 0; ii < 3; ii++) {  // with sides of length "sideLength" and
									  // with delays of "delayTime"
		goForward(sideLength);
		stopBot();
		delay(delayTime);
		turnRightDegrees(120);
		stopBot();
		delay(delayTime);
	}
}

void polygon(float sideLength, int delayTime,
			 int numOfSides) {	// This function causes the robot to drive in
								// the shape of a polygon
	for (int ii = 0; ii < numOfSides;
		 ii++) {  // with sides of length "sideLength", with delays of
				  // "delayTime" and
		goForward(
			sideLength);  // with a given number of sides called "numOfSides"
		stopBot();
		delay(delayTime);
		turnRightDegrees(360.0 / numOfSides);
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
	shield.begin();
	// This robot's left motor runs backward unless it's reversed here
	shield.invertLeft();

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
