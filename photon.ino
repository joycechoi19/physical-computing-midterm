/*  
    This application controls a servo
    Development environment specifics:
    Particle Build environment (https://www.particle.io/build)
    Particle Photon RedBoard
    Released under the MIT License(http://opensource.org/licenses/MIT)
*/
#include <stdlib.h>

Servo myservo;// create servo object using the built-in Particle Servo Library

int button = D1;    //declare variable for button
int servoPin = D0;  //declare variable for servo
int pos = 0;        //variable to keep track of the servo's position
bool flag = 1;      //variable to keep track of the button presses

// This routine runs only once upon reset
void setup()
{
  Serial.begin(9600);//Start the Serial port @ 9600 baud

  pinMode(button, INPUT_PULLUP);   // sets button pin as input with internal pullup resistor

  Particle.subscribe("physical_computing_light_status", myHandler);
  Particle.subscribe("physical_computing_will", shreyaInit);
  myservo.attach(servoPin);  //Initialize the servo attached to pin D0
  myservo.write(180);        //set servo to furthest position
  delay(500);                //delay to give the servo time to move to its position
  myservo.detach();          //detach the servo to prevent it from jittering
  
  pinMode(D6, OUTPUT);

}

void myHandler(const char *event, const char *data){
    if(atoi(data) > 2000){
          pos = 0;
        
          Particle.publish("physical_computing_switch_status","turned_on");
    
          myservo.attach(servoPin);
          myservo.write(pos);
          delay(500);           //debounce and give servo time to move
          pos = 180;
          myservo.write(pos);
          delay(500);           //debounce and give servo time to move
          myservo.detach();
    
          flag = !flag;         //set flag to the opposite of what it's currently set to
          Serial.println(pos);  //prints to the serial port to keep track of the position
    }
}

void shreyaInit(const char *event, const char *data) {
    Particle.publish("shrey initted!");
    for (int i = 0; i < 5; i++) { // flash 5 times
        digitalWrite(D6,HIGH);
        delay(200);
        digitalWrite(D6, LOW);
        delay(100);
    }
}
