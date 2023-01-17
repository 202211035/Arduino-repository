#include <NewPing.h> // 번호는 각자 맞게 정할 것

#define MOTOR_R1 2
#define MOTOR_R2 3
#define MOTOR_R_ENA 5

#define MOTOR_L1 7
#define MOTOR_L2 4
#define MOTOR_L_ENB 6

#define SONAR_F_PIN 8
#define SONAR_R_PIN 10 
#define SONAR_L_PIN 11  

double F_distance =0;
double L_distance =0;
double R_distance =0;

int speed_l=100;
int speed_r=100;
int dir_r=1;
int dir_l=1;

NewPing sonar[3] =
{
  NewPing (SONAR_F_PIN, SONAR_F_PIN, 500),
  NewPing (SONAR_R_PIN, SONAR_R_PIN, 500),
  NewPing (SONAR_L_PIN, SONAR_L_PIN, 500)
};

void motor_control(int dir_l, int speed_l, int dir_r, int speed_r)
{
   if(dir_l==1) // 전진
   {
     digitalWrite(MOTOR_L1, HIGH);
     digitalWrite(MOTOR_L2, LOW);
     analogWrite(MOTOR_L_ENB, speed_l);  
   }
   else if(dir_l==-1)//후진
   {  
     digitalWrite(MOTOR_L1, LOW);
     digitalWrite(MOTOR_L2, HIGH);
     analogWrite(MOTOR_L_ENB, speed_l); 
   }
   else
   {
     digitalWrite(MOTOR_L1, LOW);
     digitalWrite(MOTOR_L2, LOW);
     analogWrite(MOTOR_L_ENB, 0);
   }
    if(dir_r==1) // 전진
   {
     digitalWrite(MOTOR_R1, HIGH);
     digitalWrite(MOTOR_R2, LOW);
     analogWrite(MOTOR_R_ENA, speed_r);  
   }
   else if(dir_r==-1)//후진
   {  
     digitalWrite(MOTOR_R1, LOW);
     digitalWrite(MOTOR_R2, HIGH);
     analogWrite(MOTOR_R_ENA, speed_r); 
   }
   else
   {
     digitalWrite(MOTOR_R1, LOW);
     digitalWrite(MOTOR_R2, LOW);
     analogWrite(MOTOR_R_ENA, 0);
   }
}

void setup() 
{
  Serial.begin(9600); //9600 속도로 통신을 시작 한다.
  pinMode(MOTOR_R1, OUTPUT);
  pinMode(MOTOR_R2,OUTPUT);
  pinMode(MOTOR_R_ENA, OUTPUT);

  pinMode(MOTOR_L1, OUTPUT);
  pinMode(MOTOR_L2, OUTPUT);
  pinMode(MOTOR_L_ENB, OUTPUT);

  F_distance = sonar[0].ping_cm() * 10;
  L_distance = sonar[1].ping_cm() * 10;
  R_distance = sonar[2].ping_cm() * 10;
}

void loop()
{
  F_distance = sonar[0].ping_cm() * 10;
  L_distance = sonar[1].ping_cm() * 10;
  R_distance = sonar[2].ping_cm() * 10;
  motor_control(dir_l, speed_l, dir_r, speed_r);
  Serial.print(F_distance);
  Serial.print("   ");
  Serial.print(R_distance);
  Serial.print("   ");
  Serial.println(L_distance);
  if(F_distance<=160)
  {
    motor_control(-1, 1000, 1, 1000);
    delay(50);
    motor_control(-1, 1000, 1, 1000);
    delay(50);
    motor_control(-1, 1000, 1, 1000);
    delay(50);
  }
  else if(R_distance<=160)
  {
    motor_control(-1, 100, 1, 100);
    delay(50);
    motor_control(-1, 100, 1, 100);
    delay(50);
  }
  else if(L_distance<=160)
  {
    motor_control(1, 100, -1, 100);
    delay(50);
    motor_control(1, 100, -1, 100);
    delay(50);
  }
}
