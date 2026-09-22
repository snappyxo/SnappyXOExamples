// This project aims to educate the user on how to control a differential drive
// robot with two motors and LEDs using a bluetooth module and the MicroBlue
// app.
#include <MicroBlue.h>
#include <SnappyXOShield.h>
MicroBlueManager manager;

const int PIN_LED_RED = 10;
const int PIN_LED_GREEN = 11;
const int PIN_LED_BLUE = 12;

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

void setup() {
	pinMode(PIN_LED_GREEN, OUTPUT);
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_LED_BLUE, OUTPUT);
	initMotors();
	manager.begin("My BLE Module");
}

void loop() {
	MicroBlueMessage msg = manager.read();

	if (msg.id == "d0" || msg.id == "d1") {
		int throttle, steering;
		sscanf(msg.value.c_str(), "%d,%d", &steering, &throttle);
		throttle -= 512;
		steering -= 512;
		drive(throttle, steering);
	}
}
