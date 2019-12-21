/*
 * rosserial Subscriber Example
 * Blinks an LED on callback
*/
 
 #include <ros.h>
 #include <std_msgs/Empty.h>

/*Example sketch to control a stepper motor with A4988 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */
// Define stepper motor connections and steps per revolution:
#define dirPin 4
#define stepPin 3
#define stepsPerRevolution 200

void run_stepper_motor(void);
 
 ros::NodeHandle nh;
 
 void messageCb( const std_msgs::Empty& toggle_msg){
   digitalWrite(13, HIGH-digitalRead(13));   // blink the led
   if(digitalRead(13)) {
       run_stepper_motor();
   }
 }
 
 ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb );
 
 void setup()
 {
   pinMode(13, OUTPUT);
   pinMode(stepPin,OUTPUT);
   pinMode(dirPin,OUTPUT);
   nh.initNode();
   nh.subscribe(sub);
 }
 
 void loop()
 {
   nh.spinOnce();
   delay(1);
 }

void run_stepper_motor() {
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);
  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
    delay(1000);
 }