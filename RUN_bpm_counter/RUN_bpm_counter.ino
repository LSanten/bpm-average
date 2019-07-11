// Leon Santen

// if doesnt connect to arduino use:
// sudo chmod a+rw /dev/ttyACM0

#include<LiquidCrystal.h>



// initalize the library with the numbers of the interface pins
LiquidCrystal lcd(12,11,5,4,3,2);



int led1 = 9;
int button = 10;
int button_last_status; // will be set to 1 when button pressed; to 0 when not pressed

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(led1, OUTPUT); // LED lights up when button is pressed --> digitalRead(button) == LOW
  pinMode(button, INPUT); // this is button for bpm counter. Press to beat. LOW is pressed. HIGH is not pressed.

  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);

  lcd.print("avg. BPM:");
  lcd.setCursor(10, 0); // (column, row) --> it starts with 0
  lcd.print("123.55");
  lcd.setCursor(0, 1);
  lcd.print("----------------");

}

void loop() {
  // put your main code here, to run repeatedly:
    
    
  if (digitalRead(button) == HIGH) //if button is pressed (LOW), led will light up
  {
    digitalWrite(led1, LOW);
    button_last_status = 0;
  }
  else 
  {
    digitalWrite(led1, HIGH);
    
  
    if (button_last_status == 0) // print millis when first button push in a row
    {
      uint32_t t1 = millis();  
      Serial.println(t1); // print millis since program started
    }
  
    button_last_status = 1; // sets button status to 1 so that Serial doesn't print continuously but only first time when button pressed
  }
  

}
