// This project aims to educate the user on how two photocells and two servos
// can automatically launch a foam ball Include Libraries
#include <Servo.h>

// Pin Definitions
int servo1Pin = A2;
int servo2Pin = A3;
int redRGBPin = 3;
int greenRGBPin = 5;
int blueRGBPin = 6;
int ambientPhotoPin = A1;
int trigPhotoPin = A0;

// Initialize Objects
Servo servo1;
Servo servo2;

// Parameter Initialization
int angle1 = 0;
int angle2 = 5;
double a = 1;
double b = 1;
int ambientLight;
int lightVal;
int a1Light;
int b1Light;
int a2Light;
int b2Light;

void setup() {
	// Declare pinModes
	pinMode(redRGBPin, OUTPUT);	   // red
	pinMode(greenRGBPin, OUTPUT);  // green
	pinMode(blueRGBPin, OUTPUT);   // blue

	// Begin serial communication
	Serial.begin(9600);

	// Attach servo pins and set inital angles
	servo1.attach(servo1Pin);
	servo2.attach(servo2Pin);
	servo1.write(angle1);
	servo2.write(angle2);

	// Perform a calibration function
	Calibrate();
}

void loop() {
	// standby (green light)
	analogWrite(greenRGBPin, 255);
	analogWrite(redRGBPin, 0);
	analogWrite(blueRGBPin, 0);

	// photocell measurements
	ambientLight = analogRead(ambientPhotoPin) / a;
	lightVal = analogRead(trigPhotoPin) / b;

	// Serial.print("Light");
	// Serial.println(lightVal);
	// Serial.print("Ambient");
	// Serial.println(ambientLight);

	// Serial.println(a);
	// Serial.println(b);

	a1Light = analogRead(ambientPhotoPin);
	b1Light = analogRead(trigPhotoPin);
	delay(50);
	a2Light = analogRead(ambientPhotoPin);
	b2Light = analogRead(trigPhotoPin);

	// if both sensors detect a similar change at the same time, then the
	// environment must have changed, so we recalibrate for it
	if (abs(a1Light - a2Light) > 5 && abs(b1Light - b2Light) > 5) {
		Calibrate();
		Calibrate();

		// calibrates twice for redundancy
	}

	if (lightVal < (ambientLight / 1.3)) {
		// ball detected
		analogWrite(redRGBPin, 110);
		analogWrite(blueRGBPin, 0);
		analogWrite(greenRGBPin, 255);
		delay(1000);

		// recheck sensors to determine if ball is still in place
		int ambientLight1 = analogRead(ambientPhotoPin) / a;
		int lightVal1 = analogRead(trigPhotoPin) / b;

		if (lightVal1 < (ambientLight1 / 1.3)) {
			Launch();
			delay(500);
			Calibrate();
		}
	}
}

void Calibrate() {
	double ambientLight_a = analogRead(ambientPhotoPin);
	double lightVal_a = analogRead(trigPhotoPin);

	// calibration script

	if (lightVal_a < ambientLight_a) {
		b = 1;
		a = ambientLight_a / lightVal_a;
		if (a > 5) {
			a = 5;
		}
	}
	if (ambientLight_a < lightVal_a) {
		a = 1;
		b = lightVal_a / ambientLight_a;
		if (b > 5) {
			b = 5;
		}
	}
	// Serial.println("Calibrated");
}

void Launch() {
	analogWrite(redRGBPin, 255);
	analogWrite(greenRGBPin, 0);
	analogWrite(blueRGBPin, 0);

	delay(500);
	servo1.write(180);
	delay(1000);
	servo2.write(80);

	// resetting
	delay(500);

	analogWrite(redRGBPin, 0);
	analogWrite(greenRGBPin, 0);
	analogWrite(blueRGBPin, 255);

	delay(200);
	servo1.write(0);
	delay(1000);
	servo2.write(5);
}