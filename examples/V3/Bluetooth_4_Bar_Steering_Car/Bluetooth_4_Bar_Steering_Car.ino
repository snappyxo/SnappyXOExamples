// This code controls a car with a steering mechanism via bluetooth. You can
// control the speed and steer angle of the car.
#include <MicroBlue.h>
#include <Servo.h>
#include <SnappyXOShield.h>

MicroBlueManager manager;                   // talks to the MicroBlue app
SnappyXOShield shield(SnappyXOShield::V3);  // the shield version printed on the board: V3 or V2

int servoPin = A0;
Servo myServo;

void setup() {
	shield.begin();
	// This car's left motor runs backward unless it's reversed here
	shield.invertLeft();
	myServo.attach(servoPin);
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

				// Below speed 127 the motors barely move the car, so any push on
				// the stick starts at 127 and goes up to full speed. Small
				// movements near the center count as stop.
				int speed = map(abs(throttle), 0, 255, 127, 255);
				if (throttle > 10) {
					shield.forward(speed);
				} else if (throttle < -10) {
					shield.reverse(speed);
				} else {
					shield.stop();
				}

				// The steering servo turns from 120 (full left) to 75 (full right)
				myServo.write(map(steering, -255, 255, 120, 75));
			}
		}
	}

	// Stop when the phone disconnects or the app's heartbeat stops (phone out
	// of range, app closed or in the background)
	if (!manager.isConnected() || manager.heartbeatLost()) {
		shield.stop();
	}
}
