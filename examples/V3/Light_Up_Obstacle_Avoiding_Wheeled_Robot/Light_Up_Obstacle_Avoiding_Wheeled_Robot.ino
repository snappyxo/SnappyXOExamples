// This code allows the 2WD DC motor car to avoid obstacles using an Ultrsonic
// sensor and lights up an LED that changes color based on the direction that
// the car is moving
#include <SnappyXOShield.h>

// Pin Definitions
int PIN_LED_RED = 10;
int PIN_LED_BLUE = 11;
int PIN_LED_GREEN = 2;
int trig = 13;	// attach pin 7 to Trig
int echo = 12;	// attach pin 8 to Echo

// Parameter Initializations
long duration, inches, cm;
int randint;

void setup() {
	initMotors();

	// Declare pinModes
	pinMode(PIN_LED_GREEN, OUTPUT);
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_LED_BLUE, OUTPUT);
	pinMode(echo, INPUT);
	pinMode(trig, OUTPUT);

	// Begin serial communication:
	Serial.begin(9600);

	// Initial motor and LED settings
	digitalWrite(PIN_LED_RED, LOW);
	digitalWrite(PIN_LED_GREEN, LOW);
	digitalWrite(PIN_LED_BLUE, LOW);
}

void loop() {
	// Ultrasonic protocol
	digitalWrite(trig, LOW);
	delayMicroseconds(2);
	digitalWrite(trig, HIGH);
	delayMicroseconds(10);
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

	// Commands robot to drive forward and lights up the LED to be green
	forward();
	green();
	randint = random(0, 2);	 // // randomly choose whether to turn left or right
							 // if an obstacle is encountered; in this code, 0
							 // is turning right and 1 is turning left

	// When robot becomes to close to the obstacle; Robot will reverse, turn
	// right, then continue forward
	if (inches < 7 && randint == 0) {
		reverse();
		red();	// turns led to be red
		delay(500);
		pause();
		red();
		delay(500);
		turnRight();
		blue();
		delay(300);
		forward();
		green();
	}

	// When robot becomes to close to the obstacle; Robot will reverse, turn
	// left, then continue forward
	if (inches < 7 && randint == 1) {
		reverse();
		red();	// turns led to be red
		delay(500);
		pause();
		red();
		delay(500);
		turnLeft();
		blue();
		delay(300);
		forward();
		green();
	}
}

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
