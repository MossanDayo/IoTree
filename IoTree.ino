#include <Adafruit_NeoPixel.h>

#define LED_COUNT 120
#define LED_PIN   6
#define BUTTON    2

Adafruit_NeoPixel led = Adafruit_NeoPixel( LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int state = 0;

void setup() {
  Serial.begin(38400);
  led.begin();
  led.setBrightness(64); // 0-255の範囲で輝度を調整
  led.show();
  pinMode(BUTTON, INPUT);
}

void loop() {
  switch (state) {
    case 0:
      if (pushButton() == true) state++;
      break;
    case 1:
      if (show_1() == true)  state++;
      break;
    case 2:
      if (show_2() == true) state++;
      break;
    case 3:
      if (show_3() == true) state++;
      break;
    case 4:
      if (show_4() == true) state++;
      break;
    case 5:
      if (show_5() == true) state++;
      break;
    case 6:
      if (show_6() == true) state++;
      break;
    default:
      state = 0;
      break;
  }
}

boolean pushButton() {
  if (digitalRead(BUTTON) == HIGH) {
    while (digitalRead(BUTTON) == HIGH) {}
    led.clear();
    return true;
  }
  return false;
}


boolean show_1(){
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


boolean show_2() {
  int r = random(0, 255);
  int g = random(0, 255);
  int b = random(0, 255);
  static int pixel[20];
  pixel[0] = random(1, 120);

  led.setPixelColor(pixel[0], led.Color(r, g, b));
  led.show();
  delay(200);

  led.setPixelColor(pixel[19], led.Color(0, 0, 0));

  for (int i = 19; i > 0; i--) {
    pixel[i] = pixel[i - 1];
  }

  if (pushButton() == true) return true;  
  return false;
}


boolean show_3() {
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


boolean show_4() {
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


boolean show_5() {
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


boolean show_6() {
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

//  for (int i = 0; i < 256; i++) {
//    led.setPixelColor(i, led.Color(0, 0, 0));  
//  }
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

//  for (int i = 0; i < 256; i++) {
//    led.setPixelColor(i, led.Color(0, 0, 0));  
//  }
  led.clear();
  led.show();

  if (pushButton() == true) return true;
  return false;
}

