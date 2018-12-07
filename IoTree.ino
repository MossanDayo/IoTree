#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "rgb_lcd.h"

#define LED_COUNT 120
#define LED_PIN   6
#define BUTTON    2
#define CdS       2

Adafruit_NeoPixel led = Adafruit_NeoPixel( LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
rgb_lcd lcd;

void setup() {
  Serial.begin(38400);
  led.begin();
  led.setBrightness(120); // 0-255の範囲で輝度を調整
  led.show();

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.noAutoscroll();

  pinMode(BUTTON, INPUT);
}

void loop() {
  static unsigned long cur_mTime;
  static unsigned long pre_mTime;
  static unsigned int h;
  static unsigned int m;
  static unsigned int s;
  
  static int state = 0;

  lcd.setCursor(0, 0);
  lcd.print("[");
  lcd.setCursor(1, 0);
  lcd.print(state);
  lcd.setCursor(2, 0);
  lcd.print("]");

  cur_mTime = millis();
  cur_mTime = cur_mTime / 1000;

  int diff = 0;
  diff = cur_mTime - pre_mTime;
  if (diff > 0) {
    s ++;
    if (s > 59) {
      m++;
      s = 0;
    }
    if (m > 59) {
      h++;
      m = 0;
    }
    if (h > 23) {
      h = 0;
    }
  }
  pre_mTime = cur_mTime;

  if (h < 10) {
    lcd.setCursor(2, 1);
    lcd.print(h);
  } else {
    lcd.setCursor(1, 1);
    lcd.print(h);
  }
  lcd.setCursor(3, 1);
  lcd.print(":");

  if (m < 10) {
    lcd.setCursor(4, 1);
    lcd.print("0");
    lcd.setCursor(5, 1);
    lcd.print(m);
  } else {
    lcd.setCursor(4, 1);
    lcd.print(m);
  }
  lcd.setCursor(6, 1);
  lcd.print(":");

  if (s < 10) {
    lcd.setCursor(7, 1);
    lcd.print("0");
    lcd.setCursor(8, 1);
    lcd.print(s);
  } else {
    lcd.setCursor(7, 1);
    lcd.print(s);
  }
  
  // 部屋が暗くなったらLED消灯
  int val = analogRead(CdS);
  if (val > 810) {
    led.clear();
    led.show();
    state = 0;
  }
  lcd.setCursor(13, 0);
  lcd.print(val);

  //memo
  //前回暗くて、今回明るいならLED点灯

  switch (state) {
    case 0:
      if (pushButton() == true) state++;
      break;
    case 1:
      if (line() == true)  state++;
      break;
    case 2:
      if (random_blink() == true) state++;
      break;
    case 3:
      if (slow_blink_orange() == true) state++;
      break;
    case 4:
      if (slow_blink_blue() == true) state++;
      break;
    case 5:
      if (random_lighting() == true) state++;
      break;
    case 6:
      if (random_lighting_2() == true) state++;
      break;
    default:
      state = 0;
      break;
  }
}

boolean pushButton() {
  if (digitalRead(BUTTON) == HIGH) {
    while (digitalRead(BUTTON) == HIGH) {}
    delay(200);
    led.clear();
    led.show();
    return true;
  }
  return false;
}


boolean line(){
  for (int i = 0 ; i < LED_COUNT + 20; i++ ) {
    int r = random(0, 255);
    int g = random(0, 255);
    int b = random(0, 255);

    led.setPixelColor(i-20,led.Color(0,0,0));
    led.setPixelColor(i,led.Color(r, g, b));

    led.show();
    delay(20);

    if (pushButton() == true) return true;  
  }
  return false;
}


boolean random_blink() {
  static int pixel[20];
  pixel[0] = random(1, 120);

  int r = random(0, 255);
  int g = random(0, 255);
  int b = random(0, 255);

  led.setPixelColor(pixel[0], led.Color(r, g, b));
  led.setPixelColor(pixel[19], led.Color(0, 0, 0));
  led.show();

  delay(50);

  for (int i = 19; i > 0; i--) {
    pixel[i] = pixel[i - 1];
  }

  if (pushButton() == true) return true;  
  return false;
}


boolean slow_blink_orange() {
  for (int i = 20; i <= 200; i++) {
    for (int j = 0; j <= 120; j++) {
      led.setPixelColor(j, led.Color(i, 20, 0));  
    }
    if (pushButton() == true) return true;
    led.show();
  }
  
  delay(120);
  
  for (int i = 200; i >= 20; i--) {
    for (int j = 0; j <= 120; j++) {
      led.setPixelColor(j, led.Color(i, 20, 0));  
    }
    if (pushButton() == true) return true;
    led.show();
  }

  if (pushButton() == true) return true;  
  return false;
}


boolean slow_blink_blue() {
  for (int i = 0; i <= 100; i++) {
    for (int j = 0; j <= 120; j++) {
      led.setPixelColor(j    , led.Color(i, i, i));  
      led.setPixelColor(j + 1, led.Color(10, 80, i));
      j++;
    }
    led.show();
    if (pushButton() == true) return true;
    delay(20);
  }
  
  if (pushButton() == true) return true;  
  delay(100);
  if (pushButton() == true) return true;  

  for (int i = 100; i >= 0; i--) {
    for (int j = 0; j <= 120; j++) {
      led.setPixelColor(j    , led.Color(i, i, i));  
      led.setPixelColor(j + 1, led.Color(10, 80, i));
      j++;
    }
    led.show();
    if (pushButton() == true) return true;
    delay(20);
  }

  if (pushButton() == true) return true;  
  delay(100);
  if (pushButton() == true) return true;  

  return false;
}


boolean random_lighting() {
  for (int i = 0; i < 256; i++) {
    int r = random(0, 100);
    int g = random(0, 100);
    int b = random(0, 100);
    led.setPixelColor(i, led.Color(r, g, b));  
  }

  led.show();
  if (pushButton() == true) return true;
  delay(1000);

  if (pushButton() == true) return true;  
  return false;
}


boolean random_lighting_2() {
  for (int i = 0; i < 256; i++) {
    int r = random(0, 100);
    int g = random(0, 100);
    int b = random(0, 100);
    led.setPixelColor(i, led.Color(r, g, b));  
    i++;
  }

  led.show();
  if (pushButton() == true) return true;
  delay(1200);
  if (pushButton() == true) return true;

  led.clear();
  led.show();

  for (int i = 1; i < 256; i++) {
    int r = random(0, 100);
    int g = random(0, 100);
    int b = random(0, 100);
    led.setPixelColor(i, led.Color(r, g, b));  
    i++;
  }

  led.show();
  if (pushButton() == true) return true;
  delay(1200);
  if (pushButton() == true) return true;

  led.clear();
  led.show();

  if (pushButton() == true) return true;
  return false;
}

