// C++ code
//
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); //핀의 모드를 결정 
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH); //13번 핀의 출력을 high
  delay(500); // Wait for 1000 millisecond(s)
  Serial.println("LED ON");
  digitalWrite(LED_BUILTIN, LOW); // 13번 핀의 출력을 low
  delay(500); // Wait for 1000 millisecond(s)
}
int main(void)
{