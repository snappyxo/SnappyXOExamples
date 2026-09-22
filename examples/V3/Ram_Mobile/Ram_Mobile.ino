// This project aims to educate the user on how to control a 2WD car using IR as
// well as operating a passive ball dropping mechanism. Include libraries
#include <IRremote.h>
#include <SnappyXOShield.h>

void setup() {
	delay(500);

	// Begin serial communication with computer.
	Serial.begin(9600);

	// Initialize motors (left inverted to match original forward direction)
	initMotors(true, false);

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
	pause();
}

// Configures the motor controller to have the robot move forward.
void Forward() {
	Serial.println("Forward");
	forward();
	delay(150);
	pause();
}

// Configures the motor controller to have the robot move backwards.
void Reverse() {
	Serial.println("Reverse");
	reverse();
	delay(150);
	pause();
}

/* TURN RIGHT */
void Right() {
	Serial.println("Left");
	turnRight();
	delay(150);
	pause();
}

/* TURN LEFT */
void Left() {
	Serial.println("Turn Right");
	turnLeft();
	delay(150);
	pause();
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
