/*
    Holyoke Codes Zombie Detector

    Uses an ultrasonic distance sensor to detect zombies
    (or other intruders) and alert you using an electronic
    buzzer.

*/

int LEDPin = 6;
int echoPin = 7; // Listen for an echo on this pin
int triggerPin = 8; // Generate an ultrasonic sound with this pin
int buzzerPin = 9;

// Use these variables to calculate how far away things are.
long duration, distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  /*
     The HC-SR04 Ultrasonic sensor has a trigger pin and an echo pin.
    Sending a signal to the trigger pin causes an ultrasonic
    sound to be broadcast. We can detect how long it takes for the echo
    to be heard and calculate the distance using the speed of sound.
  */

  // Generate an ultrasonic sound for 10 microseconds.
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // pulseIn measures the length of time (in microseconds) that
  // it takes for the echo to be heard.
  duration = pulseIn(echoPin, HIGH);

  /*
      Calculate the distance (in cm) based on the speed of sound.
      In air, sound travels 340 m/s = 34,000 cm/s = 0.034 cm/microsecond

      Elapsed time is for a round trip, so divide by 2:
      0.034 cm/microsecond / 2 = 0.017 cm/microsecond
  */
  distance = duration * 0.017;
  // Limit the distance to between 0 and 200 cm.
  distance = constrain(distance, 0, 200);

  if (distance < 100) {
    // Make the LED and buzzer respond when the zombies get close.
    digitalWrite(LEDPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    // It gets faster as the zombies get closer...
    delay(distance * 3);
    digitalWrite(LEDPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(distance * 3);

    /*
       This also works nicely as a trick-or-treater detector
       with the LED inside a pumpkin. You might want to try
       delay(random(50, 500)) for a spooky effect.
       Probably the buzzer isn't so useful for this unless
       you have enough wire to bring it inside and alert you
       for incoming visitors.
    */
  }
}
