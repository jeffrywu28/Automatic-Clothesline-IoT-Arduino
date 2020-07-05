#include<Servo.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
Adafruit_ADS1115 ads(0x48);
Servo myservo;
char auth[] = "";
char ssid[] = "ASUS_X01BD";
char pass[] = "xxxxx";
int16_t adc0, adc1;
int sensorValue = 0;
const int capteur_D = 4;
int val_analogique;
int c;
int w;
int q;

BlynkTimer timer;
void myTimerEvent()
{
  sensorValue = analogRead(A0);
  Blynk.virtualWrite(V5, q);
  Blynk.virtualWrite(V1, w);
  
}
BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); 
  c=pinValue;
}

void setup()
{
  pinMode(capteur_D, INPUT);
  pinMode(w, INPUT);
  Serial.begin(9600);
  myservo.attach(2);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
  ads.begin();
}

void loop()
{
  q = adc0/16;
  w = adc1/16;
  val_analogique=analogRead(w); 
  sensorValue = analogRead(q);
  adc0 = ads.readADC_SingleEnded(0); 
  adc1 = ads.readADC_SingleEnded(1);
  if(q>=c && w>=c) 
  {
    Serial.print("Slider value : ");
    Serial.println(c);
    Serial.println("Digital value : Cloudly & Dry"); 
    delay(10);
    myservo.write(105);       
    delay(15);
  }
  else if(q<c && w<=c)
  {
    Serial.print("Slider value : ");
    Serial.println(c);
    Serial.println("Digital value : Hot & Rain");
    delay(10);
    myservo.write(105); 
    delay(15);        
  }
  else if(q>=c && w<c) 
  {
    Serial.print("Slider value : ");
    Serial.println(c);
    Serial.println("Digital value : Cloudly & Rain"); 
    delay(10);
    myservo.write(105);       
    delay(15);
  }
  else if(q<c && w>=c)
  {
    Serial.print("Slider value : ");
    Serial.println(c);
    Serial.println("Digital value : Hot & Dry");
    delay(10);
    myservo.write(10); 
    delay(15);        
  }
   
  Serial.print("Analog value(Light sensor) : ");
  Serial.println(q);
  Serial.print("Analog value(Rain sensor) : ");
  Serial.println(w);
  Serial.println(" ");
  delay(1000);
  Blynk.run();
  timer.run();
}
