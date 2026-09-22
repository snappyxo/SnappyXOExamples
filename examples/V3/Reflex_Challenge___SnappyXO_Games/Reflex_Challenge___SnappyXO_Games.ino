// This code aims to educate the user on how to use various sensors through an
// interactive game. User inputs affect the readings of each sensor and push the
// user to test their reaction time. Pin Definitions
int buzzerPin = 6;
int photoLEDPin = 7;
int switchLEDPin = 8;
int potLEDPin = 9;
int buttonLEDPin = 10;
int switchPin = 11;
int potPin = 12;
int buttonPin = 13;
int photoPin = A2;

// Parameter Definitions
String buttonState;
String twistItState;
String slideItState;
String pinchItState;
float Voltage_mv;
float Voltage_ambient;
float Voltage_pinch;
float initalPinch;
float Calibration;
float timestart = millis();
float timeend = timeend;
float Time = 2000;
bool lost = false;
int randomVar;
int ii = 0;
int Score;

void setup() {
	// Declare pinModes
	pinMode(buttonPin, INPUT);
	pinMode(potPin, INPUT);
	pinMode(switchPin, INPUT);
	pinMode(photoPin, INPUT);
	pinMode(buttonLEDPin, OUTPUT);
	pinMode(potLEDPin, OUTPUT);
	pinMode(switchLEDPin, OUTPUT);
	pinMode(photoLEDPin, OUTPUT);
	pinMode(buzzerPin, OUTPUT);

	// Begin serial communication
	Serial.begin(9600);

	// Initalize random seed and game piece configs
	randomSeed(analogRead(A5));	 // Reads an open pin

	Serial.println(
		"Please ensure all buttons and switches are returned to the beginning "
		"orientation");

	while (digitalRead(buttonPin) == HIGH || digitalRead(potPin) == HIGH ||
		   digitalRead(switchPin) == HIGH) {
		if (digitalRead(buttonPin) == HIGH) {
			Serial.println(
				"Please do not press the button while the game is being setup");
			digitalWrite(buttonLEDPin, HIGH);
			delay(200);
			digitalWrite(buttonLEDPin, LOW);
			delay(200);
			digitalWrite(buttonLEDPin, HIGH);
			delay(200);
			digitalWrite(buttonLEDPin, LOW);
			delay(200);
			digitalWrite(buttonLEDPin, HIGH);
			delay(200);
			digitalWrite(buttonLEDPin, LOW);
		}
		delay(1000);

		if (digitalRead(potPin) == HIGH) {
			Serial.println(
				"Please rotate the potentiometer to the untwisted position");
			digitalWrite(potLEDPin, HIGH);
			delay(200);
			digitalWrite(potLEDPin, LOW);
			delay(200);
			digitalWrite(potLEDPin, HIGH);
			delay(200);
			digitalWrite(potLEDPin, LOW);
			delay(200);
			digitalWrite(potLEDPin, HIGH);
			delay(200);
			digitalWrite(9, LOW);
		}

		delay(1000);

		if (digitalRead(switchPin) == HIGH) {
			Serial.println("Please return the switch to the off position");
			digitalWrite(switchLEDPin, HIGH);
			delay(200);
			digitalWrite(switchLEDPin, LOW);
			delay(200);
			digitalWrite(switchLEDPin, HIGH);
			delay(200);
			digitalWrite(switchLEDPin, LOW);
			delay(200);
			digitalWrite(switchLEDPin, HIGH);
			delay(200);
			digitalWrite(switchLEDPin, LOW);
		}
		delay(1000);
	}

	Serial.println("Get Ready! The Game is starting in:");
	tone(buzzerPin, 262);
	delay(500);
	noTone(buzzerPin);
	delay(500);
	Serial.println("3");
	tone(buzzerPin, 262);
	delay(500);
	noTone(buzzerPin);
	delay(500);
	Serial.println("2");
	tone(buzzerPin, 262);
	delay(500);
	noTone(buzzerPin);
	delay(500);
	Serial.println("1");
	tone(buzzerPin, 349);
	delay(1000);
	noTone(buzzerPin);
}

void loop() {
	// Serial.println("Button is " + buttonState + "          " + "Potentiometer
	// is " + twistItState + "        " + "Switch is " + slideItState + " " +
	// "Thermistor is " + pinchItState); Serial.println(Temperature);

	if (lost == false) {
		int randomNumber =
			random(1, 5);  // Generate a random number between 1 and 5
		if (randomNumber == 1) {
			pinchIt();
		} else if (randomNumber == 2) {
			twistIt();
		} else if (randomNumber == 3) {
			slideIt();
		} else if (randomNumber == 4) {
			pushIt();
		}
		ii = ii + 1;
		if (ii % 5 == 0 && lost == false) {
			Congratulations();
			Serial.println("Nice Going! You beat the round");
			delay(1000);
			Serial.println("Get Ready!");
			Time = Time * 0.95;
		}
		delay(1000);
	}
}

void Count() {}

void pushIt() {
	Serial.println("Push it!");

	digitalWrite(buttonLEDPin, HIGH);
	timestart = millis();
	timeend = millis();

	while (digitalRead(buttonPin) == LOW) {
		timeend = millis();
		Timer();
		if ((timeend - timestart) > Time) {
			lost = true;
			Serial.println("Too Slow! You Lost!");
			Lost_tone();
			delay(100);
			Serial.println(String("Final Score = ") + ii +
						   " correct reactions");
			break;
		}
	}
	digitalWrite(buttonLEDPin, LOW);
}

void twistIt() {
	Serial.println("Twist it!");
	digitalWrite(potLEDPin, HIGH);
	timestart = millis();
	timeend = millis();
	while (digitalRead(potPin) == LOW) {
		timeend = millis();
		Timer();
		if ((timeend - timestart) > Time) {
			lost = true;
			Serial.println("Too Slow! You Lost!");
			Lost_tone();
			delay(100);
			Serial.println(String("Final Score = ") + ii +
						   " correct reactions");
			break;
		}
	}
	digitalWrite(potLEDPin, LOW);
}

void slideIt() {
	Serial.println("Slide it!");
	digitalWrite(switchLEDPin, HIGH);
	timestart = millis();
	timeend = millis();
	while (digitalRead(switchPin) == LOW) {
		timeend = millis();
		Timer();
		if ((timeend - timestart) > Time) {
			lost = true;
			Serial.println("Too Slow! You Lost!");
			Lost_tone();
			delay(100);
			Serial.println(String("Final Score = ") + ii +
						   " correct reactions");
			break;
		}
	}
	digitalWrite(switchLEDPin, LOW);
}

void pinchIt() {
	Serial.println("Pinch it!");
	digitalWrite(photoLEDPin, HIGH);
	timestart = millis();
	timeend = millis();
	initalPinch = analogRead(photoPin);
	while (analogRead(photoPin) > 0.9 * initalPinch) {
		timeend = millis();
		Timer();
		if ((timeend - timestart) > Time) {
			lost = true;
			Serial.println("Too Slow! You Lost!");
			Lost_tone();
			delay(100);
			Serial.println(String("Final Score = ") + ii +
						   " correct reactions");
			break;
		}
	}
	delay(200);
	digitalWrite(photoLEDPin, LOW);
}

void Lost_tone() {
	tone(buzzerPin, 293.66);
	delay(400);
	tone(buzzerPin, 277.18);
	delay(400);
	tone(buzzerPin, 261.63);
	delay(400);
	tone(buzzerPin, 246.94);
	delay(400);
	noTone(buzzerPin);
}

void Timer() {
	tone(buzzerPin, 1000);	  // Turn on the buzzer at 1000 Hz
	delay(Time / buzzerPin);  // Keep the buzzer on for 100 milliseconds
	noTone(buzzerPin);		  // Turn off the buzzer
	delay(Time / buzzerPin);  // Delay between ticks
}

void Congratulations() {
	tone(buzzerPin, 523);  // C5
	delay(250);
	tone(buzzerPin, 659);  // E5
	delay(250);
	tone(buzzerPin, 783);  // G5
	delay(250);
	tone(buzzerPin, 659);  // E5
	delay(250);
	tone(buzzerPin, 783);  // G5
	delay(250);
	tone(buzzerPin, 880);  // A5
	delay(500);
	noTone(buzzerPin);
}