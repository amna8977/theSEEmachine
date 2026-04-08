// Define the pins for the Ultrasonic Sensor
const int trigPin = 7;  // Trigger pin
const int echoPin = 6; // Echo pin

// Define the pin for the Beeper
const int beeperPin = 11;

// Define a maximum distance threshold (in centimeters)
const int maxDistance = 100;

// Define a minimum distance threshold (in centimeters)
const int minDistance = 10;

// Define the maximum and minimum frequency for the tone
const int minFrequency = 200;   // the further away, the lower the frequency
const int maxFrequency = 2000;  // the closer it is, the higher the frequency

// Define variables for the duration and distance
long duration;
int distance;

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);

  // Set the trigger pin as an output and the echo pin as an input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set the beeper pin as an output
  pinMode(beeperPin, OUTPUT);
}

void loop() {
  // Clear the trigger pin by setting it LOW:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Set the trigger pin HIGH for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin.  The sound wave has to travel to the object and back.
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;

  // map the frequency based on the distance
  int frequency = map(distance, minDistance, maxDistance, minFrequency, maxFrequency);

  // constrain the distance between the min and max
  distance = constrain(distance, minDistance, maxDistance);

  // Print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Activate the beeper
  if (distance != 100) {
    tone(beeperPin, frequency); // Send frequency sound signal
    delay(10);                  // Delay for 10ms
    noTone(beeperPin);          // Stop sound
  }

  delay(100); // Wait for 0.1 second before the next measurement
}
