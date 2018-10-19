/*
 This project was build ontop of a sketch and library created
 and provided by the people below.

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



/*-------------------------------------SETUP-----------------------------------------*/
void setup() {
   
  /*The following two lines set the cursor to home 
  and print the welcome message*/
  lcd.begin(16, 2);            
  lcd.print("Set a time");
  
  /*Turn on the serial brinter at a 9600 baud*/
  Serial.begin(9600);         
  
}


/*--------------------------------------LOOP-----------------------------------------*/
void loop() {
  
  /*Uncomment the lines below to turn on the serial printer debugger*/
  boolean printSerial = true;  // turn true if you want to have serial monitor print voltages on A5-A1
  int serialTimer = 750;        //uncomment for serial printing

  /*This is the threshhold for */
  int buttonVoltage = 1000;      //when button is pressed it shows a voltage over 1000
  int refreshRate = 250;         //rate to wait between button presses and screen updates
  
  /*When the fifth button (set brew time button) is pressed*/
  if(analogRead(A1) > buttonVoltage){
    
    /*initalize values default to 12:00a*/
    boolean brewTimeSet = false;  
    int hour = 12;
    int minute = 00;
    char amPm = 'a';
    
    /*This loop will run until the brew time is set*/
    while(!brewTimeSet){
     
      clearLCDScreen();                              //clear the LCD screen
      displaySetTimeScreen(hour, minute, amPm);      //display the current set time screen
         
      boolean confirmTime = false;
      
      /*This loop runs until the user confirms setTime is correct*/
      while(!confirmTime){
        
        
        /*If the minus hour button is hit*/
        if(analogRead(A5) > buttonVoltage){
          
          /*If we are at 1, we have to "roll over" back to twelve*/
          if(hour == 1){
            
            hour = 12;                   //roll clock over from 1 to 12                 
            
          }
          
          else{
           
            hour -= 1;                  //minus an hour
            
            /*When a clock changes between 11 and 12, the am becomes pm and visaversa*/
            if(hour == 11){            
               /*If statement will roll am over to pm 
              and visa versa when clock rolls over*/
              if(amPm == 'a'){             //if its am, switch it to pm
                amPm = 'p';
              }
              else{
                amPm = 'a';                //pm switches to am
              } 
            }
            
          }          
        }
        
        /*If the plus hour button is hit*/
        if(analogRead(A4) > buttonVoltage){
          if(hour == 12){
            
            hour = 1;                    //roll clock over from 12 to 1
           
          }
          else{
            hour += 1;
            
            if(hour == 12){
              /*If statement will roll am over to pm 
              and visa versa when clock rolls over*/
              if(amPm == 'a'){             //if its am, switch it to pm
                amPm = 'p';
              }
              else{
                amPm = 'a';                //pm switches to am
              }
            }
            
          }          
        }
        
        /*If the minus minute button is hit*/
        if(analogRead(A3) > buttonVoltage){
          if(minute == 0){
            minute = 50;
          }
          else{
            minute -= 10;
          }          
        }
        
        /*If the plus minute button is hit*/
        if(analogRead(A2) > buttonVoltage){
          if(minute == 50){
            minute = 0;
          }
          else{
            minute += 10;
          }          
        }
        
        /*If the confirm minute button is hit*/
        if(analogRead(A1) > buttonVoltage){
          Serial.print("Exit loop?");
          confirmTime = true;
        }
        
        delay(refreshRate);
        displaySetTimeScreen(hour, minute, amPm); 
        
      }       
    
      
      String days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
      String day = days[0];
      
      boolean confirmDay = false;
      while(!confirmDay){
        
        int currentDay = 0;
        
        /*If the confirm minute button is hit*/
        if(analogRead(A5) > buttonVoltage){
      
          if(currentDay == 0){
           currentDay = 6; 
          }
          else{
            currentDay -= 1;
          }
          
          day = days[currentDay];
          
        }
        
        
        /*If the confirm minute button is hit*/
        if(analogRead(A4) > buttonVoltage){
          
          if(currentDay == 6){
           currentDay = 1; 
          }
          else{
            currentDay += 1;
          }
          
          day = days[currentDay];
        }
        
        
        /*If the confirm minute button is hit*/
        if(analogRead(A1) > buttonVoltage){
          confirmDay = true;
        }
        
        delay(refreshRate);
        displaySetTimeScreen(hour, minute, amPm); 
        
      }
      
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
    serialDebug(serialTimer);
  }
  
  delay(1000);
  
}

void displaySetDayScreen(String day){
  
    /*This will be displayed on the bottom row*/
    String setDayBottomLine = "***edit day***";
    
    
    String setDayTopLine = "";
    
    int dayLength = day.length();
    
    
    if(dayLength == 6){
      
      setDayTopLine += day;
    }
    else if(dayLength == 7){
      
    }
    else if(dayLength == 8){
      
    }
    else{
      
    }
  
  
  
  
}

void displaySetTimeScreen(int hour, int minute, char amPm){
  
    /*This will be displayed on the bottom row*/
    String setTimeBottomLine = "***edit values***";
    
  
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
    
    Serial.print("hour is ");
    Serial.print(hour);
    Serial.print("\n");
    Serial.print("minute is ");
    Serial.print(minute);
    Serial.print("\n");
    Serial.print("amPm is ");
    Serial.print(amPm);
    Serial.print("\n");
    printToLCD(setTime, setTimeBottomLine);              //Display the current brew time       
  
}


void printToLCD(String top, String bottom){
  
  clearLCDScreen();
  lcd.setCursor(0, 0);               //Set cursor to top left
  lcd.print(top);     //clear LCD
  lcd.setCursor(0, 1);               //Set cursor to top left
  lcd.print(bottom);     //clear LCD
  lcd.setCursor(0,0);                //Return the cursor to home
}

void clearLCDScreen(){
  
    /*Next 5 lines clears the screen and resets the cursor to home*/
    lcd.setCursor(0, 0);               //Set cursor to top left
    lcd.print("                ");     //clear LCD
    lcd.setCursor(0, 1);               //Set cursor to top left
    lcd.print("                ");     //clear LCD
    lcd.setCursor(0,0);                //Set the cursor to home
    
}

void serialDebug(int delayTime){
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
    delay(delayTime);
}

