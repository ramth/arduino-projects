#include <LiquidCrystal.h>

/*
Hook a serial resistor(100k) and unknown capacitor to digital pin 10 and ground.
After 10s of starting the arduino, it will print the capacitor value (in uF ?)
*/
unsigned long cap_charge_time = 0;
unsigned long start_time = 0;
double cap_value = 0;
//LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);
boolean start = true;
boolean display_flag = false;


//use with 100k resistor
//high triggered when 0.6 of Vcc
void setup(){
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  attachInterrupt(0,dig_high,RISING);
  
 /lcd.begin(16,2);
}

void loop() {
delay(10000);

  if(start) {

    digitalWrite(10,HIGH);
    start_time = millis();
  }
  
  if(display_flag && start) {

    cap_value = (double)cap_charge_time*1.3/(90.9876);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print((int)cap_value);
    Serial.println((int)cap_charge_time);
    display_flag = false;
    start = false;
    
  }
  
}

void dig_high() {
  cap_charge_time = millis()- start_time;
  display_flag = true;
  digitalWrite(10,LOW);
}

