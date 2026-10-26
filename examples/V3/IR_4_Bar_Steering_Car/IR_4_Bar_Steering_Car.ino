// This code controls a car with a steering mechanism via IR Remote. You can
// control the speed and steer angle of the car.
//
// Developed by A+ Mobile Solutions Inc
// Licensed under the MIT License. See LICENSE for details.

// Include libraries
#include <IRremote.hpp>
#include <Servo.h>
#include <SnappyXOShield.h>

SnappyXOShield shield(SnappyXOShield::V3);  // the shield version printed on the board: V3 or V2

// Initialize objects
Servo myServo;

// Pin Definitions
int servoPin = A0;
int IRpin = 10;

// Parameter Initalizations
float motorSpeed;
int motorDir = 0;

void setup() {
	// Define pinModes
	pinMode(servoPin, OUTPUT);
	pinMode(IRpin, INPUT);
	shield.begin();
	// If a wheel turns backward when it should go forward, uncomment its line:
	// shield.invertLeft();   // left wheel
	// shield.invertRight();  // right wheel

	// Set inital motor speed
	motorSpeed = .75;

	// Attach servo to pin and begin communications
	IrReceiver.begin(IRpin, DISABLE_LED_FEEDBACK);
	myServo.attach(servoPin);
	Serial.begin(9600);

	// Protocol to find the correct decoder for your remote
	Serial.print(F("Ready to receive IR signals of protocols: "));
	printActiveIRProtocols(&Serial);
	Serial.println("SETUP COMPLETE");
}

void loop() {
	// Decodes Infrared Signal from Remote
	if (IrReceiver.decode()) {
		// Enable receiving of the next value
		IrReceiver.resume();
		Serial.println(IrReceiver.decodedIRData.command);

		if (IrReceiver.decodedIRData.command == 0x18) {
			Serial.println("Forward");
			motorDir = 1;
			shield.forward((int)(255 * motorSpeed));
			myServo.write(90);
		} else if (IrReceiver.decodedIRData.command == 0x52) {
			Serial.println("Backward");
			motorDir = -1;
			shield.reverse((int)(255 * motorSpeed));
			myServo.write(90);
		} else if (IrReceiver.decodedIRData.command == 0x8) {
			Serial.println("Left");
			myServo.write(105);
		} else if (IrReceiver.decodedIRData.command == 0x5A) {
			Serial.println("Right");
			myServo.write(75);
		}
		//        else if (IrReceiver.decodedIRData.command == 0x19) {
		//            Serial.println("Forward");
		//            myServo.write(90);
		//        }
		else if (IrReceiver.decodedIRData.command == 0x1C) {
			Serial.println("Stop");
			motorDir = 0;
			shield.stop();
		} else if (IrReceiver.decodedIRData.command == 0x45) {
			Serial.println("Motor Speed: 1");
			motorSpeed = 0.5;
			if (motorDir == 1)
				shield.forward((int)(255 * motorSpeed));
			else if (motorDir == -1)
				shield.reverse((int)(255 * motorSpeed));
		} else if (IrReceiver.decodedIRData.command == 0x46) {
			Serial.println("Motor Speed: 2");
			motorSpeed = 0.75;
			if (motorDir == 1)
				shield.forward((int)(255 * motorSpeed));
			else if (motorDir == -1)
				shield.reverse((int)(255 * motorSpeed));
		} else if (IrReceiver.decodedIRData.command == 0x47) {
			Serial.println("Motor Speed: 3");
			motorSpeed = 1.0;
			if (motorDir == 1)
				shield.forward((int)(255 * motorSpeed));
			else if (motorDir == -1)
				shield.reverse((int)(255 * motorSpeed));
		}
	}
}
