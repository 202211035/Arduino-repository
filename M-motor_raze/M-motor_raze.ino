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

int speed_l=120;
int speed_r=100;
int dir_r=1;
int dir_l=1;

NewPing sonar[3] =
{
  NewPing (SONAR_F_PIN, SONAR_F_PIN, 500),
  NewPing (SONAR_R_PIN, SONAR_R_PIN, 500),
  NewPing (SONAR_L_PIN, SONAR_L_PIN, 500)
};

int line_sensor[5] = {0,0,0,0,0};
int sensor =1;
int sum = 1;
int stopit=0;

int mode_0()
{
  int i;
  int sum = 0;
  int stopit=0;
  for(i = 0; i < 5; i++)
  {
    line_sensor[i] = analogRead(A0 + i);
   if(i==0) if(  line_sensor[i] > 550) sum = sum - 3;       
   if(i==1) if(  line_sensor[i] > 550) sum = sum - 1;
   if(i==2) if(  line_sensor[i] > 550) sum = sum ;
   if(i==3) if(  line_sensor[i] > 550) sum = sum + 1; 
   if(i==4) if(  line_sensor[i] > 550) sum = sum + 3;
   if(analogRead(A0+i)<550) stopit= stopit+100;
  }
  return sum;           
}

void motor_control(int speed_l, int dir_l, int speed_r, int dir_r)
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

  pinMode(SONAR_F_PIN, OUTPUT);
  pinMode(SONAR_R_PIN, OUTPUT);
  pinMode(SONAR_L_PIN, OUTPUT);
}

void read_distance()
{
  motor_control(speed_l, dir_l, speed_r, dir_r);
  F_distance = sonar[0].ping_cm() * 10;
  L_distance = sonar[1].ping_cm() * 10;
  R_distance = sonar[2].ping_cm() * 10;
  if(F_distance<=200)
  {
    if(L_distance<=200)
    {
      while(F_distance < 200)
      {
        motor_control(150, 1, 150, -1);
      }
      delay(300);
    }
    if(R_distance<=200)
    {
      while(F_distance < 200)
      {
        motor_control(150, -1, 150, 1);
      }
      delay(300);
    }
  }
}
void go_line()
{
  line_sensor[5];
  mode_0(); 
  motor_control(speed_l, dir_l, speed_r, dir_r);

  sensor = mode_0();
  if(sensor < 0)
  {
    motor_control(sum * 120,1,0,0); 
  }
  else if(sensor > 0)
  {
    motor_control(0,0,-sum * 100,1);
  }
  else
  {
     motor_control(100,1,100,1);
     if(F_distance < 200)
     {
      motor_control( 1, 0, 1, 0);
     }
  }
}
void loop()
{
  go_line();
  while(stopit>=500)
  {
    motor_control(0, 1, 0, 1);
    delay(1000);
    read_distance();
  }
}
