#define MOTOR_L1 2
#define MOTOR_L2 3
#define MOTOR_L_ENL 5

#define MOTOR_R1 4
#define MOTOR_R2 7
#define MOTOR_R_ENR 6

#define F_Sonar 8
#define L_Sonar 11
#define R_Sonar 10

int dir_l;
int speed_l;
int dir_r;
int speed_r;

void setup()
{
  pinMode(MOTOR_L1, OUTPUT);
  pinMode(MOTOR_L2, OUTPUT);
  pinMode(MOTOR_L_ENL, OUTPUT);
  
  pinMode(MOTOR_R1, OUTPUT);
  pinMode(MOTOR_R2, OUTPUT);
  pinMode(MOTOR_R_ENR, OUTPUT);
  
  pinMode(F_Sonar, OUTPUT);
  pinMode(L_Sonar, OUTPUT);
  pinMode(R_Sonar, OUTPUT);

  Serial.begin(9600);
}

float F_Sonar_sensor()
{ 
    float duration = 0.0;
    float distance = 0.0;
  
    pinMode(F_Sonar, OUTPUT);
    digitalWrite(F_Sonar,LOW);
    digitalWrite(F_Sonar,HIGH);
    delay(10);
    digitalWrite(F_Sonar,LOW);
    pinMode(F_Sonar, INPUT);
    duration = pulseIn(F_Sonar,HIGH);
    distance = (duration*340.0)/2.0/10000.0;
    
    return distance;
}

float L_Sonar_sensor()
{
    float duration = 0.0;
    float distance = 0.0;
  
    pinMode(L_Sonar, OUTPUT);
    digitalWrite(L_Sonar,LOW);
    digitalWrite(L_Sonar,HIGH);
    delay(10);
    digitalWrite(L_Sonar,LOW);
    pinMode(L_Sonar, INPUT);
    duration = pulseIn(L_Sonar,HIGH);
    distance = (duration*340.0)/2.0/10000.0;
    
    return distance;
}
float R_Sonar_sensor()
{
    float duration = 0.0;
    float distance = 0.0;
  
    pinMode(R_Sonar, OUTPUT);
    digitalWrite(R_Sonar,LOW);
    digitalWrite(R_Sonar,HIGH);
    delay(10);
    digitalWrite(R_Sonar,LOW);
    pinMode(R_Sonar, INPUT);
    duration = pulseIn(R_Sonar,HIGH);
    distance = (duration*340.0)/2.0/10000.0;
    
    return distance;
}
void motor_control(int dir_1,int speed_1,int dir_r,int speed_r)
{
    if(dir_l==1) // 전진
   {
     digitalWrite(MOTOR_L1, HIGH);
     digitalWrite(MOTOR_L2, LOW);
     analogWrite(MOTOR_L_ENL, speed_l);  
   }
   else if(dir_l==-1)//후진
   {  
     digitalWrite(MOTOR_L1, LOW);
     digitalWrite(MOTOR_L2, HIGH);
     analogWrite(MOTOR_L_ENL, speed_l); 
   }
   else
   {
     digitalWrite(MOTOR_L1, LOW);
     digitalWrite(MOTOR_L2, LOW);
     analogWrite(MOTOR_L_ENL, 0);
   }
    if(dir_r==1) // 전진
   {
     digitalWrite(MOTOR_R1, HIGH);
     digitalWrite(MOTOR_R2, LOW);
     analogWrite(MOTOR_R_ENR, speed_r);  
   }
   else if(dir_r==-1)//후진
   {  
     digitalWrite(MOTOR_R1, LOW);
     digitalWrite(MOTOR_R2, HIGH);
     analogWrite(MOTOR_R_ENR, speed_r); 
   }
   else
   {
     digitalWrite(MOTOR_R1, LOW);
     digitalWrite(MOTOR_R2, LOW);
     analogWrite(MOTOR_R_ENR, 0);
   }
}

double F_sonar_distance=0;
double L_sonar_distance=0;
double R_sonar_distance=0;

void loop()
{
    float F_sonar_distance=0.0;
    F_sonar_distance=F_Sonar_sensor();
    
    float L_sonar_distance=0.0;
    L_sonar_distance=L_Sonar_sensor();
    
    float R_sonar_distance=0.0;
    R_sonar_distance=R_Sonar_sensor();
    
    Serial.print(F_sonar_distance);
    Serial.print("     ");
    Serial.print(R_sonar_distance);
    Serial.print("     ");
    Serial.println(L_sonar_distance);
    Serial.print("     ");
  
    if(F_sonar_distance<=150)
    {
      motor_control(-1, 100, -1, 100);
      delay(100);
      motor_control(1, 100, -1, 100);
      delay(100);
      motor_control(1, 100, -1, 100);
      delay(100);
    }
    else if(L_sonar_distance<=150)
    {
      motor_control(1, 100, -1, 100);
      delay(100);
      motor_control(1, 100, -1, 100);
      delay(100);
    }
    else if(R_sonar_distance<=150)
    {
      motor_control(-1, 100, 1, 100);
      delay(100);
      motor_control(-1, 100, 1, 100);
      delay(100);
    }
    else
    {
      motor_control(1, 100, 1, 100);
      delay(100);
    }
}
