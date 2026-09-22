// This project aims to educate the user on how two servos can pick up and move
// a foam ball Include Libraries
#include <Servo.h>
#include <SnappyXOShield.h>

#include <IRremote.hpp>

// Pin Definitions
int IRPin = 2;
int servo1Pin = A0;
int servo2Pin = A1;

// Initialize Objects
Servo servo1;
Servo servo2;

// Parameter Initialization
int angle1 = 180;
int angle = 0;
int motorDelay = 70;

void setup() {
	initMotors();

	// Begin serial communications and IR Reception
	Serial.begin(9600);
	IrReceiver.begin(IRPin, DISABLE_LED_FEEDBACK);

	// Attach servo pins
	servo1.attach(servo1Pin);
	servo2.attach(servo2Pin);

	// Initialize motor speeds
	forward();
	servo1.write(angle);
	servo2.write(angle1);
}

void loop() {
	if (IrReceiver.decode()) {
		IrReceiver.start();

		if (IrReceiver.decodedIRData.command == 0x45) {
			servoUp();
			// 1
		}

		else if (IrReceiver.decodedIRData.command == 0x47) {
			// 3
			servoOpen();
		} else if (IrReceiver.decodedIRData.command == 0x44) {
			// 4
			servoDown();
		}

		else if (IrReceiver.decodedIRData.command == 0x43) {
			// 6
			servoClose();
		}

		else if (IrReceiver.decodedIRData.command == 0x19) {
			angle = 0;
			servo1.write(angle);
			angle1 = 180;
			servo2.write(angle1);

		}

		else if (IrReceiver.decodedIRData.command == 0x18) {
			motorSetForward();

		} else if (IrReceiver.decodedIRData.command == 0x52) {
			motorSetBackward();

		} else if (IrReceiver.decodedIRData.command == 0x8) {
			TurnLeft();

		} else if (IrReceiver.decodedIRData.command == 0x5A) {
			TurnRight();
		}
	}
}

void motorSetForward() {
	Serial.println("Forward");
	forward();
	delay(motorDelay);
	pause();

	// Do not write the motor speeds on this function. It simply configures the
	// motor controller.
}

void motorSetBackward() {
	Serial.println("Reverse");
	reverse();
	delay(motorDelay);
	pause();
	// Do not write the motor speeds on this function. It simply configures the
	// motor controller.
}

void TurnLeft() {
	Serial.println("Left");
	turnLeft();
	delay(motorDelay);
	pause();
}

void TurnRight() {
	Serial.println("Right");
	turnRight();
	delay(motorDelay);
	pause();
}

void servoUp() {
	angle = angle;
	angle = angle + 3;
	servo1.write(angle);
	Serial.println(angle);
	delay(20);
	if (angle > 100) {
		angle = 100;
	}
}

void servoDown() {
	angle = angle;
	angle = angle - 3;
	servo1.write(angle);
	Serial.println(angle);
	delay(20);

	if (angle < 0) {
		angle = 0;
	}
}

void servoClose() {
	angle1 = angle1;
	angle1 = angle1 - 3;
	servo2.write(angle1);
	Serial.println(angle1);
	delay(20);

	if (angle1 < 100) {
		angle1 = 100;
	}
}

void servoOpen() {
	angle1 = angle1;
	angle1 = angle1 + 3;
	servo2.write(angle1);
	Serial.println(angle1);
	delay(20);

	if (angle1 > 180) {
		angle1 = 180;
	}
}
