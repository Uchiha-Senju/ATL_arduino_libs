/*
 *  Ultrasonic Sensor Class
 *  Made by Varad Mahashabde
 *  created 26 July, 2019
 *  
 *  A simple class that manages the ultrasonic sensor interface
 *  and provides a simple abstraction to the user :
 *    update values
 *    read the time delay
 *    read the distance to the reflecting object
 *  
 */
#include "new.h"
 
class UltrasonicSensor {
  const unsigned trigger_pin;
  const unsigned echo_pin;
  float time_delay;
  float distance;

  public:
    UltrasonicSensor() : trigger_pin(0), echo_pin(1) {
      // Set time and distance to null values
      time_delay = distance = 0;
      // Initialize pins as input or output. Very very important
      pinMode(trigger_pin, OUTPUT);
      pinMode(echo_pin, INPUT);
    }
    UltrasonicSensor(const int trig_pin, const int ec_pin) : trigger_pin(trig_pin), echo_pin(ec_pin) {
      // Set time and distance to null values
      time_delay = distance = 0;
      // Initialize pins as input or output. Very very important
      pinMode(trigger_pin, OUTPUT);
      pinMode(echo_pin, INPUT);
    }
    UltrasonicSensor(const UltrasonicSensor& ul) : trigger_pin(ul.trigger_pin), echo_pin(ul.echo_pin) {
      // Set time and distance to null values
      time_delay = distance = 0;
      // Initialize pins as input or output. Very very important
      pinMode(trigger_pin, OUTPUT);
      pinMode(echo_pin, INPUT);
    }
    UltrasonicSensor& operator=(const UltrasonicSensor& ul) {
      if (this != &ul) { // Check for self-assignment
        this->~UltrasonicSensor();
        new(this) UltrasonicSensor(ul);
      }
      return *this;
    }

    float getDistance() {
      return distance;
    }
    float getTimeDelay() {
      return time_delay;
    }
    void update() {
      // Set trig to LOW to prepare for HIGH pulse
      digitalWrite(trigger_pin, LOW);
      delay(5);
      // HIGH pulse triggers the module to send a sound pulse
      digitalWrite(trigger_pin, HIGH);
      delay(10);
      digitalWrite(trigger_pin, LOW);

      // Read a HIGH pulse from echo. pulseIn measures in microseconds
      // Length of pulse is the time until the sound pulse is heard back
      // Note : check with pulseInLong if longer wait times can be achieved
      // Reason : Time delay for maximum observed length is eerily close to 65535(2^16 -1)
      time_delay = pulseIn(echo_pin, HIGH);

      // Velocity calculations for sound in air. 
      // v_sound = 343 metres / second in dry air at 293K(20 degC)
      // ^^^^^^^ this is subject to change, as per changes in temperature, composition e.g. humidity, etc.
      // Maybe try and calibrate with temperature and humidity sensor???

      // Distance is measured in centimeters
      distance = time_delay * 343 * 100 / 10e6;
      // Sound pulse makes a two-way journey
      distance *= 0.5;
    }
};
