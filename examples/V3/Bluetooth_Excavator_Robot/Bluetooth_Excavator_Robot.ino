// This project aims to educate the user on how to control a 2WD car using
// bluetooth as well as an excavator mechanism using finite servos.
#include <MicroBlue.h>
#include <Servo.h>
#include <SnappyXOShield.h>

MicroBlueManager manager;                   // talks to the MicroBlue app
SnappyXOShield shield(SnappyXOShield::V3);  // the shield version printed on the board: V3 or V2

Servo arm;
Servo sweeper;

int armpos = 0;
int angle;

void setup() {
	shield.begin();
	shield.setTurnSpeed(60);  // how hard the robot turns, 0-100 percent: lower makes steering gentler
	arm.attach(A0);
	sweeper.attach(A1);
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
		} else if (msg.id == "sl0") {
			armpos = map(msg.value.toInt(), 0, 180, 0, 100);
			arm.write(armpos);
		} else if (msg.id == "sl1") {
			angle = map(msg.value.toInt(), 0, 180, 0, 100);
			sweeper.write(angle);
		}
	}

	// Stop when the phone disconnects or the app's heartbeat stops (phone out
	// of range, app closed or in the background)
	if (!manager.isConnected() || manager.heartbeatLost()) {
		shield.stop();
	}
}
