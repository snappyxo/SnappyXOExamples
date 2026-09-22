// This code controls a car with a steering mechanism via bluetooth. You can
// control the speed and steer angle of the car.
#include <MicroBlue.h>
#include <Servo.h>
#include <SnappyXOShield.h>
MicroBlueManager manager;

int servoPin = A0;
Servo myServo;

void setup() {
	// Original forward was IN1(4)=HIGH, IN2(5)=LOW.
	// Library forward sets InputOne(4)=LOW, InputTwo(7)=HIGH — opposite on the
	// shared pin 4, so invert the left motor so logical "forward" matches
	// original behaviour.
	initMotors(/*invertL=*/true, /*invertR=*/false);
	myServo.attach(servoPin);
	manager.begin("My BLE Module");
}

void loop() {
	MicroBlueMessage msg = manager.read();

	if (msg.id == "d0" || msg.id == "d1") {
		int steerRaw, throttleRaw;
		sscanf(msg.value.c_str(), "%d,%d", &steerRaw, &throttleRaw);
		int throttle = throttleRaw - 512;
		int steering = steerRaw - 512;

		int mappedThrottle = map(abs(throttle), 0, 512, 127, 255);
		int mappedSteer = map(steering, -512, 512, 120, 75);

		if (throttle > 0)
			forward(mappedThrottle);
		else if (throttle == 0)
			pause();
		else
			reverse(mappedThrottle);

		myServo.write(mappedSteer);
	}
}
