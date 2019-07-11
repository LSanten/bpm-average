// Leon Santen

// if doesnt connect to arduino use:
// sudo chmod a+rw /dev/ttyACM0

#include<LiquidCrystal.h>

// initalize the library with the numbers of the interface pins
LiquidCrystal lcd(12,11,5,4,3,2);



int led1 = 9;
int button = 10;
int buttonLastStatus; // will be set to 1 when button pressed; to 0 when not pressed
int maxInterval = 3000; // max time in milliseconds after which BPM resets itself
int minInterval = 200; // min interval between button pushs in milliseconds

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

  /* LCD Screen Print Example
  lcd.print("avg. BPM:");
  lcd.setCursor(10, 0); // (column, row) --> it starts with 0
  lcd.print("123.55");
  lcd.setCursor(0, 1);
  lcd.print("----------------");
  */
  lcd.setCursor(0, 0);
  lcd.print("BPM Counter");
  lcd.setCursor(0, 1);
  lcd.print("----------------");
  delay(2500);
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:
    
    
  if (digitalRead(button) == HIGH) //if button is pressed (LOW), led will light up
  {
    digitalWrite(led1, LOW);
    buttonLastStatus = 0;
  }
  else 
  {
    digitalWrite(led1, HIGH);
    
  
    if (buttonLastStatus == 0) // print millis when first button push in a row
    {
      uint32_t t1 = millis();

      if (t1 - lastBeat > maxInterval and lastBeat != 0 ) //resets BPM counter as soon as maxInterval is reached
      {
        // reset BPM variables
        firstBeat = 0;
        lastBeat = 0;
        beatCount = 0;

        // reset Screen
        lcd.clear();
      }

      

      if (t1 - lastBeat < minInterval) // let's counter only increment when interval between push is smaller than minimalInterval
      {
        
      }
      else
      {
        beatCount++; 
 

        if (beatCount == 1) // sets first button push time to firstBeat, then last one to lastBeat
        {
          firstBeat = t1;
        }
        else if (beatCount > 1)
        {
          lastBeat = t1;
          intervalTime = (lastBeat - firstBeat)/(beatCount - 1);
          
        }
  
        // Serial Prints
        Serial.println(t1); // print millis since program started
  
        // LCD Prints
  
        
  
        //Debugging Screen
        lcd.setCursor(0, 0); //firstBeat
        lcd.print(firstBeat);
        
        lcd.setCursor(0, 1); //lastB
        lcd.print(lastBeat);
  
        lcd.setCursor(10, 0); //t1
        lcd.print(intervalTime);
    
        //lcd.setCursor(8, 0); //t1
        //lcd.print(t1);
    
        lcd.setCursor(14, 1); // print beatCount on LCD screen
        lcd.print(beatCount);
      }
      
    }
      
    buttonLastStatus = 1; // sets button status to 1 so that Serial doesn't print continuously but only first time when button pressed
  }
  

}
