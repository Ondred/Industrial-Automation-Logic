/*
 * Industrial Distance & Object Monitor
 * Targeted for: Zubi Technologies SIWES Application
 * Description: Reads ultrasonic sensor data and outputs formatted 
 * JSON-like strings for Python backend integration.
 */

const int trigPin = 9;
const int echoPin = 10;
const int alertLed = 13; // Onboard LED for alerts

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(alertLed, OUTPUT);
  
  // High baud rate for stable communication with Python
  Serial.begin(9600); 
  while (!Serial) { ; // Wait for serial port to connect
  }
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  distance = duration * 0.034 / 2;

  // Logic: Visual alert if object is too close (Critical Limit)
  if (distance < 10 && distance > 0) {
    digitalWrite(alertLed, HIGH);
  } else {
    digitalWrite(alertLed, LOW);
  }

  // Format data for Python Backend: "Distance: [value]"
  Serial.print("Data_Packet: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500); // 0.5s sampling rate
}
