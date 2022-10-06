#include "Keyboard.h"
int adc_key_val[5] ={600,650, 700,  800, 900 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;
int s1 = 2;
int s2 = 3;
int s3 = 4;
int s4 = 5;

void setup(){
  pinMode(13, OUTPUT);  
  Serial.begin(9600);
  Keyboard.begin();
}

void loop(){
  adc_key_in = analogRead(0);    // read the value from the sensor
  digitalWrite(13,LOW);
  key = get_key(adc_key_in);  // convert into key press
  int v1 = digitalRead(s1);
  int v2 = digitalRead(s2);
  int v3 = digitalRead(s3);
  int v4 = digitalRead(s4);
  
  if (v1 == 0) {
    Keyboard.press('z');
    Serial.println("z");
    delay(100);
    Keyboard.release('z');
  }
    if (v2 == 0) {
    Keyboard.press('x');
    Serial.println("x");
    delay(100);
    Keyboard.release('x');
  }
    if (v3 == 0) {
    Keyboard.press('c');
    Serial.println("c");
    delay(100);
    Keyboard.release('c');
  }
    if (v4 == 0) {
    Keyboard.press('m');
    Serial.println("m");
    delay(100);
    Keyboard.release('m');
  }
  if (key != oldkey){
    delay(50);  // wait for debounce time
    adc_key_in = analogRead(0);    // read the value from the sensor
    key = get_key(adc_key_in);    // convert into key press
    if (key != oldkey){
      oldkey = key;
      if (key >=0){
        digitalWrite(13,HIGH);
        switch(key){
           case 0:
                  Keyboard.press(KEY_UP_ARROW);
                  delay(100);
                  Keyboard.release(KEY_UP_ARROW);
                  Serial.println("arrow up");
                  break;
           case 1:
                  Keyboard.press(KEY_LEFT_ARROW);
                  delay(100);
                  Keyboard.release(KEY_LEFT_ARROW);
                  Serial.println("arrow left");
                  break;
           case 2:
                  Keyboard.press(KEY_DOWN_ARROW);
                  delay(100);
                  Keyboard.release(KEY_DOWN_ARROW);
                  Serial.println("arrow down");
                  break;
           case 3:
                  Keyboard.press(KEY_RIGHT_ARROW);
                  delay(100);
                  Keyboard.release(KEY_RIGHT_ARROW);
                  Serial.println("arrow right");
                  break;
           case 4:
                  Keyboard.press(' ');
                  delay(100);
                  Keyboard.release(' ');
                  Serial.println("spacebar");
                  break;
        }
      }
    }
  }
 delay(100);
}

int get_key(unsigned int input){
    int k;
    for (k = 0; k < NUM_KEYS; k++){
      if (input < adc_key_val[k]){
            return k;
        }
   }
   if (k >= NUM_KEYS)k = -1;  // No valid key pressed
   return k;
}
