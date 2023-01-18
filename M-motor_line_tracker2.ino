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

int speed_l=150;
int speed_r=150;
int dir_r=1;
int dir_l=1;

int line_sensor[5]={0, 0, 0, 0, 0};
int i;
int sum=0;
int line_index=0;

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

int read_line_sensor()
{
  for(i=0; i<5; i++)
  {
    line_sensor[i]=analogRead(A0+i);
    Serial.print(analogRead(A0+i));
    Serial.print("  ");
    if(line_sensor[i]>500)//15~20=검은색, 노랑>900
    {
      line_sensor[i]=1;
      sum++;
    }
    else
    {
      line_sensor[i]=0;
    }
 }
//line_sensor[0]    line_sensor[1]   line_sensor[2]   line_sensor[3]   line_sensor[4]
//       -4              -3   -2         -1    0           1      2        3      4
  if(sum==1)
  {
      if( line_sensor[0]==1)
        line_index = -4; 
      if( line_sensor[1]==1)
        line_index = -2; 
      if( line_sensor[2]==1)
        line_index =  0; 
      if( line_sensor[3]==1)
        line_index =  2; 
      if( line_sensor[4]==1)
        line_index =  4; 
  }
  else if(sum==2)
  {
      if((line_sensor[0]==1)&&(line_sensor[1]==1)) 
        line_index = -3; 
      if( (line_sensor[1]==1)&&(line_sensor[2]==1))
        line_index = -1; 
      if((line_sensor[2]==1)&&(line_sensor[3]==1))
        line_index =  1; 
      if((line_sensor[3]==1)&&(line_sensor[4]==1))
        line_index =  3; 
  }
  Serial.print(line_index);
  Serial.println(" ");
  return line_index;
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
  motor_control(1, 150, 1, 170);
  /*Serial.print(F_distance);
  Serial.print("   ");
  Serial.print(R_distance);
  Serial.print("   ");
  Serial.println(L_distance);*/
  read_line_sensor();
  switch(line_index)
  {
    case -4:
      motor_control(1, 150, 1, 500);
      break;
    case -3:
      motor_control(1, 150, 1, 500);
      break;
    case -2:
      motor_control(1, 150, 1, 500);
      break;
    case -1:
      motor_control(1, 150, 1, 500);
      break;
    case 0:
      motor_control(1, 500, 1, 500);
      break;
    case 1:
      motor_control(1, 500, 1, 150);
      break;
    case 2:
      motor_control(1, 500, 1, 150);
      break;
    case 3:
      motor_control(1, 500, 1, 150);
      break;
    case 4:
      motor_control(1, 500, 1, 150);
      break;
  }
  
  if(F_distance<=40)
  {
    motor_control(-1, 500, 1, 500);
  }
  
  if(R_distance<=40)
  {
    motor_control(-1, 500, 1, 500);
  }
  
  if(L_distance<=40)
  {
    motor_control(1, 500, -1, 500);
  }
}
