// This project aims to educate the user on how to use the UNO R4 WiFi's
// built-in Bluetooth to control a 2WD car and toggle a 4 bar linkage that
// performs a lifting motion.
//
// Developed by A+ Mobile Solutions Inc
// Licensed under the MIT License. See LICENSE for details.
#include <MicroBlue.h>
#include <Servo.h>
#include <SnappyXOShield.h>

MicroBlueManager manager;                   // talks to the MicroBlue app
SnappyXOShield shield(SnappyXOShield::V3);  // the shield version printed on the board: V3 or V2

Servo arm;

void setup() {
	shield.begin();
	shield.setTurnSpeed(60);  // how hard the robot turns, 0-100 percent: lower makes steering gentler
	arm.attach(A2);
	manager.begin("My BLE Module");
}

void loop() {
	if (manager.isConnected()) {
		MicroBlueMessage msg = manager.read();

		// The Drive screen's D-Pad, Joystick and Tilt send "x,y", each 0-1023:
		// 1023 is right or forward, 0 is left or back, 512,512 is the center
		if (msg.id == "d0" || msg.id == "d1") {
			int x, y;
			if (sscanf(msg.value.c_str(), "%d,%d", &x, &y) == 2) {
				int throttle = map(y, 0, 1023, -255, 255);  // forward and back
				int steering = map(x, 0, 1023, -255, 255);  // left and right
				shield.drive(throttle, steering);
			}
		} else if (msg.id == "b0") {
			// The button sends 1 when pressed and 0 when let go: the arm lifts
			// while it's held
			if (msg.value == "1") {
				arm.write(180);
			} else if (msg.value == "0") {
				arm.write(0);
			}
		}
	}

	// Stop when the phone disconnects or the app's heartbeat stops (phone out
	// of range, app closed or in the background)
	if (!manager.isConnected() || manager.heartbeatLost()) {
		shield.stop();
	}
}
