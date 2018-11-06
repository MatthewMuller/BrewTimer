/*
	This project uses the open source LCD library that is compatable with a 1602 LCD screen.
	http://www.arduino.cc/en/Tutorial/LiquidCrystal

	The rest of this project was created by Matthew Muller. It is open source and can be used 
	however you see fit. You can find this project at the link below.

		https://github.com/mmuller914/BrewTimer

*/


// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);



/*-------------------------------------SETUP-----------------------------------------*/
void setup() {
     
    /*The following two lines initialize the LCD and print the welcome message*/
    lcd.begin(16, 2);                        
    lcd.print("Set a time");
    
    /*These initalize the pins for the buttons*/
    pinMode(2, INPUT);                              //hour/day down button
    pinMode(3, INPUT);                              //hour/day up button
    pinMode(4, INPUT);                              //minute down button
    pinMode(5, INPUT);                              //minute up button
    pinMode(6, INPUT);                              //set button button
     
    
    /*Turn on the serial brinter at a 9600 baud*/
    Serial.begin(9600);                 
    
}


/*--------------------------------------LOOP-----------------------------------------*/
void loop() {
    
    /*Uncomment the lines below to turn on the serial printer debugger*/
    boolean printSerial = false;                // turn true if you want to have serial monitor print voltages on A5-A1
    int serialTimer = 750;                      //uncomment for serial printing

    /*This is the threshhold for */
    int buttonVoltage = 1000;                   //when button is pressed it shows a voltage over 1000
    int refreshRate = 250;                      //rate to wait between button presses and screen updates
    int pauseTime = 2000;                       //Pause time variable when program is set to pause
    
    /*initalize values default to 12:00a*/ 
    int hour = 12;
    int minute = 00;
    char amPm = 'a';
    
    boolean runProgram = true;
    
    while(runProgram){
        
        
        /*When the fifth button (set brew time button) is pressed*/
        if(digitalRead(6) == HIGH){
            
            boolean brewTimeSet = false; 
            
            /*This loop will run until the brew time is set*/
            while(!brewTimeSet){
             
                clearLCDScreen();                                       //clear the LCD screen
                displaySetTimeScreen(hour, minute, amPm);               //display the current set time screen
                     
                boolean confirmTime = false;
                
                delay(pauseTime);                                       //let the voltage reads over the buttons die
                
                /*This loop runs until the user confirms setTime is correct*/
                while(!confirmTime){
                    
                    /*If the minus hour button is hit*/
                    if(digitalRead(2) == HIGH){
                        
                        /*If we are at 1, we have to "roll over" back to twelve*/
                        if(hour == 1){
                            
                            hour = 12;                                  //roll clock over from 1 to 12                                 
                            
                        }
                        else{
                         
                            hour -= 1;                                  //minus an hour
                            
                            /*When a clock changes between 11 and 12, the am becomes pm and visaversa*/
                            if(hour == 11){                        
                                 
                                /*If statement will roll am over to pm and visa versa when clock rolls over*/
                                if(amPm == 'a'){                        
                                    amPm = 'p';
                                }
                                else{
                                    amPm = 'a';                                
                                } 
                            }
                            
                        }
     
     
                        delay(refreshRate);                             //Pause the system so buttons debase
                        displaySetTimeScreen(hour, minute, amPm);       //Update the screen with the new time
                     
                    }
                    
                    /*If the plus hour button is hit*/
                    if(digitalRead(3) == HIGH){
                        if(hour == 12){
                            
                            hour = 1;                                   //roll clock over from 12 to 1
                         
                        }
                        else{
                            hour += 1;
                            
                            if(hour == 12){

                                /*If statement will roll am over to pm and visa versa when clock rolls over*/
                                if(amPm == 'a'){                        //if its am, switch it to pm
                                    amPm = 'p';
                                }
                                else{
                                    amPm = 'a';                         //pm switches to am
                                }
                            }
                            
                        } 
     
                        delay(refreshRate);                             //Pause the system so buttons debase
                        displaySetTimeScreen(hour, minute, amPm);       //Update the screen with the new time
                     
                    }
                    
                    /*If the minus minute button is hit*/
                    if(digitalRead(4) == HIGH){
                        if(minute == 0){
                            minute = 50;
                        }
                        else{
                            minute -= 10;
                        }     
         
         
                        delay(refreshRate);                             //Pause the system so buttons debase
                        displaySetTimeScreen(hour, minute, amPm);       //Update the screen with the new time     
                        
                    }
                    
                    /*If the plus minute button is hit*/
                    if(digitalRead(5) == HIGH){
                        if(minute == 50){
                            minute = 0;
                        }
                        else{
                            minute += 10;
                        }
    
                        delay(refreshRate);                             //Pause the system so buttons debase
                        displaySetTimeScreen(hour, minute, amPm);       //Update the screen with the new time                    
                    }
                    
                    /*If the confirm minute button is hit*/
                    if(digitalRead(6) == HIGH){
                        delay(500);                                     //This gives the user a chance to stop pressing the button
                        confirmTime = true;
                    }
                    
                    
                    
                }             
            
                /*Array containing all the days of the week*/
                String days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
                String day = days[0];                                   //This is the current date
                
                boolean confirmDay = false;
                int currentDay = 0;
                
                delay(refreshRate);                                     //Pause the system so buttons debase
                displaySetDayScreen(day);                               //Update the display with the new day
                
                while(!confirmDay){
                    
                    /*If the minus day button is hit*/
                    if(digitalRead(2) == HIGH){
                
                        if(currentDay == 0){
                         currentDay = 6; 
                        }
                        else{
                            currentDay -= 1;
                        }
                        
                        day = days[currentDay];
                        
                        delay(refreshRate);                             //Pause the system so buttons debase
                        displaySetDayScreen(day);                       //Update the display with the new day
                        
                    }
                    
                    
                    /*If the plus day button is hit*/
                    if(digitalRead(3) == HIGH){
                        
                        if(currentDay == 6){
                         currentDay = 0; 
                        }
                        else{
                            currentDay += 1;
                        }
                        
                        day = days[currentDay];
                        
                        delay(refreshRate);                             //Pause the system so buttons debase
                        displaySetDayScreen(day);                       //Update the display with the new day
                        
                    }
                    
                    
                    /*If the confirm minute button is hit*/
                    if(digitalRead(6) == HIGH){
                        confirmDay = true;
                    }
                    
                }
                
                
                
                brewTimeSet = true;                                     //both the time and date have been set. Break loop
                
                delay(refreshRate);                                     //Pause the system so buttons debase
                displayBrewTime(day, hour, minute, amPm);               //Update the display with the new day
                
            }
            
            
            
        }
        
        
        
        //Serial printing for reading pins and things from board
        if(printSerial == true){
            serialDebug(serialTimer);
        }
        
        delay(1000);
        
    }
    
}

void displayBrewTime(String day, int hour, int minute, char amPm){
    
        String topLine = "Last Brewed";                 //This will be our top line displayed
        String bottomLine = "";                         //Initialize the bottom string
        
        bottomLine += hour;                             //Add the hour
        bottomLine += ":";                              //Append the : for formatting the time
        
        /*This adds 00 if the minute is set to 0 because time is red as 00*/
        if(minute == 0){
            bottomLine += "00";
        }
        else{
            bottomLine += minute;
        }
        
        bottomLine += amPm;                             //append the am or pm char
        
        bottomLine += " ";                              //Space between time and day                                        
        bottomLine += day;                              //Add the day
        
        printToLCD(topLine, bottomLine);                //Print the strings to the display
    
}

void displaySetDayScreen(String day){
    
        /*This will be displayed on the bottom row*/
        String topLine = "Day brewed?";
        
        
        String setDay = "        ";                     //White space before Day on screen
        
        setDay += day;                                  //Add the day to the string
        printToLCD(topLine, setDay);                    //Print the strings to the display
        
        
    
}

void displaySetTimeScreen(int hour, int minute, char amPm){
    
        /*This will be displayed on the bottom row*/
        String topLine = "Time Brewed?";
        
    
        /*The next thre lines builds the brewTime to print to screen*/
        String setTime = "          ";
        
        /*Formatting. Adds a space if number is 1 - 9 so it lines up with the 10 - 12*/
        if(hour < 10){
            setTime += " ";
        }
        
        setTime += hour;                                //Add the hour to the string
        setTime += ":";                                 //Add the : sperating minutes and hours
        
        /*This adds 00 if the minute is set to 0 because time is red as 00*/
        if(minute == 0){
            setTime += "00";
        }
        else{
            setTime += minute;
        }
        
        setTime += amPm;                                //append the am or pm char
        
        printToLCD(topLine, setTime);                   //Display the current brew time             
    
}


void printToLCD(String top, String bottom){
    
    clearLCDScreen();
    lcd.setCursor(0, 0);                                //Set cursor to top left
    lcd.print(top);                                     //clear LCD
    lcd.setCursor(0, 1);                                //Set cursor to top left
    lcd.print(bottom);                                  //clear LCD
    lcd.setCursor(0,0);                                 //Return the cursor to home
}

void clearLCDScreen(){
    
        /*Next 5 lines clears the screen and resets the cursor to home*/
        lcd.setCursor(0, 0);                            //Set cursor to top left
        lcd.print("                                ");  //clear LCD
        lcd.setCursor(0, 1);                            //Set cursor to top left
        lcd.print("                                ");  //clear LCD
        lcd.setCursor(0,0);                             //Set the cursor to home
        
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

