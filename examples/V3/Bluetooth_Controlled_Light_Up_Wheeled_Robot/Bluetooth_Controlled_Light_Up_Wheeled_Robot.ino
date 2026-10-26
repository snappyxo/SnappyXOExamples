// This project aims to educate the user on how to control a differential drive
// robot with two motors and LEDs using the UNO R4 WiFi's built-in Bluetooth
// and the MicroBlue app. The LED shows what the robot is doing: green driving
// forward, red stopped or backward, blue spinning in place, and blinking red
// while the phone isn't connected.
//
// Developed by A+ Mobile Solutions Inc
// Licensed under the MIT License. See LICENSE for details.
#include <MicroBlue.h>
#include <SnappyXOShield.h>

MicroBlueManager manager;                   // talks to the MicroBlue app
SnappyXOShield shield(SnappyXOShield::V3);  // the shield version printed on the board: V3 or V2

const int PIN_LED_RED = 10;
const int PIN_LED_GREEN = 11;
const int PIN_LED_BLUE = 12;

// The last throttle and steering from the app, which the LED shows
int throttle = 0;
int steering = 0;

void red() {
	digitalWrite(PIN_LED_RED, HIGH);
	digitalWrite(PIN_LED_BLUE, LOW);
	digitalWrite(PIN_LED_GREEN, LOW);
}

void blue() {
	digitalWrite(PIN_LED_RED, LOW);
	digitalWrite(PIN_LED_BLUE, HIGH);
	digitalWrite(PIN_LED_GREEN, LOW);
}

void green() {
	digitalWrite(PIN_LED_RED, LOW);
	digitalWrite(PIN_LED_BLUE, LOW);
	digitalWrite(PIN_LED_GREEN, HIGH);
}

void off() {
	digitalWrite(PIN_LED_RED, LOW);
	digitalWrite(PIN_LED_BLUE, LOW);
	digitalWrite(PIN_LED_GREEN, LOW);
}

// Shows how the robot is driving. Values under 10 count as 0, as they do in
// shield.drive(), so a thumb resting near the joystick's center shows stopped.
void showDriving() {
	if (throttle >= 10) {
		green();  // forward
	} else if (throttle <= -10) {
		red();  // backward
	} else if (abs(steering) >= 10) {
		blue();  // spinning in place
	} else {
		red();  // stopped
	}
}

void setup() {
	pinMode(PIN_LED_GREEN, OUTPUT);
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_LED_BLUE, OUTPUT);
	shield.begin();
	shield.setTurnSpeed(60);  // how hard the robot turns, 0-100 percent: lower makes steering gentler
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
				throttle = map(y, 0, 1023, -255, 255);  // forward and back
				steering = map(x, 0, 1023, -255, 255);  // left and right
				shield.drive(throttle, steering);
			}
		}
	}

	// Stop when the phone disconnects or the app's heartbeat stops (phone out
	// of range, app closed or in the background), and blink red until the app
	// is back
	if (!manager.isConnected() || manager.heartbeatLost()) {
		shield.stop();
		throttle = 0;
		steering = 0;
		if ((millis() / 250) % 2 == 0) {
			red();
		} else {
			off();
		}
	} else {
		showDriving();
	}
}
