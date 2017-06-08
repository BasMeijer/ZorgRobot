#include <Servo.h>
#define SPEAKER 3


// SERVO VARIABLES
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

// PRESSURE SENSOR VARIABLES
int fsrAnalogPin = 1; // FSR is connected to analog 0
int fsrReading;      // the analog reading from the FSR resistor divider

// SPEAKER TABS

int HappySound[]={600,500,550,400};
int NeutralSound[]={1200,1900,1300,1000};
int SadSound[]={1900,1400};


// MOOD SETTING
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

  playMoodSounds(mood);
  
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
        if(mood < 150){
          mood = mood + 50; 
        }
        playHappySound();
        wiggle();
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

void sound(uint8_t note_index, int soundTab[])
{
    for(int i=0;i<100;i++)
    {
        digitalWrite(SPEAKER,HIGH);
        delayMicroseconds(soundTab[note_index]);
        digitalWrite(SPEAKER,LOW);
        delayMicroseconds(soundTab[note_index]);
    }
}

void playMoodSounds(int mood){

  long randNumber = random(10);
  Serial.print("Random mood number ");
  Serial.println(randNumber);

  if(randNumber == 5){
    if(mood > 80){
      // play happy sound
      playHappySound();
    }else if(mood > 20 && mood < 80){
      // play neutral sound
      playNeutralSound();
    }else if(mood < 20){
      playSadSound();
    }
  }

}

void playHappySound(){
  for(int note_index=0;note_index<7;note_index++)
  {
    for(int i=0;i<100;i++)
    {
        digitalWrite(SPEAKER,HIGH);
        delayMicroseconds(HappySound[note_index]);
        digitalWrite(SPEAKER,LOW);
        delayMicroseconds(HappySound[note_index]);
    }
  }
}

void playNeutralSound(){
  for(int note_index=0;note_index<7;note_index++)
  {
    for(int i=0;i<100;i++)
    {
        digitalWrite(SPEAKER,HIGH);
        delayMicroseconds(NeutralSound[note_index]);
        digitalWrite(SPEAKER,LOW);
        delayMicroseconds(NeutralSound[note_index]);
    }
  }
}

void playSadSound(){
  for(int note_index=0;note_index<2;note_index++)
  {
    for(int i=0;i<100;i++)
    {
        digitalWrite(SPEAKER,HIGH);
        delayMicroseconds(SadSound[note_index]);
        digitalWrite(SPEAKER,LOW);
        delayMicroseconds(SadSound[note_index]);
    }
  }
}
