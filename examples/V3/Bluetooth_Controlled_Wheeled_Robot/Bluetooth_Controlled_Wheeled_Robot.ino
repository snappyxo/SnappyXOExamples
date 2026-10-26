// This project aims to educate the user on how to control a differential drive
// robot with two motors using the UNO R4 WiFi's built-in Bluetooth and the
// MicroBlue app.
#include <MicroBlue.h>
#include <SnappyXOShield.h>

MicroBlueManager manager;                   // talks to the MicroBlue app
SnappyXOShield shield(SnappyXOShield::V3);  // the shield version printed on the board: V3 or V2

void setup() {
	shield.begin();
	shield.setTurnSpeed(60);  // how hard the robot turns, 0-100 percent: lower makes steering gentler
	manager.begin("My BLE Module");
	Serial.begin(9600);
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

				Serial.print("throttle ");
				Serial.print(throttle);
				Serial.print(", steering ");
				Serial.println(steering);
			}
		}
	}

	// Stop when the phone disconnects or the app's heartbeat stops (phone out
	// of range, app closed or in the background)
	if (!manager.isConnected() || manager.heartbeatLost()) {
		shield.stop();
	}
}
