// This project aims to educate the user on how connect an Ultrasonic sensor and
// demonstrate how this sensor can help a 2WD car avoid obstacles.
#include <SnappyXOShield.h>

// Pin Definitions
int trig = 13;
int echo = 12;

// Parameter Initialization
long duration, inches, cm;
int randint;

void setup() {
	initMotors();

	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);

	// Begin serial communication:
	Serial.begin(9600);
}

void loop() {
	// Ultrasonic Sensor protocol
	digitalWrite(trig, LOW);
	delayMicroseconds(2);
	digitalWrite(trig, HIGH);
	delayMicroseconds(5);
	digitalWrite(trig, LOW);

	duration = pulseIn(echo, HIGH);

	// convert the time into a distance
	inches = microsecondsToInches(duration);
	cm = microsecondsToCentimeters(duration);

	Serial.print(inches);
	Serial.print("in, ");
	Serial.print(cm);
	Serial.print("cm");
	Serial.println();
	delay(10);

	// Commands robot to drive forward
	forward();

	// randomly choose whether to turn left or right if an obstacle is
	// encountered; in this case, 0 is turning right and 1 is turning left
	randint = random(0, 2);

	// When robot becomes to close to the obstacle; Robot will reverse, turn
	// right, then continue forward
	if (inches < 7 && randint == 0) {
		reverse();
		delay(500);
		pause();
		delay(500);
		turnRight();
		delay(200);
		forward();
	}

	// When robot becomes to close to the obstacle; Robot will reverse, turn
	// left, then continue forward
	if (inches < 7 && randint == 1) {
		reverse();
		delay(500);
		pause();
		delay(500);
		turnLeft();
		delay(200);
		forward();
	}
}

long microsecondsToInches(long microseconds) {
	// There are 73.746 microseconds per inch (i.e. sound travels at 1130 feet
	// per second). This gives the distance travelled by the ping, outbound and
	// return, so we divide by 2 to get the distance of the obstacle.
	return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
	// The speed of sound is 340 m/s or 29 microseconds per centimeter.
	// The ping travels out and back, so to find the distance of the
	// object we take half of the distance travelled.
	return microseconds / 29 / 2;
}
