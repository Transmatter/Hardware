#include "Keyboard.h"
int adc_key_val [5] = {50, 200, 400, 600, 800};
int NUM_KEYS = 5;
int adc_key_in;
int key = -1;
int oldkey = -1;
bool hold_m = false;
bool status_mode = false;

void setup (){
   Serial.begin (9600); // 9600 bps
   Keyboard.begin();
}

void loop (){
   adc_key_in = analogRead (0);
   digitalWrite (13, LOW);
   key = get_key (adc_key_in);
 
   if (key != oldkey) {
      delay (50);
      adc_key_in = analogRead (0);
      key = get_key (adc_key_in);
      if (key != oldkey) {
         oldkey = key;
         if (key >= 0) {
            digitalWrite (13, HIGH);
            switch (key) {
               case 0: browsing_content(); //s1
               break;
               case 1:home_page();//s2
               break;
               case 2: load_more(); //s3
               break;
               case 3: searching_content(); //s4
               break;
               case 4: confirm();//s5
               break;
            }
         }
      }
   }
   delay (100);
}
void home_page() {
  Serial.println("S2 OK");
  status_mode = !status_mode;
  if(status_mode) {
    Serial.println("v is pressed");
    Keyboard.press('v');
    delay(100);
    Keyboard.release('v');
  } else {
    Serial.println("Arrow Up is pressed");
    Keyboard.press(KEY_UP_ARROW);
    delay(100);
    Keyboard.release(KEY_UP_ARROW);  
  }
}

void load_more() {
  Serial.println ("S3 OK");
  Keyboard.press(KEY_DOWN_ARROW);
  delay(100);
  Keyboard.release(KEY_DOWN_ARROW);
}

void browsing_content() {
  Serial.println ("S1 OK");
  Keyboard.press('x');
  delay(100);
  Keyboard.release('x');
}

void searching_content() {
  hold_m = !hold_m;
  if(hold_m){
      Serial.println ("press m");
      Keyboard.press('m');
  } else {
      Serial.println ("release m");
      Keyboard.release('m');
      delay(1500);
      Keyboard.press(KEY_RETURN);
      delay(100);
      Keyboard.release(KEY_RETURN);
  }
}

void confirm() {
  Serial.println ("S5 OK");
  Keyboard.press('/');
  delay(100);
  Keyboard.release('/');
}

// Convert ADC value to key number
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
