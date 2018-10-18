//www.elegoo.com
//2016.06.13

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  
  int serialTimer = 0;         //uncomment for serial printing
  
  Serial.begin(9600);         //uncomment this line for serial print to be activated
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("humble beginings");
  
}

void loop() {
  
  boolean printSerial = false; // turn true if you want to have serial monitor print voltages on A5-A1
  int buttonVoltage = 950;     //when button is pressed it shows a voltage over 1000
  
  /*If the first button is pressed*/
  if(analogRead(A5) > buttonVoltage){
    
    // set up the LCD's number of columns and rows:
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("                ");
    
    
    // set up the LCD's number of columns and rows:
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("Brew Thur 9:00p");
    
  }
  
  /*If the second button is pressed*/
  if(analogRead(A4) > buttonVoltage){
    // set up the LCD's number of columns and rows:
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("                ");
    
    
    // set up the LCD's number of columns and rows:
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("Hi Brandon!");
    
  }
  
  /*If the fifth button is pressed*/
  if(analogRead(A1) > buttonVoltage){
    
    boolean brewTimeSet = false;
    int hour = 12;
    int minute = 00;
    char amPm = 'a';
    
    /*This loop will run until the brew time is set*/
    while(!brewTimeSet){
     
      /*Next 5 lines clears the screen and resets the cursor to home*/
      lcd.setCursor(0, 0);               //Set cursor to top left
      lcd.print("                ");     //clear LCD
      lcd.setCursor(0, 1);               //Set cursor to top left
      lcd.print("                ");     //clear LCD
      lcd.setCursor(0,0);                //Set the cursor to home 
      
      /*The next thre lines builds the brewTime to print to screen*/
      String setTime = "Set Time  ";
      setTime += hour;
      setTime += ":";
      
      /*This adds 00 if the minute is not 10,20,30,40, or 50*/
      if(minute == 0){
        setTime += "00";
      }
      else{
        setTime += minute;
      }
      
      setTime += amPm;                 //append the am or pm char
      
      lcd.print(setTime);              //Display the current brew time        
      
      boolean confirm = false;
      
      /*This loop runs until the user confirms setTime is correct*/
      while(!confirm){
        
        
      }
      
      
      
      
      
      delay(1000);
      
    }
    
    // set up the LCD's number of columns and rows:
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("                ");
    
    
    // set up the LCD's number of columns and rows:
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("Brew Thur 9:00p");
    
  }
  
  //Serial printing for reading pins and things from board
  if(printSerial == true){
    Serial.print("A5 voltage is");
    Serial.println(analogRead(A5));
    Serial.print("A4 voltage is");
    Serial.println(analogRead(A4));
    Serial.print("A3 voltage is");
    Serial.println(analogRead(A3));
    Serial.print("A2 voltage is");
    Serial.println(analogRead(A2));
    Serial.print("A1 voltage is");
    Serial.println(analogRead(A1));
    
    Serial.println("\n");
  }
  
 
  delay(1000);
  
}

