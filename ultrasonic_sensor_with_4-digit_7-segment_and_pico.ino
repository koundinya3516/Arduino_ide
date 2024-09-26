// Pin definitions for the 7-segment display
const int segmentPins[] = {0, 1, 2, 3, 4, 5, 6, 7}; // Segments A, B, C, D, E, F, G, DP
const int digitPins[] = {8, 9, 10, 11};  // Common anode pins for the 4 digits

// Pin definitions for the HC-SR04 ultrasonic sensor
const int trigPin = 15;  // Trigger pin
const int echoPin = 14;  // Echo pin

// Digit segment patterns for common anode display (0 = ON, 1 = OFF)
byte digitPatterns[10][8] = {
  {0, 0, 0, 0, 0, 0, 1, 1},  // 0
  {1, 0, 0, 1, 1, 1, 1, 1},  // 1
  {0, 0, 1, 0, 0, 1, 0, 1},  // 2
  {0, 0, 0, 0, 1, 1, 0, 1},  // 3
  {1, 0, 0, 1, 1, 0, 0, 1},  // 4
  {0, 1, 0, 0, 1, 0, 0, 1},  // 5
  {0, 1, 0, 0, 0, 0, 0, 1},  // 6
  {0, 0, 0, 1, 1, 1, 1, 1},  // 7
  {0, 0, 0, 0, 0, 0, 0, 1},  // 8
  {0, 0, 0, 0, 1, 0, 0, 1}   // 9
};

void setup() {
  // Set up segment pins as outputs
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  // Set up digit pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], LOW);  // Turn off all digits initially
  }

  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);  // For debugging purposes
}

void loop() {
  int distance = getDistance();  // Get the distance from the ultrasonic sensor

  if (distance == -1) {
    displayNumber(9999);  // Show "9999" if out of range
  } else {
    displayNumber(distance);  // Display the distance
  }

  delay(100);  // Delay before next reading
}

// Function to get distance from ultrasonic sensor
int getDistance() {
  // Trigger a 10us pulse on the TRIG pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo pulse duration (in microseconds)
  long duration = pulseIn(echoPin, HIGH, 30000);  // 30ms timeout

  // If no echo received (timeout), return -1
  if (duration == 0) {
    return -1;
  }

  // Calculate distance in centimeters
  int distance = duration * 0.0343 / 2;
  return distance;
}

// Function to clear all digits (turn off)
void clearDigits() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], LOW);
  }
}

// Function to display a single digit on a specific position
void displayDigit(int digit, int number) {
  // Turn on the corresponding digit (common anode, high = on)
  digitalWrite(digitPins[digit], HIGH);

  // Set the corresponding segments for the current digit
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], digitPatterns[number][i]);
  }

  // Delay for multiplexing
  delay(5);

  // Turn off the digit after displaying
  digitalWrite(digitPins[digit], LOW);
}

// Function to display a number on the 4-digit 7-segment display
void displayNumber(int number) {
  // Ensure the number is a 4-digit string
  char buffer[5];
  sprintf(buffer, "%04d", number);

  // Display each digit one by one
  for (int digit = 0; digit < 4; digit++) {
    int currentNumber = buffer[digit] - '0';  // Convert char to int
    displayDigit(digit, currentNumber);       // Display the digit
  }
}
