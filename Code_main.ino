#define BLYNK_PRINT Serial
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


char auth[] = "4ersp_A9Lv-Uc8fR1CiEZk0ZzEM6d-4i";

char ssid[] = "Gwyndolyn.exe-2.4G";
char pass[] = "Sbz45370";

///////motor///////
int MotorL = 26;
int MotorR = 27;
int MotorL2 = 32;
int MotorR2 = 33;
int enablePin = 14;
int enablePin2 = 25;
///////////////////

// Setting PWM properties
const int freq = 30000;
const int freq2 = 30000;
const int pwmChannel = 0;
const int pwmChannel2 = 1;
const int resolution2 = 8;
const int resolution = 8;
int dutyCycle;

void setup()
{
  
  Blynk.begin(auth, ssid, pass, "103.253.73.204", 8080);

  //-------MOTOR------------
  pinMode(MotorL, OUTPUT);
  pinMode(MotorR, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  //------------------------

  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  ledcSetup(pwmChannel2, freq2, resolution2);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enablePin, pwmChannel);
  ledcAttachPin(enablePin2, pwmChannel2);
  
  Serial.begin(9600);

}

//โค้ดพัดลม ----------------------
BLYNK_WRITE(V1){
 if(param.asInt()==1){
  dutyCycle = 200;
  ledcWrite(pwmChannel, dutyCycle); 
  }else if(param.asInt()==0){
  dutyCycle = 0;
  ledcWrite(pwmChannel, dutyCycle);
  }
 }
 //-----------------------------

 
 //โค้ด gate --------------------
 BLYNK_WRITE(V2){
  if(param.asInt()==1){
  digitalWrite(MotorL2, 1);
  digitalWrite(MotorR2, 0);
  dutyCycle = 150;
  ledcWrite(pwmChannel2, dutyCycle); 
  delay(3000);
  dutyCycle = 0;
  ledcWrite(pwmChannel2, dutyCycle); 
 }else if(param.asInt()==0){
  digitalWrite(MotorL2, 0);
  digitalWrite(MotorR2, 1);
  dutyCycle = 150;
  ledcWrite(pwmChannel2, dutyCycle); 
  delay(3000);
  dutyCycle = 0;
  ledcWrite(pwmChannel2, dutyCycle); 
 }
 }
//----------------------------

void loop(){
  
  //----------------------
  digitalWrite(MotorL, 1);
  digitalWrite(MotorR, 0);
  digitalWrite(MotorL2, 0);
  digitalWrite(MotorR2, 1);
  //----------------------
  
  Blynk.run();
}
