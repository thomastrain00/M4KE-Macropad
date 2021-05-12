/*
  Copyright (c) 2014-2016 NicoHood  https://github.com/NicoHood/HID
  Copyright (c) 2021 thomastrain00  https://github.com/thomastrain00

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <HID-Project.h>
#include <HID-Settings.h>

/*
   Code below is derived from the Surface Dial Example from HID-Project library:
*/
// input pins for encoder channel A and channel B
const int pinA = 2;
const int pinB = 3;

// input pin for pushbutton
const int pinButton = 4;

volatile bool previousButtonValue = false;

volatile int previous = 0;
volatile int counter = 0;

/*
   Assign pins for switches and leds here:
   Change '4' in 'switchPins[4]' to the number of pins you're using for your switches.
   I'm using for 4 switches, hence 4 pins and '4'.
   Note: 'switchPins[4]' is of type integer with an array size of 4.
   The same logic applies to 'ledPins[3]'
*/

const int switchPins[4] = { 10, 14, 15, 16 };
const int ledPins[3] = { 5, 6, 9 }; //Must be PWM pins if you want to adjust colors

/*
   Color assigned to their respective pin:
*/
enum ledColors {
  red = 9,
  blue = 5,
  green
};

/*
   Names for layers:
*/
enum layers {
  MEDIA = 0,
  ONENOTE,
  EDITING,
  ZOOM_DISCORD
};

int layout = MEDIA;

bool debugON = false;

void setup() {

  /*
     Code below is derived from the Surface Dial Example from HID-Project library:
  */
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  pinMode(pinButton, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), changed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), changed, CHANGE);

  SurfaceDial.begin();

  Consumer.begin();
  Keyboard.begin();

  if (debugON) {
    Serial.begin(9600);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(switchPins[i], INPUT_PULLUP);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

//----------------------------------------
void changed() {
  int A = digitalRead(pinA);
  int B = digitalRead(pinB);

  int current = (A << 1) | B;
  int combined  = (previous << 2) | current;

  if (combined == 0b0010 ||
      combined == 0b1011 ||
      combined == 0b1101 ||
      combined == 0b0100) {
    counter++;
  }

  if (combined == 0b0001 ||
      combined == 0b0111 ||
      combined == 0b1110 ||
      combined == 0b1000) {
    counter--;
  }

  previous = current;
}
//----------------------------------------

void initLayerLED (int activeLayer)
{
  switch (activeLayer) //set led color depending on active layout/layer
  {
    case MEDIA: //red

      analogWrite(red, 255);
      analogWrite(green, 0);
      analogWrite(blue, 0);
      break;
    case ONENOTE: //cyan
      analogWrite(red, 0);
      analogWrite(green, 255);
      analogWrite(blue, 255);
      break;
    case EDITING: //green
      analogWrite(red, 0);
      analogWrite(green, 255);
      analogWrite(blue, 0);
      break;
    case ZOOM_DISCORD: //blue
      analogWrite(red, 0);
      analogWrite(green, 0);
      analogWrite(blue, 255);
      break;
    default:
      break;
  }
}
/*
   Go to: https://tinyurl.com/thomastrain00 for my keymap
*/

void keymap (int activeSwitch)
{
  switch (activeSwitch) //perform specific action depending on the key pressed
  {
    case 10:
      if (layout == ONENOTE) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('v');  //If you're using a letter in your macro, make sure it is LOWERCASE ('CTRL+V' is not the same as 'CTRL+v').
        delay(100);
        Keyboard.releaseAll();
      }
      else if (layout == EDITING) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('v');
        delay(100);
        Keyboard.releaseAll();
      }
      else if (layout == ZOOM_DISCORD) {
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press('s');
        delay(100);
        Keyboard.releaseAll();
      }
      else {
        Keyboard.write('l');
      }
      break;
    case 14:
      if (layout == ONENOTE ) {
        Keyboard.write(KEY_ESC);
      }
      else if (layout == EDITING) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('c');
        delay(100);
        Keyboard.releaseAll();
      }
      else if (layout == ZOOM_DISCORD) {
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press('v');
        delay(100);
        Keyboard.releaseAll();
      }
      else {
        Consumer.write(MEDIA_VOLUME_MUTE);
      }
      break;
    case 15:
      if (layout == ONENOTE ) {
        Keyboard.write(KEY_DELETE);
      }
      else if (layout == EDITING) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('x');
        delay(100);
        Keyboard.releaseAll();
      }
      else if (layout == ZOOM_DISCORD) {
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press('a');
        delay(100);
        Keyboard.releaseAll();
      }
      else {
        Consumer.write(MEDIA_PLAY_PAUSE);
      }
      break;
    case 16:  //Layer Toggle
      if (layout == MEDIA) {
        layout = ONENOTE;
        Serial.println("ONENOTE LAYER ACTIVE");
      }
      else if (layout == ONENOTE) {
        layout = EDITING;
        Serial.println("EDITING LAYER ACTIVE");
      }
      else if (layout == EDITING) {
        layout = ZOOM_DISCORD;
        Serial.println("ZOOM_DISCORD LAYER ACTIVE");
      }
      else if (layout == ZOOM_DISCORD ) {
        layout = MEDIA;
        Serial.println("MEDIA LAYER ACTIVE");
      }
      break;
    default:
      break;
  }
  delay(250); //basic debouncing
}

void loop() {
  /*
     Code below is derived from the Surface Dial Example from HID-Project library:
  */
  bool buttonValue = digitalRead(pinButton);
  if (buttonValue != previousButtonValue) {
    if (buttonValue) {
      SurfaceDial.press();
    } else {
      SurfaceDial.release();
    }
    previousButtonValue = buttonValue;
  }

  if (counter >= 4) {
    SurfaceDial.rotate(100); //keep this at 100 if you want each detent to be one "step"
    Serial.println("UP");
    counter -= 4;
  } else if (counter <= -4) {
    SurfaceDial.rotate(-100);
    Serial.println("DOWN");
    counter += 4;
  }
  //----------------------------------------

  initLayerLED(layout);

  //check each key for input:
  for (int i = 0; i < 4; i++)
  {
    if (!digitalRead(switchPins[i])) //if a key is pressed, proceed
    {
      keymap(switchPins[i]);
    }
  }
}
