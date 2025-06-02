int ledRed = 13;
int ledYellow = 12;
int ledGreen = 11;
int buzzerPin = 9;
int pot1 = A1;
int pot2 = A2;
int button1 = A4;
int button2 = A5;
int infrared = 4;
void testLeds(int led, int d);
void testPot(int pot, char message[20]);
void testButton(int button);
void controlLeds(int red, int yellow, int green, int pot);
void controlBuzzer(int buzzerPin, int pot);


void setup() {
  // outputs
  pinMode(ledRed,OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen,OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(infrared,OUTPUT);
//  inputs
  pinMode(pot1,INPUT);
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  
  Serial.begin(9600);

  digitalWrite(buzzerPin, LOW);
}

void loop() {
  // main code

  testPot(pot1, "Pot1");
  testPot(pot2, "Pot2");
  controlLeds(ledRed, ledYellow,ledGreen,pot1);
 
//  testLeds(ledRed,1000);
//  testLeds(ledYellow,1000);
//  testLeds(ledGreen,1000);
testButton(button2);
//controlBuzzer(buzzerPin,Pot2);
delay(100);

}


//test leds
void testLeds(int led, int d){
  digitalWrite(led,1);
  delay(d);
  digitalWrite(led,0);
  delay(d);
  
}

//test potentiometers
void testPot(int pot, char message[20]){
 Serial.print(message);
 Serial.print(": ");
 Serial.println(analogRead(pot)); 
 }
// test buttons 
void testButton(int button){

  Serial.println(digitalRead(button));
  
  
  }

// control leds using the pots

void controlLeds(int red, int yellow, int green, int pot){
  
int  potval = analogRead(pot);

  if (potval >=683){
     digitalWrite(red,HIGH);
     digitalWrite(green, LOW);
     digitalWrite(yellow,LOW);
    
    }
  else if(potval >= 341 && potval < 683){
    digitalWrite(yellow,HIGH);
    digitalWrite(red,LOW);
    digitalWrite(green,LOW);
    
    }
  else{
      
      digitalWrite(green, HIGH);
      digitalWrite(yellow,LOW);
      digitalWrite(red,LOW);
      
      }
  
  
  
  
  }

void controlBuzzer(int buzzerPin, int pot)
{
int potval = analogRead(pot);
if(digitalRead(button2))
  

}
