// This project aims to educate the user on how to connect use a PIR sensor and
// a Piezzo buzzer to detect a person and play a song when they're detected Pin
// Definitions
int PIRPin = 2;
int buzzerPin = 5;

// Parameter Definitions
int NOTE_G3 = 196;
int NOTE_C4 = 262;
int NOTE_D4 = 294;
int NOTE_E4 = 330;
bool isTriggered = false;
int V_PID;
unsigned long currentMillis;
unsigned long prevMillis = 0;
int timeBetweenChimes = 10000;

void setup() {
	// Define pinModes
	pinMode(buzzerPin, OUTPUT);
	pinMode(PIRPin, INPUT);

	// Begin serial communications
	Serial.begin(9600);
}

void loop() {
	currentMillis = millis();

	V_PID = digitalRead(PIRPin);

	// Serial.println(V_PID);

	if (V_PID == HIGH) {
		isTriggered = true;
	}

	if (isTriggered == true && currentMillis - prevMillis > timeBetweenChimes) {
		bellChime();
		isTriggered = false;
		prevMillis = currentMillis;
	} else {
		isTriggered = false;
	}
}

void bellChime() {
	// This function plays a classic bell chime tune

	int speed = 2;

	tone(buzzerPin, NOTE_E4);
	delay(speed * 250);
	tone(buzzerPin, NOTE_C4);
	delay(speed * 250);
	tone(buzzerPin, NOTE_D4);
	delay(speed * 250);
	tone(buzzerPin, NOTE_G3);
	delay(speed * 500);

	noTone(buzzerPin);
	delay(speed * 250);

	tone(buzzerPin, NOTE_G3);
	delay(speed * 250);
	tone(buzzerPin, NOTE_D4);
	delay(speed * 250);
	tone(buzzerPin, NOTE_E4);
	delay(speed * 250);
	tone(buzzerPin, NOTE_C4);
	delay(speed * 750);
	noTone(buzzerPin);
}