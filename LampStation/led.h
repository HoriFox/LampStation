#pragma once
#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>
#include "definitions.h"

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, ORING_LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t wheel(byte WheelPos);
void rainbow(uint8_t wait);

class ColorPro {
  public:
    bool power = false;
    uint16_t red = 0;
    uint16_t targetRed = 0;
    uint16_t green = 0;
    uint16_t targetGreen = 0;
    uint16_t blue = 0;
    uint16_t targetBlue = 0;
    float alpha = 0;

    ColorPro(uint16_t red_, uint16_t green_, uint16_t blue_, float alpha_ = 0) {
      targetRed = red_;
      targetGreen = green_;
      targetBlue = blue_;
      alpha = alpha_;
    }

    void updateLed() {
      if ( red < targetRed ) red += 1;
      if ( red > targetRed ) red -= 1;
    
      if ( green < targetGreen ) green += 1;
      if ( green > targetGreen ) green -= 1;
    
      if ( blue < targetBlue ) blue += 1;
      if ( blue > targetBlue ) blue -= 1;
   
      updateColor();

      float l_wait_ms = 3.0;
      delay(l_wait_ms);
    }

    uint32_t currentColor() {
      return strip.Color(uint16_t(red * alpha), uint16_t(green * alpha), uint16_t(blue * alpha));
    }
    
    void setColor(uint16_t red_, uint16_t green_, uint16_t blue_) {
      targetRed = red_;
      targetGreen = green_;
      targetBlue = blue_;
    }

    void setRandomColor() {
      targetRed = uint16_t(random(256));
      targetGreen = uint16_t(random(256));
      targetBlue = uint16_t(random(256));
    }

    void setAlpha(float alpha_) {
      if (alpha_ < 0) alpha_ = 0;
      //power = (alpha_ == 0) ? false : true;
      alpha = alpha_;
      updateColor();
    }

    void checkoutPower(bool autoPower = true, bool power_ = false) {
      if (autoPower) {
        power = !power;
      } else {
        if (power == power_) return;
        power = power_;
      }
      float l_wait_ms = 10.0;
      if (power) {
        for (int i = 1; i <= 20; i++) {
          setAlpha(0.05 * i);
          delay(l_wait_ms);
        }
      } else {
        for (int i = 20; i > 0; i--) {
          setAlpha(0.05 * i);
          delay(l_wait_ms);
        }
        setAlpha(0);
      }
      Serial.println("Изменили активность (power): " + String(power));
    }

    void heil() {
      float lastAlpha = alpha;
      float l_wait_ms = 10.0;
      int l_iteration = 2;
      for (int v = 1; v <= l_iteration; v++) { 
        int smooth_value = 20;
        float smooth_sep = 1.0 / smooth_value;
        for (int i = 1; i <= smooth_value; i++) {
          setAlpha(lastAlpha - (smooth_sep * i));
          delay(l_wait_ms);
        }
        for (int i = smooth_value; i > 0; i--) {
          setAlpha(lastAlpha - (smooth_sep * (i - 1)));
          delay(l_wait_ms);
        }
      }
      setAlpha(lastAlpha);
    }

    void updateColor() {
      uint32_t color = currentColor();
      for (int q = 0; q <= NUMPIXELS; q++) {
        strip.setPixelColor(q, color);
      }
      strip.show();
    }
};

ColorPro color_pro = ColorPro(100, 100, 100);

#endif // LED_H
