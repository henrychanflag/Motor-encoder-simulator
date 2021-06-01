//Motor with Encoder Simulator V2.0
//By Angus Wong, 13May2021
//Use Pro-Mini 3.3V, 8MHz
//Convert the DC input voltage to an encoder output (Phase A and Phase B)
//Frequency is from 100Hz to 1000Hz, inversely proportional to DC input
//No encoder pulse if duty cycle is too low
//Add artificial variation of +/-5% to the motor speed

#define DCinput A0
#define DCinput1 A1
#define variation A2
#define encoder_out_A 13
#define encoder_out_B 12
#include <neotimer.h>

Neotimer mytimer(200); // Set timer interrupt to 500ms
int adc = 0;
int adc1 = 1;
int adc2 = 512;
long delay_time = 0;
int fraction = 100;


void setup() {
  // put your setup code here, to run once:
  pinMode(encoder_out_A,OUTPUT);
  pinMode(encoder_out_B,OUTPUT);
  digitalWrite(encoder_out_A, HIGH);
  digitalWrite(encoder_out_B, HIGH);
  Serial.begin(115200);

  //only read once after power up reset
  //define the variation fraction
  adc2 = analogRead(variation); 
  fraction = map(adc2, 0, 1024, 95, 105);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Read DC voltage and update encoder frequency every 0.2s
  if (mytimer.repeat()){
    adc = analogRead(DCinput);
    adc1 = analogRead(DCinput1);
    //Serial.println(adc);
    //Serial.println(adc1);
  }
  if (adc>1000 && adc1>1000){ //Encoder idle if PWM duty cycle is too low
    digitalWrite(encoder_out_A, HIGH);
    digitalWrite(encoder_out_B, HIGH);
  }
  else if (adc < 1000){
    delay_time = map(adc, 60,1000,300,5000);// map to 100Hz, 1000Hz
    delay_time = delay_time * fraction/100;
    //Serial.println(delay_time);
    digitalWrite(encoder_out_A, LOW);
    digitalWrite(encoder_out_B, LOW);
    delayMicroseconds(delay_time/2);//A=0, B=0
  
    digitalWrite(encoder_out_A, HIGH);
    digitalWrite(encoder_out_B, LOW);
    delayMicroseconds(delay_time/2);//A=1, B=0
  
    digitalWrite(encoder_out_A, HIGH);
    digitalWrite(encoder_out_B, HIGH);
    delayMicroseconds(delay_time/2);//A=1, B=1
  
    digitalWrite(encoder_out_A, LOW);
    digitalWrite(encoder_out_B, HIGH);
    delayMicroseconds(delay_time/2);//A=0, B=1
  }
  
  else {
    delay_time = map(adc1, 60,1000,300,5000);// map to 100Hz, 1000Hz
    delay_time = delay_time * fraction/100;
    //Serial.println(delay_time);
    digitalWrite(encoder_out_B, LOW);
    digitalWrite(encoder_out_A, LOW);
    delayMicroseconds(delay_time/2);//A=0, B=0
  
    digitalWrite(encoder_out_B, HIGH);
    digitalWrite(encoder_out_A, LOW);
    delayMicroseconds(delay_time/2);//A=0, B=1
  
    digitalWrite(encoder_out_B, HIGH);
    digitalWrite(encoder_out_A, HIGH);
    delayMicroseconds(delay_time/2);//A=1, B=1
  
    digitalWrite(encoder_out_B, LOW);
    digitalWrite(encoder_out_A, HIGH);
    delayMicroseconds(delay_time/2);//A=1, B=0
  }
  
} 
