// This project uses the photoresistor to steer a car in the direction of
// greatest light.
//
// Developed by A+ Mobile Solutions Inc
// Licensed under the MIT License. See LICENSE for details.
#include <SnappyXOShield.h>

SnappyXOShield shield(SnappyXOShield::V3);  // the shield version printed on the board: V3 or V2

// Pin Definitions
int photoLeft = A1;
int photoRight = A0;

// Parameter Initialization
float V_Left;
float initalLeftVal;
float V_Right;
float initalRightVal;
float lightDifference;
float minLightDiff = 2;

void setup() {
	// Define pinModes
	pinMode(photoLeft, INPUT);
	pinMode(photoRight, INPUT);

	// Begin serial communication
	Serial.begin(9600);

	// Inital motor settings
	shield.begin();
	shield.invertRight();
}

void loop() {
	// put your main code here, to run repeatedly:
	V_Left = analogRead(photoLeft);
	V_Right = analogRead(photoRight);
	lightDifference = abs(V_Left - V_Right);

	Serial.print(V_Left);
	Serial.print(",");
	Serial.println(V_Right);

	if (V_Left > V_Right && lightDifference > minLightDiff) {
		shield.spinLeft();
	} else if (V_Left < V_Right && lightDifference > minLightDiff) {
		shield.spinRight();
	} else {
		shield.forward();
	}
}
