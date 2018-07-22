#include <dht.h>


//#include <DHT.h>
#include <SoftwareSerial.h>
//#include <Adafruit_Sensor.h>


#define tempSensor A2 // Analog Pin sensor is connected to
 
dht DHT;
 

SoftwareSerial BTserial(10,11); // RX | TX

SoftwareSerial mySerial(10, 11);
int lightSensor = A1;                
int gasSensor=A0;

int pir= 6;
int relay=7;                  
const int pinLED = 13;


void setup() {

BTserial.begin(9600);
pinMode(pinLED,OUTPUT);
pinMode(7,INPUT);
  Serial.begin(115200);           
  pinMode(pir,INPUT);
   mySerial.begin(9600);
 // interruptSetup(); 
  }
/*void interruptSetup()

{    

  TCCR2A = 0x02;  // This will disable the PWM on pin 3 and 11

  OCR2A = 0X7C;   // This will set the top of count to 124 for the 500Hz sample rate

  TCCR2B = 0x06;  // DON'T FORCE COMPARE, 256 PRESCALER

  TIMSK2 = 0x02;  // This will enable interrupt on match between OCR2A and Timer

  sei();          // This will make sure that the global interrupts are enable

}*/
void loop() {

//sensorValue = analogRead(sensorPin);

//IMPORTANT: The complete String has to be of the Form: 1234,1234,1234,1234;

//(every Value has to be seperated through a comma (',') and the message has to

//end with a semikolon (';'))

//Serial.print("BPM: ");
float gasval=analogRead(gasSensor);
float lightval=analogRead(lightSensor);
float tempval=analogRead(tempSensor);
if(relayup()==true )
{
Serial.println("gas ");
  Serial.println(gasval);
  delay(1000); // Print value every 1 sec.
   Serial.println("light intensity");
  Serial.println(lightval);
  delay(1000);

  digitalWrite(pinLED,LOW);
    DHT.read11(tempSensor);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
BTserial.print("Gasval=");
BTserial.println(gasval);
BTserial.println(",");

if(gasval>289 && gasval<302)
{
//BTserial.print("Normal");
//BTserial.print(",");

}
BTserial.print("Light Intensity=");
BTserial.println(lightval);
//BTserial.println(",");
if(lightval>30&&lightval<50)
{
BTserial.print("Moderade Increase");
BTserial.print(",");
digitalWrite(pinLED,HIGH);
}
BTserial.print("Temperature and humidity=");
BTserial.println(DHT.temperature);
BTserial.println(DHT.humidity);
//BTserial.println(",");



}
BTserial.print("date=");
BTserial.println("24/5/2018");
//BTserial.println(",");
}
boolean relayup(){
  pinMode(relay,OUTPUT);
int  pirval=digitalRead(pir);
  Serial.println(pirval);
  if(pirval==1)
  {
  digitalWrite(relay,HIGH);
  Serial.println("Motion Detected");
  delay(20);
  }
  else
  {
    digitalWrite(relay,LOW);
    Serial.println("Motion not detected");
}
    return true;
}
