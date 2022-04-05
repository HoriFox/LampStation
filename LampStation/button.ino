#include "button.h"

int clickTime = 450;  // max ms between clicks for a double click event
int holdTime = 2000;  // ms hold period: how long to wait for press+hold event

int countClick = 0;
long lastUpTime = -1;
long lastDownTime = -1;
bool buttonVal = LOW;
bool buttonValLast = LOW;
bool resetButtonUp = true;
bool resetButtonDown = true;

int checkButton()
{  
    int event = 0;
    buttonVal = digitalRead(TOUCH_PIN);

    if (buttonValLast != buttonVal) {
      //Serial.println("Смена button!"); 
      if (buttonVal == HIGH)
      {
        //Serial.println("Down"); 
        lastDownTime = millis();
        resetButtonDown  = false;
      } 
      else if (buttonVal == LOW) 
      {
        //Serial.println("Up"); 
        if ((millis()-lastUpTime) <= clickTime) {
          countClick += 1;
        }
        lastUpTime = millis();
        resetButtonUp = false;
      }
      buttonValLast = buttonVal;
    } else if (!resetButtonUp && (millis()-lastUpTime) > clickTime && !resetButtonDown && !buttonVal) {
      //Serial.println("Сброс up!"); 
      // Череда кликов оборвалась, ограничитель
      event = (countClick + 1) > 3 ? 3 : countClick + 1;
      countClick = 0;
      resetButtonUp = true;
    } else if (!resetButtonDown && (millis()-lastDownTime) > holdTime && buttonVal) {
      //Serial.println("Сброс down!"); 
      event = -1;
      resetButtonDown  = true;
      resetButtonUp = true;
    }

    return event;
}
