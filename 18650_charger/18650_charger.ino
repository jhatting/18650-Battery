/*
 * Arduino 18650 Battery Gauge
 *
 * learnelectronics
 * 13 JUL 2017
 *
 * www.youtube.com/c/learnelectronics
 */
 
#include <LiquidCrystal.h>                    //we need the library for the lcd display
 
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);      //we ned to tell the arduino which pins to use with the lcd
 
float rawV = 0.0;                             //a variable with a decimal point to hold battery voltage
int batC = 0;                                 //a variable with no decimal point to hold battery percentage
int graph = 0;                                //a variable with no decimal point to hold the value for the graph
 
void setup() {                                //only runs when the Arduino is powered on reset
 
  lcd.begin(16, 2);                           //start lcd with 16 columns & 2 rows
  lcd.clear();                                //clear any garbage from screen
  pinMode(A0,INPUT);                          //we will use analog pin 0 to read voltage from 18650
 
}
 
void loop() {                                 //runs over and over
 
  rawV = (analogRead(A0)*4.98)/1024;          //figure out the battery voltage (4.98 is the actual reading of my 5V pin)
 
 
                                              //some logic to set values
                                             
  if (rawV <3.6){                             //battery @ 3.5V or less
  batC = 0;                                   //% = 0
  graph = 0;                                  //# of graph segments to light
  }
 
if(rawV > 3.5 && rawV < 3.7){                 //battery @ 3.6V
  batC = 2;
  graph = 1;
  }
 
if (rawV > 3.6 && rawV < 3.8){                //battery @ 3.7V
  batC = 12;
  graph = 4;
  }
 
if (rawV > 3.7 && rawV <3.9){                 //battery @ 3.8V
  batC = 42;
  graph = 7;
  }
 
if (rawV > 3.8 && rawV < 4.0){                //battery @ 3.9V
  batC = 62;
  graph = 10;
  }
 
if (rawV > 3.9 && rawV < 4.1){                //battery @ 4.0V
  batC = 79;
  graph = 13;
  }
 
if (rawV > 4.0 && rawV < 4.2){                //battery @ 4.1V
  batC = 81;
  graph = 15;
  }
 
if (rawV > 4.19){                             //battery @ 4.2V
  batC = 100;
  graph = 16;
  }
 
 
                                              //send all the values to the lcd
 
  lcd.setCursor(0,0);
  lcd.print("V:");
  lcd.setCursor(3,0);
  lcd.print(rawV);
  lcd.setCursor(10,0);
  lcd.print("%:");
  lcd.setCursor(13,0);
  lcd.print(batC);
  lcd.setCursor(0,1);
  for(int m = 0; m < graph; m++){             //draw the graph (light up m number of segments)
    lcd.write(255);
  }
 
delay(1000);                                  //wait one second to stabilize
 
lcd.clear();                                  //clear previous data from lcd
 
 
 
}
