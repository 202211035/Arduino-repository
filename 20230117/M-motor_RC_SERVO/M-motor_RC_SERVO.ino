//Steering Servo Control
#include <Servo.h>
#define RC_SERVO_PIN 6
#define NEURAL_ANGLE 105
#define LEFT_STEER_ANGLE -30
#define RIGHT_STEER_ANGLE 30
#define MOTOR_PWM 5
#define MOTOR_DIR 4

Servo Steeringservo;
int Steering_Angle=NEURAL_ANGLE;

void setup() 
{
  pinMode(MOTOR_DIR, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);

  Steeringservo.attach(RC_SERVO_PIN);
  Steeringservo.write(NEURAL_ANGLE);

}

void steering_control(int steer_angle)
{
  Steeringservo.write(NEURAL_ANGLE+steer_angle);
}

void motor_control(int direction, int speed)
{
  digitalWrite(MOTOR_DIR, 1);
 analogWrite(MOTOR_PWM, 50);
}

void loop() 
{
   int i;
   for(i=0; i<255; i++)
  {
    motor_control(1, i);
    delay(10);
  }
  
   steering_control(LEFT_STEER_ANGLE);
   delay(1000);
   steering_control(RIGHT_STEER_ANGLE);
   delay(1000);
   motor_control(1, 100);

}
