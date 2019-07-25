// Leon Santen

// if doesnt connect to arduino use:
// sudo chmod a+rw /dev/ttyACM0

// if display doesn't work --> page 140 - https://github.com/Freenove/Freenove_Ultimate_Starter_Kit_for_Arduino/blob/master/Tutorial.pdf 

#include<LiquidCrystal.h>

// initalize the library with the numbers of the interface pins
LiquidCrystal lcd(12,11,5,4,3,2);



int led1 = 9;
int button = 10;
int buttonLastStatus; // will be set to 1 when button pressed; to 0 when not pressed
int maxInterval = 3000; // max time in milliseconds after which BPM resets itself
int minInterval = 200; // min interval between button pushs in milliseconds

uint32_t pressTime; //millis() when button pressed 
uint32_t firstBeat = 0; // millis of first beat
uint32_t lastBeat = 0; // millis of last beat
uint32_t beatCount = 0; // number of how many times one has pressed the button

float intervalTime;
float bpm;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(led1, OUTPUT); // LED lights up when button is pressed --> digitalRead(button) == LOW
  pinMode(button, INPUT); // this is button for bpm counter. Press to beat. LOW is pressed. HIGH is not pressed.

  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);

  // Welcome Display
  lcd.setCursor(0, 0); // (column, row) --> it starts with 
  lcd.print("BPM Counter");
  lcd.setCursor(13, 1);
  lcd.print(":-)");
  delay(1800);
  lcd.clear();

  // Counter Mode display without values
  lcd.setCursor(0, 0);
  lcd.print("Avg. BPM:");
  lcd.setCursor(10, 1);
  lcd.print("---.--");


}

void loop() {
  // put your main code here, to run repeatedly:
    
    
  if (digitalRead(button) == HIGH) { //if button is pressed (LOW), led will light up
    digitalWrite(led1, LOW);
    buttonLastStatus = 0;
  }
  else 
  {
    digitalWrite(led1, HIGH);
    
  
    if (buttonLastStatus == 0) // save press time if first button push in a row
    {
      pressTime = millis();

      if (pressTime - lastBeat > maxInterval and lastBeat != 0 ) //resets BPM counter as soon as maxInterval is reached
      {
        // reset BPM variables
        firstBeat = 0;
        lastBeat = 0;
        beatCount = 0;

        // reset Screen
        lcd.clear();
      }

      

      if (pressTime - lastBeat < minInterval) {// let's counter only increment when interval between push is bigger than minimalInterval
      }
      else {
        beatCount++; 
 

        if (beatCount == 1) // sets first button push time to firstBeat, then last one to lastBeat
        {
          firstBeat = pressTime;
        }
        else if (beatCount > 1)
        {
          lastBeat = pressTime;
          intervalTime = (lastBeat - firstBeat)/(beatCount - 1);
          bpm = 60000/((float(lastBeat) - float(firstBeat))/(float(beatCount) - 1.00));
          
        }
  
        // Serial Prints
        Serial.println(pressTime); // print millis since program started
  
        // LCD Prints        
        lcd.setCursor(0, 0);
        lcd.print("Avg. BPM:");

        if (bpm >= 100.00){ // places BPM correctly on display depending on float's length
          lcd.setCursor(10, 1);
          lcd.print(bpm);
        }
        else {
          lcd.setCursor(10, 1);
          lcd.print(" ");
          
          lcd.setCursor(11, 1);
          lcd.print(bpm);
        }
        

        /*
        //Debugging Screen
        lcd.setCursor(0, 0); // firstBeat
        lcd.print(firstBeat);
        
        lcd.setCursor(0, 1); // lastB
        lcd.print(lastBeat);

        lcd.setCursor(10, 0); // BPM
        lcd.print(bpm);
   
        //lcd.setCursor(10, 0); // intervalTime
        //lcd.print(intervalTime);
    
        //lcd.setCursor(8, 0); // pressTime
        //lcd.print(pressTime);
    
        lcd.setCursor(14, 1); // print beatCount on LCD screen
        lcd.print(beatCount);
        */
        
      }
      
    }
      
    buttonLastStatus = 1; // sets button status to 1 so that Serial doesn't print continuously but only first time when button pressed
  }

  // Show arrow on display when maxInterval exceeded as state feedback
  uint32_t currentMillis = millis();
  if (currentMillis - lastBeat > maxInterval and beatCount > 1) {
    lcd.setCursor(6, 1);
    lcd.print("-->");
  }


}
