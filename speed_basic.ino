#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int timer1;
int timer2;

float Time;

int tracker1 = 0;
int tracker2 = 0;

float distance = 4.75;
float speed;

int ir_s1 = A0;
int ir_s2 = A1;



void setup(){
  Serial.begin(9600);
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);
 

  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
//  2
  
  delay(2000);
  lcd.clear();
}

void loop() {
if(digitalRead (ir_s1) == LOW && tracker1==0){timer1 = millis(); tracker1=1;}

if(digitalRead (ir_s2) == LOW && tracker2==0){timer2 = millis(); tracker2=1;}

if (tracker1==1 && tracker2==1){
     if(timer1 > timer2){Time = timer1 - timer2;}
else if(timer2 > timer1){Time = timer2 - timer1;}
 distance = distance*0.0254;
 Time=Time/1000;//convert millisecond to second
 speed=(distance/Time);//v=d/t
 

}

if(speed==0){ 
lcd.setCursor(0, 1); 
if(tracker1==0 && tracker2==0){lcd.print("waiting");}
                    else{lcd.print("Searching...    ");} 
}
else{
    lcd.clear(); 
    lcd.setCursor(0, 0); 
    lcd.print("Speed:");
    lcd.print(speed,4);
    lcd.print("m/s  ");
    lcd.setCursor(0, 1); 
  
              
    delay(3000);
    
    
    speed = 0;
    tracker1 = 0;
    tracker2 = 0;    
 }
}
