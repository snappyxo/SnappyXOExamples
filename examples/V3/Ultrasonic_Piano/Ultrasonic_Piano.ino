// Piano Project Code This project aims to teach the user about the ultrasonic
// sensor avialable in the Advanced Robotics SnappyXO kit. When a key is pressed
// on the piano, a paddle blocks the ultrasonic sensor. Then, according to the
// distance that paddle is away from the sensor, a tone is played with a buzzer.
// Pin Definitions
#define trigger 9
#define echo 10
#define buzzerPin 11  // Must be placed on PWM enabled pin

// Parameter Definitions
const float OMEGA_C =
	50.0 / (2.0 * 3.1415);	// [Hz], Cut-off frequency for low pass filter
const float T = 50.0;		// [ms], Sampling period of loop
float data;
float fdata;
float fdata_km1;			  // The k-1 step of the output data from the filter
float data_km1;				  // The k-1 step of the input data to the filter
unsigned long currentMillis;  // [ms], current time
unsigned long prevMillis = 0.0;	 // [ms], time of last step, k-1
unsigned long duration;
float distance_cm;
float speedOfSound = 33100.0;  // [cm/s]

// Note Frequency Data
int NOTE_C4 = 262;	// All of these values are in Hz
int NOTE_D4 = 294;
int NOTE_E4 = 330;
int NOTE_F4 = 349;
int NOTE_G4 = 392;
int NOTE_A4 = 440;
int NOTE_C5 = 523;
float C_nom = 7;  // [cm], Nominal values for the distance of each paddle from
				  // emperical trials
float D_nom = 13;
float E_nom = 20;
float backStop = 25;
float allowableRange = 2.5;	 // Defines acceptable range from nominal value
float CID;
float changeInDis;
float allowableCID = 2.;
float prevDis = 0;
int NOTE;

void setup() {
	// Declare pinModes
	pinMode(trigger, OUTPUT);
	pinMode(echo, INPUT);
	pinMode(buzzerPin, OUTPUT);

	// Begin serial monitor
	Serial.begin(115200);
}

void loop() {
	// Timing if statement
	currentMillis = millis();

	// Protocol for ultrasound sensor
	digitalWrite(trigger, LOW);
	delayMicroseconds(2);
	digitalWrite(trigger, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigger, LOW);

	duration = pulseIn(echo, HIGH, 50000);

	if ((currentMillis - prevMillis) > T) {
		// Calculate distance using speed of sound and duration and filter the
		// data
		distance_cm = (speedOfSound * duration * 1.0e-6) * 0.5;
		if (distance_cm != 0) {
			if (distance_cm > backStop) {
				distance_cm = backStop;
			}
			data = distance_cm;
			fdata = filteredData(data, OMEGA_C, T, fdata_km1, data_km1);

			CID = abs(fdata - fdata_km1);

			// Print data for debugging
			Serial.print(C_nom);
			Serial.print(",");
			Serial.print(D_nom);
			Serial.print(",");
			Serial.print(E_nom);
			Serial.print(",");
			Serial.print(backStop);
			Serial.print(",");
			Serial.print(CID);
			Serial.print(",");
			Serial.print(allowableCID);
			Serial.print(",");
			Serial.print(data);
			Serial.print(",");
			Serial.println(fdata);

			if (CID < allowableCID && data < backStop) {
				if (fdata <= C_nom + allowableRange &&
					fdata >= C_nom - allowableRange) {
					NOTE = NOTE_C4;
				} else if (fdata <= D_nom + allowableRange &&
						   fdata >= D_nom - allowableRange) {
					NOTE = NOTE_D4;
				} else if (fdata <= E_nom + allowableRange &&
						   fdata >= E_nom - allowableRange) {
					NOTE = NOTE_E4;
				} else {
					NOTE = 0;
				}

				tone(buzzerPin, NOTE, 100);
			}
		}

		fdata_km1 = fdata;
		data_km1 = data;
		prevDis = distance_cm;
		prevMillis = currentMillis;
	}
}

// Data Filtering Function
float filteredData(float DATA, float OMEGA_C, float T, float FDATA_KM1,
				   float DATA_KM1) {
	// This function takes inputs of:
	// DATA: Noisy data from sensor
	// OMEGA_C: Cutoff frequency [Hz]
	// T: Sampling Period [ms]
	// FDATA_KM1: Filtered data from the previous loop
	// DATA_KM1: Unfiltered data from the previous loop
	//
	// And outputs:
	// FDATA: The filtered, smooth signal

	float T_sec = T / 1000.0;
	float FDATA =
		(1 - OMEGA_C * T_sec) * FDATA_KM1 + OMEGA_C * T_sec * DATA_KM1;
	return FDATA;
}