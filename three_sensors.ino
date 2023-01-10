#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //sets up lcd screen

int timer1;
int timer2;
int timer3;

float Time1;
float Time2;

int flag1 = 0;
int flag2 = 0;
int flag3=0;

float d_1 = 0.15; //meters. measure in cm and convert
float d_2 = 0.075;
float d_3;
float d;
float h=0.087;
float d_prime;
float v_1;
float v_2;

int irs_1 = A0;
int irs_2 = A1;
int irs_3 = A2;



void setup(){
  Serial.begin(9600); //set baud rate (standard 9600)
  pinMode(irs_1, INPUT); // set up sensors as input 
  pinMode(irs_2, INPUT);
  pinMode(irs_3,INPUT);
 
  d_1=0.15; //input separation measurements
  d_2 = 0.075;
  d_prime = 0.11;
  d_3=0.10;
  d=d_prime-h;
  
  lcd.init(); // initialize lcd display 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("hello "); // print this to see if its working
  delay(2000);
  lcd.clear();
}

void loop() {
  if (digitalRead(irs_1) == LOW && flag1==0 )  //irs_1 triggered
 {
    
    timer1 = millis(); flag1 =1;
  }
  
  if (digitalRead(irs_2) == LOW && flag2 == 0) // irs_2 triggered 
   {  

  timer2 = millis();
  flag2 = 1;

  }
  if (digitalRead(irs_3==LOW) && flag3==0) // irs_3 triggered first time
  {
  
  flag3=1;
  }
  
  if (flag1==1 && flag2==1){

    Time1=timer2-timer1;
    v_1 = (d)*1000/(Time1); // what is the benefit of having the sensors so far apart?

  }

  if (flag3==1 && digitalRead(irs_3==LOW)) //irs_3 triggered again
  {
    timer3 = millis();
    Time2 = timer2-timer3;
    v_2 = (d_3+d_prime)*1000/(Time2);
    
    }

  lcd.setCursor(0,0); // print v_1 && v_2 (down and up speeds)
  lcd.print(v_2);
  lcd.setCursor(1,0);
  lcd.print(v_1);
  
  delay(2000);
  lcd.clear();
  lcd.print("ready");
  
  
}

  

  
   
  

  
