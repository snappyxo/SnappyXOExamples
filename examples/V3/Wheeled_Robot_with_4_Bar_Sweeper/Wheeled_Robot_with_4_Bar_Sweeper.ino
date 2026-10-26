// This project aims to educate the user on how to control a differential drive
// robot with two DC motors and induce a sweeping motion with a 4 bar mechanism
// and finite servo.
//
// Developed by A+ Mobile Solutions Inc
// Licensed under the MIT License. See LICENSE for details.
#include <MicroBlue.h>
#include <Servo.h>
#include <SnappyXOShield.h>

MicroBlueManager manager;                   // talks to the MicroBlue app
SnappyXOShield shield(SnappyXOShield::V3);  // the shield version printed on the board: V3 or V2

Servo arm;

// A sweep moves the arm out, then back after a second. It's timed with
// millis() instead of delay(), so the robot keeps listening to the app (and
// can stop) while the arm moves.
bool sweeping = false;
unsigned long sweepStartedAt = 0;

void setup() {
	shield.begin();
	shield.setTurnSpeed(60);  // how hard the robot turns, 0-100 percent: lower makes steering gentler
	arm.attach(A0);
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
		} else if (msg.id == "b0" && msg.value == "1" && !sweeping) {
			// Button pressed: start a sweep
			arm.write(180);
			sweeping = true;
			sweepStartedAt = millis();
		}
	}

	if (sweeping) {
		unsigned long elapsed = millis() - sweepStartedAt;
		if (elapsed >= 2000) {
			sweeping = false;  // the arm is back: ready for the next sweep
		} else if (elapsed >= 1000) {
			arm.write(0);  // sweep back
		}
	}

	// Stop when the phone disconnects or the app's heartbeat stops (phone out
	// of range, app closed or in the background)
	if (!manager.isConnected() || manager.heartbeatLost()) {
		shield.stop();
	}
}
