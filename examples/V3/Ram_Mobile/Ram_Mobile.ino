// This project aims to educate the user on how to control a 2WD car using IR as
// well as operating a passive ball dropping mechanism.
//
// Developed by A+ Mobile Solutions Inc
// Licensed under the MIT License. See LICENSE for details.

// Include libraries
#include <IRremote.hpp>
#include <SnappyXOShield.h>

SnappyXOShield shield(SnappyXOShield::V3);  // the shield version printed on the board: V3 or V2

void setup() {
	delay(500);

	// Begin serial communication with computer.
	Serial.begin(9600);

	shield.begin();
	// This robot's left motor runs backward unless it's reversed here
	shield.invertLeft();

	// initialize ir receiver pin
	IrReceiver.begin(2, DISABLE_LED_FEEDBACK);

	// print available protocols
	Serial.print(F("Ready to receive IR signals of protocols: "));
	printActiveIRProtocols(&Serial);
	Serial.println("SETUP COMPLETE");
}

// Configures the motor controller to stop the motors.
void Brake() {
	Serial.println("Stop");
	shield.stop();
}

// Configures the motor controller to have the robot move forward.
void Forward() {
	Serial.println("Forward");
	shield.forward();
	delay(150);
	shield.stop();
}

// Configures the motor controller to have the robot move backwards.
void Reverse() {
	Serial.println("Reverse");
	shield.reverse();
	delay(150);
	shield.stop();
}

/* TURN RIGHT */
void Right() {
	Serial.println("Right");
	shield.spinRight();
	delay(150);
	shield.stop();
}

/* TURN LEFT */
void Left() {
	Serial.println("Left");
	shield.spinLeft();
	delay(150);
	shield.stop();
}

// Main loop which detects users inputs and responds based on which button is
// pressed on the IR remote.
void loop() {
	// Decodes Infrared Signal from Remote
	if (IrReceiver.decode()) {
		// Enable receiving of the next value
		IrReceiver.resume();
		Serial.println(IrReceiver.decodedIRData.command);

		// check for which button was pressed on IR Remote and execute relevant
		// functions
		if (IrReceiver.decodedIRData.command == 0x45) {
			Serial.println(1);
		} else if (IrReceiver.decodedIRData.command == 0x46) {
			Serial.println(2);

		} else if (IrReceiver.decodedIRData.command == 0x47) {
			Serial.println(3);

		} else if (IrReceiver.decodedIRData.command == 0x44) {
			Serial.println(4);

		} else if (IrReceiver.decodedIRData.command == 0x18) {
			Serial.println("Forward");
			Forward();

		} else if (IrReceiver.decodedIRData.command == 0x52) {
			Serial.println("Reverse");
			Reverse();
		} else if (IrReceiver.decodedIRData.command == 0x8) {
			Serial.println("Left");
			Left();
		} else if (IrReceiver.decodedIRData.command == 0x5A) {
			Serial.println("Right");
			Right();
		} else if (IrReceiver.decodedIRData.command == 0x1C) {
			Serial.println("OK");
			Brake();
		}
	}
}
