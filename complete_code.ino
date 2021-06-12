const int IN1 = 6;
const int IN2 = 7;
int pwmPin = 9;
const int IRINPUT=11;
int val;
int status=false;
boolean received = false;
char str[15];  
int i = 0;
int value = 0;
int PWM_value = 0;
//---------------------------//
char number[] = "+916354999129"; 
//---------------------------//
void setup()
{
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  
  pinMode(IRINPUT,INPUT);
  analogWrite(pwmPin, 0);
  delay(10000);
  /*delay(20000);
  delay(20000);*/
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.print("AT+CMGS=");
  Serial.print("\"");
  Serial.print(number);
  Serial.println("\"");
  delay(1000);
  Serial.println("System is Ready.");
  delay(1000);
  Serial.println((char)26);
  delay(1000);
}

void loop()
{
  if (received == true)
  {
    if (str[0] == 'r' || str[0] == 'R')
    {
      reverse();
    }
    if (str[0] == 'n' || str[0] == 'N')
    {
      normal();
    }
    value = (str[1] - 0x30) * 100 + (str[2] - 0x30) * 10 + (str[3] - 0x30);
    analogWrite(pwmPin, value);
  }
  received = false;
  i = 0;
}

void serialEvent()
{
  while (Serial.available())
  {
    if (Serial.find("/"))
    {
      delay(1000);
      while (Serial.available())
      {
        char Buffer = Serial.read();
        str[i++] = Buffer;
        if (Buffer == '/')
        {
          received = true;
          return;
        }
      }
    }
  }
}

void normal()
{
   Serial.println("Bhai forward ma jay che!!!!!");
   val=digitalRead(IRINPUT);
   Serial.println(val);
   if(val==HIGH)
   {
    if(status==false)
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      status=true;
    }
    normal();
   }
   else
   {
      if(status==true)
      {
        delay(3000);
        stopmottorforopen();
      }
      else
      {
        alreadyopenmsg();
      }
      
   }
}

void reverse()
{
  Serial.println("Bhai revese ma ave che!!!!!");
   val=digitalRead(IRINPUT);
   Serial.println(val);
   if(val==LOW)
   {
    if(status==false)
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      status=true;
    }
    reverse();
   }
   else
   {
      if(status==true)
      {
        delay(10000);
        stopmottorforclose();
      }
      else
      {
        alreadyclose();
      }
      
   }
  
}

void stopmottorforclose()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  status=false;
  Serial.println("have motor off!");
  Serial.println("AT\r");
  delay(1000);
  Serial.println("AT+CMGF=1\r");
  delay(1000);
  Serial.println("AT+CMGS=\"+916354999129\"\r");
  delay(1000);
  Serial.println("Door open");
  delay(1000);
  Serial.println((char)26);
  delay(100);
  
}

void stopmottorforopen()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  status=false;
  Serial.println("have motor off!");
  Serial.println("AT\r");
  delay(1000);
  Serial.println("AT+CMGF=1\r");
  delay(1000);
  Serial.println("AT+CMGS=\"+916354999129\"\r");
  delay(1000);
  Serial.println("Door closed");
  delay(1000);
  Serial.println((char)26);
  delay(100);
}

void alreadyopenmsg()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  status=false;
  Serial.println("have motor off!");
  Serial.println("AT\r");
  delay(1000);
  Serial.println("AT+CMGF=1\r");
  delay(1000);
  Serial.println("AT+CMGS=\"+916354999129\"\r");
  delay(1000);
  Serial.println("Door is already open");
  delay(1000);
  Serial.println((char)26);
  delay(100);
}

void alreadyclose()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  status=false;
  Serial.println("have motor off!");
  Serial.println("AT\r");
  delay(1000);
  Serial.println("AT+CMGF=1\r");
  delay(1000);
  Serial.println("AT+CMGS=\"+916354999129\"\r");
  delay(1000);
  Serial.println("Door is already closed");
  delay(1000);
  Serial.println((char)26);
  delay(100);
}
