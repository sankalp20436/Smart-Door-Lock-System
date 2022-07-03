#include <Keypad.h>
#include<Servo.h>
#include<LiquidCrystal.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[ROWS] = { 6,7,8,9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10,11,12}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
Servo myServo;

LiquidCrystal lcd(A0,A1,A1,A2,A3,A4,A5);

int pos=0;
int i=0; 
char password[5];
char S[5]="2021";
int redled=4;
int greenled=5;
int buzz=3;
int invalidcount=12;

void setup()
{  
  myServo.attach(2);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("DOOR LOCK SYSTEM");
  delay(3000);
  lcd.clear();
  //Serial.print("Enter Password:");
  lcd.setCursor(0,0);
  digitalWrite(redled, HIGH); 
  lcd.print("Enter Password");
}



void loop()
{
  char key = customKeypad.getKey(); 
  if(key)
  {
    if(key!='#'&&key!='*')
    {
      //Serial.print('*');
      lcd.setCursor(i,1);
      lcd.print('*');
      keypress();
      password[i]=key;
      password[i+1]=NULL;
      i++;
    }  
    if(key=='#')
    {
      //Serial.println();
      if(strcmp(password,S)==0)
          {
            digitalWrite(greenled, HIGH); 
            digitalWrite(redled, LOW); 
            //Serial.println("ACCESS GRANTED");
            lcd.clear();
            lcd.print("ACCESS GRANTED");
            unlockbuzz();
            delay(1500);
            lcd.clear();
            lcd.print("WELCOME HOME!!");
            ServoOpen();
            unlockbuzz();

            
            clearData();
          }
      else if(strcmp(password,S)!=0)
         {
           //Serial.println("ACCESS DENIED");
           lcd.clear();
           lcd.print("ACCESS DENIED");
           digitalWrite(redled, LOW);
           delay(150);
           digitalWrite(redled, HIGH);
           digitalWrite(buzz, HIGH);
           
          digitalWrite(redled, HIGH);
           delay(3000);
            
           digitalWrite(buzz,LOW);
           delay(2000);
           lcd.setCursor(0,0);
           lcd.print("Enter Password");
            
           clearData();
         }
      i=0;             
    }
    if(key=='*')
    {
      //Serial.println("CLOSING");
      lcd.clear();
      digitalWrite(redled, HIGH);
       digitalWrite(greenled, LOW); 
            
      lcd.print("GET IN WITHIN ");
      //ServoClose();
      delay(2000);
      lcd.setCursor(0,0);
      lcd.print("Enter Password");
      clearData();
    } 
  }
 delay(100);
}

void keypress()
{
 
 
 
digitalWrite(buzz, HIGH);
delay(50);
digitalWrite(buzz, LOW);
}
void ServoOpen()
{
 for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(25);  
    
    
   
  /*
  for(;pos<=90;pos+=10)
  {
    myServo.write(pos);
    delay(40);
    */
  }
}
void ServoClose()
{

  for (pos = 0; pos <= 180; pos -= 5) { 
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
      
    delay(15);
   
    
  }

  /*for(;pos>=0;pos-=10)
  {
    myServo.write(pos);
    delay(40);
   
  }
  */
}
void unlockbuzz()
{
 
digitalWrite(buzz, HIGH);
delay(80);
digitalWrite(buzz, LOW);
delay(80);
digitalWrite(buzz, HIGH);
delay(80);
digitalWrite(buzz, LOW);
delay(200);
digitalWrite(buzz, HIGH);
delay(80);
digitalWrite(buzz, LOW);
delay(80);
digitalWrite(buzz, HIGH);
delay(80);
digitalWrite(buzz, LOW);
delay(80);
}


void clearData()
{
  password[0]=NULL;
}
