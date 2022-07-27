#if (ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include <WProgram.h>
#endif

// importing libraryes

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Empty.h>
#include <AFMotor.h>
#include <Servo.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle nh;

// pins and motor description

#define trig 51        // Ultrasonic trigger pin
#define echo 50        // Ultrasonic echo pin
AF_DCMotor Motor(1);   //dc motor
Servo servo;

// Publistion and subscription classes

// Motor control class
void mes_forward(const std_msgs::String& toggle_msg)
{
  forward();
}

void mes_backward(const std_msgs::String& toggle_msg)
{
  backward();
}

void mes_stop(const std_msgs::String& toggle_msg)
{
  stopping();
}

// LED Control class

void messageCb( const std_msgs::Empty& toggle_msg)
{
  digitalWrite(52, HIGH-digitalRead(52));   // blink the led
}

// Servo Control class

void servo_cb(const std_msgs::UInt16 & cmd_msg)
{
  servo.write(cmd_msg.data);
  digitalWrite(13, HIGH-digitalRead(13));
}

// ---------------------------- subscriber message for motors and LED  -------------------------------------
ros::Subscriber<std_msgs::String> motor_forward("motor_forward", &mes_forward);
ros::Subscriber<std_msgs::String> motor_backward("motor_backward", &mes_backward);
ros::Subscriber<std_msgs::String> motor_stop("motor_stop", &mes_stop);
ros::Subscriber<std_msgs::Empty> led("toggle_led", &messageCb );
ros::Subscriber<std_msgs::UInt16> sub("servo", servo_cb);

// ------------------------ publisher message for ultrasonic sensor ------------------------------
std_msgs::Int16 int_msg;
ros::Publisher ultra("ultra", &int_msg);

void setup()
{

  nh.initNode();

  // ------ motor subscriber --------------
  nh.subscribe(motor_forward);
  nh.subscribe(motor_backward);
  nh.subscribe(motor_stop);
  nh.subscribe(led); 
  nh.subscribe(sub);

  // ------ ultrasonic publisher -----------
  nh.advertise(ultra);
  
  // ---- ultrasonic sensor pin description ------------
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(52, OUTPUT);
  pinMode(13, OUTPUT);

  servo.attach(22);
}

void loop()
{
  long duration;
  int distance;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (duration/2) / 29.1;
  int_msg.data = distance;
  ultra.publish(&int_msg);

  nh.spinOnce();
  delay(1);
  
}

void forward()
{
  Motor.setSpeed(255);
  Motor.run(FORWARD);
}

void backward()
{
  Motor.setSpeed(255);
  Motor.run(BACKWARD);
}

void stopping()
{
  Motor.setSpeed(255);
  Motor.run(RELEASE);
}
