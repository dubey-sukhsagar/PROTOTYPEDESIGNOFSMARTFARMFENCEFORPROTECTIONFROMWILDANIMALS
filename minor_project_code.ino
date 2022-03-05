#include <Stepper.h> // stepper motor
#include <SoftwareSerial.h>
#include <LiquidCrystal.h> // for LCD
#define STEPS 200   // number of stepes of stepper motor
SoftwareSerial mySerial(14,15);//Tx,Rx
LiquidCrystal lcd(48,49,50,51,52,53); // define LCD pin number
Stepper motor(STEPS, 11,10,9,8); // define stepper motor pin number

void setup()
{
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  Serial.begin(9600);
  motor.setSpeed(15);
  lcd.begin(16,2);
    lcd.setCursor(0,0);
  lcd.print(" Smart Electric Fence");
  lcd.setCursor(0,1);
  lcd.print("Mentor-Dr.R.K.Jarial");
  for(int j=0; j<=19 ; j++)
  {
  lcd.scrollDisplayLeft();
  delay(500);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("EED Department");
  lcd.setCursor(0,1);
  lcd.print("NIT Hamirpur");
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  delay(100);
}


void loop ()
{
  int zon1=0, zon2=0,zon3=0,zon4=0,steps=0,b=0;
  zon1= digitalRead(6); // sensing value for zone 1
  zon2= digitalRead(7); // for zone 2
  zon3= digitalRead(5); // for zone 3
  zon4= digitalRead(4); // for zone 4

  if (zon1>0)
  {
    b=1;
    steps= 20;
  }else if (zon2>0)
  {
    b=2;
    steps=10;
  }else if (zon3>0)
  {
    b=3;
    steps=45;
  }else if (zon4>0)
  {
    b=4;
    steps=33;
  }

  if (zon1 || zon2 || zon3 || zon4 >0)
  {
    lcd.setCursor(0,0);
    lcd.print("Intruder inZone");
    lcd.setCursor (15,0);
    lcd.print(b);
    motor.step(steps);
    motor.setSpeed(10);
    delay(100);
    motor.step(-10);
    delay(100);
     for(int i=0 ; i<=20; i++)
      {
        digitalWrite(3,HIGH);
        delay(100);
        digitalWrite(3,LOW);
        delay(100);
      }
    digitalWrite(3,HIGH);
    motor.step(-10);
    motor.step(20);
    delay(100);
    motor.setSpeed(15);
    delay(100);
    digitalWrite(2, HIGH);
    digitalWrite(3,LOW);
    motor.step(-steps);
      delay(10000);
      digitalWrite(3,LOW);
      digitalWrite(2,LOW);
     int k=0, a=0,x=0;
      for(int k=0; k<=50; k++)
      {
        if(zon1 || zon2 || zon3 || zon4 ==1)
        { 
  zon1= digitalRead(6); // sensing value for zone 1
  zon2= digitalRead(7); // for zone 2
  zon3= digitalRead(5); // for zone 3
  zon4= digitalRead(4); // for zone 4 
          x++;
        }
      }
      Serial.println(x);
      if(x>=20)
      {
    SendMessage(b);
    delay(10000);
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Intruder Stuck");
  lcd.setCursor(0,1);
  lcd.print("Message Sent");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("System Active");
      } 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("System Active");  
  }
}

void SendMessage(int asd)
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919882547401\"\r"); // Replace x with mobile number
  delay(1000);
  String string=" Intruder is stucked in Zone ";
 // String string1=" \ntemp is(c):";
 // String string2=" \n temp rising is(c):";
  
String  final_string=string+ asd;
  mySerial.println(final_string);// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}












