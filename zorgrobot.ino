#include <Servo.h>
#define SPEAKER 3


// SERVO VARIABLES
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

// PRESSURE SENSOR VARIABLES
int fsrAnalogPin = 1; // FSR is connected to analog 0
int fsrReading;      // the analog reading from the FSR resistor divider

// SPEAKER TABS
int BassTab[]={1911,600,415,1333,900,1500,1012};//bass 1~7


int mood = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  myservo.attach(4);  // attaches the servo on pin 9 to the servo object
  initSpeaker();
}

void loop() {
  // put your main code here, to run repeatedly:
  moodDecay();
  touchInput();
  
  // READING INPUTS
  int value = analogRead(A0);

  // PRESSURE SENSOR READING
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);

  // LIGHT READING
  Serial.print("Analog reading light = ");
  Serial.println(value);


  // PRESSURE SENSOR READING
  Serial.print("Mood = ");
  Serial.println(mood);

  delay(1000);
}

void moodDecay(){
  if(mood > -100){
      mood = mood -1;  
  }
} 

void touchInput(){
      fsrReading = analogRead(fsrAnalogPin);

      if(fsrReading > 5){
        mood = mood + 5;  
        playTouchSound(fsrReading);
        wiggle();
      }
}


void playTouchSound(int fsrReading){
  for(int note_index=0;note_index<7;note_index++)
  {
      sound(note_index);
  }
}

void wiggle(){
  // SERVO CODE
  for (pos = 0; pos <= 180; pos += 10) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 10) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void initSpeaker()
{
    pinMode(SPEAKER,OUTPUT);
    digitalWrite(SPEAKER,LOW);
}

void sound(uint8_t note_index)
{
    for(int i=0;i<100;i++)
    {
        digitalWrite(SPEAKER,HIGH);
        delayMicroseconds(BassTab[note_index]);
        digitalWrite(SPEAKER,LOW);
        delayMicroseconds(BassTab[note_index]);
    }
}
