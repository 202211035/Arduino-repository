#define MOTOR_PWM 5
#define MOTOR_DIR 4

void setup() 
{
  pinMode(MOTOR_DIR, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);

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

 
 motor_control(1, 100);

}
