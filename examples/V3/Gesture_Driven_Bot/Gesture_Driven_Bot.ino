// This project aims to educate the user on how an ultrasonic sensor can detect
// different heights to drive a robot foward and backward
#include <SnappyXOShield.h>

// Pin Declarations

int trig = 13;	// attach pin 7 to Trig
int echo = 12;	// attach pin 8 to Echo

void setup() {
	// initialize serial communication:
	Serial.begin(9600);

	// invertR=true matches original forward direction (InputOne HIGH, InputTwo
	// LOW)
	initMotors(false, true, false);
	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);
}

void loop() {
	long duration, inches, cm;

	// send a short LOW pulse first
	digitalWrite(trig, LOW);
	delayMicroseconds(2);

	// send a 5 microsecond HIGH pulse, specified by datasheet
	digitalWrite(trig, HIGH);
	delayMicroseconds(10);

	// end high pulse
	digitalWrite(trig, LOW);

	// now set the pingPin to the input mode and listens for echo, records in
	// microseconds

	duration = pulseIn(echo, HIGH, 38000);

	// convert the time into a distance
	inches = microsecondsToInches(duration);
	cm = microsecondsToCentimeters(duration);
	if (cm != 0) {
		Serial.print(inches);
		Serial.print("in, ");
		Serial.print(cm);
		Serial.print("cm");
		Serial.println();

		// Commands robot

		if (cm < 15) {
			Serial.println("Reverse");
			reverse();
		}

		else if (cm < 30 && cm > 16) {
			Serial.println("Forward.");
			forward();
		}

		else {
			Serial.println("Pause");
			pause();
		}
	}
}

long microsecondsToInches(long microseconds) {
	// According to Parallax's datasheet for the PING))), there are
	// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
	// second). This gives the distance travelled by the ping, outbound
	// and return, so we divide by 2 to get the distance of the obstacle.
	// See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
	return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
	// The speed of sound is 340 m/s or 29 microseconds per centimeter.
	// The ping travels out and back, so to find the distance of the
	// object we take half of the distance travelled.
	return microseconds / 29 / 2;
}
