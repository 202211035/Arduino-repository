#define AOpin  A0     // Analog output - yellow
#define SIpin  22     // Start Integration - orange
#define CLKpin 23     // Clock - red
// Vcc - brown
// GND - black
#include<NewPing.h>
#define NPIXELS 130  // No. of pixels in array

byte Pixel[NPIXELS]; // Field for measured values <0-255>

int LineSensor_Data[NPIXELS];           // line sensor data(original)
int LineSensor_Data_Adaption[NPIXELS];  // line sensor data(modified)
int MAX_LineSensor_Data[NPIXELS];       // Max value of sensor
int MIN_LineSensor_Data[NPIXELS];       // Min value of sensor
int flag_line_adapation;          // flag to check line sensor adpation

#define FASTADC 1
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

/////////////////////Ultrasonic Sensor////////////////////////////////////////////////////////////////////////////
#define MOTOR_DIR 4
#define MOTOR_PWM 5

/////////////////////Steering Servo Control////////////////////////////////////////////////////////////////////////
#include <Servo.h>
#define RC_SERVO_PIN 8
#define NETURAL_ANGLE 120
#define LEFT_STEER_ANGLE -40
#define RIGHT_STEER_ANGLE 40
#define L_Sonar_TRIG 50 
#define L_Sonar_ECHO 48   
#define F_Sonar_TRIG 50 
#define F_Sonar_ECHO 50
#define R_Sonar_TRIG 50 
#define R_Sonar_ECHO 50 
#define MaxDistance  300


//////////////////////////////////////////////DC_Motor_Control/////////////////////////////////////////////////////
#define MOTOR_DIR 4
#define MOTOR_PWM 5

int Motor_Speed =0;
#define NORMAL_SPEED 100
#define SLOW_SPEED    70

void motor_control(int direction, int speed)
{
  digitalWrite(MOTOR_DIR, 1-direction);
  analogWrite(MOTOR_PWM, speed);

}

///////////////////////////////////Steering Servo Control////////////////////////////////////////
void steering_control(int steer_angle)
{
  

  if(steer_angle >= RIGHT_STEER_ANGLE) steer_angle = RIGHT_STEER_ANGLE;
  if(steer_angle <= LEFT_STEER_ANGLE) steer_angle = LEFT_STEER_ANGLE;
  Steeringservo.write(NETURAL_ANGLE + steer_angle);
}

//////////////////////////////////////Steering Servo Control///////////////////////////
void wall_following2()
  {
 
    int A=1170, B=100;
    read_sonar_sensor();
  
  if(R_Sonar_distance + L_Sonar_distance <= A && R_Sonar_distance+B >= L_Sonar_distance && R_Sonar_distance-B <= L_Sonar_distance)
  {
    motor_control(-1,110);
    steering_control(14);
  }

  else if(L_Sonar_distance > R_Sonar_distance)  
  {
    motor_control(-1,110);
    steering_control(20);
           // delay(5);
  }
 
 else if(L_Sonar_distance < R_Sonar_distance)
  {
    motor_control(-1,110);
    steering_control(8);
           // delay(5);
  }
  else
  {
    motor_control(-1,110);
           // delay(5);
  }
}
  
void wall_following1()
{
       read_sonar_sensor();
      
       update_sonar_error();
   
    
       motor_control(-1,100);
       delay(5);
       update_sonar_old();
       
       if(L_Sonar_Error > 0)
       {
         steering_control(20);
         delay(5);
         update_sonar_old();
         
       }
       else if(L_Sonar_Error < 0)
       {
         steering_control(8);
         delay(5);
         update_sonar_old();
       }

    }
    void wall_following()
    {
      if(R_Sonar_distance == 3500)
      {
       wall_following1();
      }
      else
      {
        wall_following2();
      }
    }
  
  int turn_right()
  {
    if(F_Sonar_distance<1000 && F_Sonar_distance != 3500)
    {
      Steeringservo.write(180);
      motor_control(-1,130);
      delay(700);
    }
     return 1;
  }    
 
 int count = 0;
 
 void turn_corner()
{
  int d = 16;
    
  read_sonar_sensor();
  if(R_Sonar_distance+L_Sonar_distance <= 1170)
  {
    wall_following2();
    delay(100);
  }

  else if(R_Sonar_distance+L_Sonar_distance >= 1170)
  {
    steering_control(d);
    if(F_Sonar_distance<1000)
  {
    Steeringservo.write(180);
    motor_control(-1,130);
    delay(100);
  }
  delay(100);
  count++;
  }
  else 
    motor_control(-1,100);
  delay(100);   
 
}

int flag = 0;

void steering_control(int steer_angle);

 NewPing R_sensor(R_Sonar_TRIG,R_Sonar_ECHO,MaxDistance);
  
  float R_Sonar_Error = 0.0;
  float R_Sonar_distance = 0.0;
  float R_Sonar_distance_old = 0.0;

  NewPing L_sensor(L_Sonar_TRIG,L_Sonar_ECHO,MaxDistance);
  
  float L_Sonar_Error = 0.0;
  float L_Sonar_distance = 0.0;
  float L_Sonar_distance_old = 0.0;

  NewPing F_sensor(F_Sonar_TRIG,F_Sonar_ECHO,MaxDistance);
  
  float F_Sonar_Error = 0.0;
  float F_Sonar_distance = 0.0;
  float F_Sonar_distance_old = 0.0;

  void read_sonar_sensor(void)   //??????????????? ??????
  {
    R_Sonar_distance = R_sensor.ping_cm()*10.0;
    L_Sonar_distance = L_sensor.ping_cm()*10.0;
    F_Sonar_distance = F_sensor.ping_cm()*10.0;
    if(R_Sonar_distance == 0){R_Sonar_distance = MaxDistance * 10.0;}
    if(L_Sonar_distance == 0){L_Sonar_distance = MaxDistance * 10.0;}
    if(F_Sonar_distance == 0){F_Sonar_distance = MaxDistance * 10.0;}
  }

  void update_sonar_old(void)    //????????? ????????? ????????? ??????
  {
    R_Sonar_distance_old = R_Sonar_distance;
    L_Sonar_distance_old = L_Sonar_distance;
    F_Sonar_distance_old = F_Sonar_distance;
  }
  void update_sonar_error(void)   //????????? ????????? ???????????? ???????????? ?????? ??????
  {
    R_Sonar_Error = R_Sonar_distance - R_Sonar_distance_old;
    L_Sonar_Error = L_Sonar_distance - L_Sonar_distance_old;
    F_Sonar_Error = F_Sonar_distance - F_Sonar_distance_old;
  }

Servo Steeringservo;

int Steering_Angle = NETURAL_ANGLE;

void line_adaptation(void)
{
  int i;
  for (i = 0; i < NPIXELS; i++)
  {
    if (LineSensor_Data[i] >= MAX_LineSensor_Data[i])  MAX_LineSensor_Data[i] = LineSensor_Data[i];
    if (LineSensor_Data[i] <= MIN_LineSensor_Data[i])  MIN_LineSensor_Data[i] = LineSensor_Data[i];
  }
}

void read_line_sensor(void)
{
  int i;

  delayMicroseconds (1);  
  delay(10);              

  digitalWrite (CLKpin, LOW);
  digitalWrite (SIpin, HIGH);
  digitalWrite (CLKpin, HIGH);
  digitalWrite (SIpin, LOW);
  
  delayMicroseconds (1);

  for (i = 0; i < NPIXELS; i++) {
    Pixel[i] = analogRead (AOpin) / 4 ;
    digitalWrite (CLKpin, LOW);
    delayMicroseconds (1);
    digitalWrite (CLKpin, HIGH);
  }

  for (i = 0; i < NPIXELS; i++)
  {
    LineSensor_Data_Adaption[i] = map(Pixel[i], MIN_LineSensor_Data[i], MAX_LineSensor_Data[i], 0, 256);
  }

}

#define threshold_value 60

void threshold(void)
{
  int i;
  for (i = 0; i < NPIXELS; i++)
  {
    if((byte)Pixel[i] >= threshold_value)  LineSensor_Data_Adaption[i] = 255;
    else LineSensor_Data_Adaption[i] = 0;
  }
}

int steer_data = 0;

#define camera_pixel_offset 5

void steering_by_camera(void)
{
  int i;
  long sum= 0;
  long x_sum= 0;
  
  for (i = 0; i < NPIXELS; i++)
  {
    sum +=LineSensor_Data_Adaption[i];
    x_sum += LineSensor_Data_Adaption[i] * i;
  }
  steer_data = x_sum/sum - NPIXELS/2 + camera_pixel_offset;
  steering_control(steer_data*1.25);        

  Serial.println(steer_data);
}

int what=0;

int the=0;

int timer=0;

void setup()
{
  int i;
 
  for (i = 0; i < NPIXELS; i++)
  {
    LineSensor_Data[i] = 0;
    LineSensor_Data_Adaption[i] = 0;
    MAX_LineSensor_Data[i] = 1023;
    MIN_LineSensor_Data[i] = 0; 
  }

  pinMode(SIpin, OUTPUT);
  pinMode(CLKpin, OUTPUT);

  digitalWrite(SIpin, LOW); 
  digitalWrite(CLKpin, LOW); 

#if FASTADC
  
  sbi(ADCSRA, ADPS2);
  cbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);
#endif

  flag_line_adapation = 0;
  Steeringservo.attach(RC_SERVO_PIN);
  Steeringservo.write(NETURAL_ANGLE);
  pinMode(MOTOR_DIR, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT); 

  Serial.begin(115200);

}

void loop()
{

  int i;
 
  line_adaptation();
  read_line_sensor();
  read_sonar_sensor(); 
  
  if(flag == 0)
  {
    motor_control(-1,80);
    threshold();
    steering_by_camera();
    delay(100);
    
    if(L_Sonar_distance+R_Sonar_distance <= 1300)
      {flag=1;}
  }
  else if(flag == 1)
  {
   motor_control(-1,130);
   steering_control(14);
   if(F_Sonar_distance<=1000)
   {
     what++;
   }
   else
    {what=0;}
  
  if(what>=6)
  {
    turn_right();
    delay(400);
    flag=2;
    the=millis();
    what=0;
  }
}
 else if(flag == 2)
 {
   wall_following2();
   if(F_Sonar_distance<=900 && millis()-the>=5000)
  {
    what++;
  }
  else{what=0;}

  if(what>=6)    
  {  turn_right();
    delay(400);
    flag=3;   
  }
 }
 else if(flag == 3)
 {
    motor_control(-1,80);
    threshold();
    steering_by_camera();
    delay(100);
    if(F_Sonar_distance<=400){flag=4;}  
   }
       
 else if(flag == 4) 
 {
    motor_control(0,0);
 }
}