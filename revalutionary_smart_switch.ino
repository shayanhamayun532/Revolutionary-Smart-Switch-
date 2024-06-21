#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
SoftwareSerial btSerial(14, 13); // RX, TX

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6_E9gYZWb"
#define BLYNK_TEMPLATE_NAME "Revolutionary Switch"
#define BLYNK_AUTH_TOKEN "oZKOvf_SpULdelKD2PfhTrms-ZNJ5gdk"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//#include <SoftwareSerial.h>    
//SoftwareSerial mySerial(2, 3); // RX, TX
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "nouman";
char pass[] = "123456789";

const int button_1 = 5;
const int button_2 = 4;

bool flag1 = false;
bool flag2 = false;

char input_value;
unsigned long lastmillis; //variable that will store current value of millis()function

BlynkTimer timer;

 BLYNK_WRITE(V0) { if(param.asInt()==1) { Serial.println('x'); myservo.write(100);
 } else {  Serial.println('y');  myservo.write(0);}}
 //BLYNK_WRITE(V1) { if(param.asInt()==1) { Serial.println('p'); } else { Serial.println('z'); }}
 

  
void setup() {
  Serial.begin(9600);   // Serial monitor
   Serial.println("Initializing ESP-12E...");
  delay(1500);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  myservo.attach(12);  // attaches the servo on pin 9 to the servo object
      myservo.write(100);
delay(500);
      myservo.write(0);
delay(500);

  pinMode(button_1,INPUT_PULLUP);
  pinMode(button_2,INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
  delay(1000);  

   btSerial.begin(9600); // ESP8266 communication
  delay(1000);

  }

void loop() {

  buttonRead();
  
   if((millis()-lastmillis) >= 1000)
     {
      bt_App(); 
      lastmillis=millis();
     }

     
  Blynk.run();
  timer.run(); 
 
}


void buttonRead()
{
  int buttonState1 = digitalRead(button_1);
  int buttonState2 = digitalRead(button_2);

  if (buttonState1 == LOW && !flag1) {
    flag1 = true;
    flag2 = false;
    Serial.println("Switch ON");
    Blynk.virtualWrite(V1,  LOW); 

  }

  if (buttonState2 == LOW && !flag2) {
    flag1 = false;
    flag2 = true;
    Serial.println("Switch OFF");
        Blynk.virtualWrite(V1,  HIGH); 

   }
}

void bt_App()
{
   if (btSerial.available()>0) { 
 
     input_value = btSerial.read();
     //Serial.println(input_value);
    // delay(200);
  }

   if (input_value == 'a')
   {
      btSerial.write("Switch = 1");
      Serial.println(" bt on ");
      //delay(300);   
      myservo.write(100);   
      input_value=0;
   }

   else if (input_value == 's')
   {
      btSerial.write("Switch = 0");
       Serial.println(" bt on ");
      //delay(300); 
      myservo.write(0);
      input_value=0;

   }
}
