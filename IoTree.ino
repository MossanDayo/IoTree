#include <Adafruit_NeoPixel.h>

#define LED_COUNT ( 120 )
#define DIGITAL_PIN ( 6 )
#define BUTTON ( 2 )

Adafruit_NeoPixel led = Adafruit_NeoPixel( LED_COUNT,DIGITAL_PIN , NEO_GRB + NEO_KHZ800);

int state = 0;

void setup() {
  Serial.begin(38400);
  led.begin();
  led.show();
  pinMode(BUTTON, INPUT);
}

void loop() {
  switch (state) {
    case 0:
      led.begin();
      if (pushButton() == true) state++;
      break;
    case 1:
      if (show_1() == true) {
        led.begin();
        state++;
      }
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
  int led_r = random(0, 255);
  int led_g = random(0, 255);
  int led_b = random(0, 255);
  static int pixel[20];
  pixel[0] = random(1, 120);

  led.setPixelColor(pixel[0], led.Color(led_r, led_g, led_b));
  led.show();
  delay(200);

  led.setPixelColor(pixel[19], led.Color(0, 0, 0));

  pixel[19] = pixel[18];
  pixel[18] = pixel[17];
  pixel[17] = pixel[16];
  pixel[16] = pixel[15];
  pixel[15] = pixel[14];
  pixel[14] = pixel[13];
  pixel[13] = pixel[12];
  pixel[12] = pixel[11];
  pixel[11] = pixel[10];
  pixel[10] = pixel[9];
  pixel[9] = pixel[8];
  pixel[8] = pixel[7];
  pixel[7] = pixel[6];
  pixel[6] = pixel[5];
  pixel[5] = pixel[4];
  pixel[4] = pixel[3];
  pixel[3] = pixel[2];
  pixel[2] = pixel[1];
  pixel[1] = pixel[0];

  if (pushButton() == true) return true;  
  return false;
}

boolean show_3() {
  for (int i = 20; i <= 200; i++) {
    for (int j = 0; j <= 120; j++) {
      led.setPixelColor(j, led.Color(i, 20, 0));  
    }
    led.show();
  }
  delay(120);
  for (int i = 200; i >= 20; i--) {
    for (int j = 0; j <= 120; j++) {
      led.setPixelColor(j, led.Color(i, 20, 0));  
    }
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
    delay(20);
  }

  if (pushButton() == true) return true;  
  delay(100);
  if (pushButton() == true) return true;  

  return false;
}

boolean show_5() {
  for (int i = 0; i < 256; i++) {
    int led_r = random(0, 100);
    int led_g = random(0, 100);
    int led_b = random(0, 100);
    led.setPixelColor(i, led.Color(led_r, led_g, led_b));  
  }

  led.show();
  delay(1000);

  if (pushButton() == true) return true;  
  return false;
}

boolean show_6() {
  for (int i = 0; i < 256; i++) {
    int led_r = random(0, 100);
    int led_g = random(0, 100);
    int led_b = random(0, 100);
    led.setPixelColor(i, led.Color(led_r, led_g, led_b));  
    i++;
  }

  led.show();
  delay(1200);

  for (int i = 0; i < 256; i++) {
    led.setPixelColor(i, led.Color(0, 0, 0));  
  }
  led.show();

  for (int i = 1; i < 256; i++) {
    int led_r = random(0, 100);
    int led_g = random(0, 100);
    int led_b = random(0, 100);
    led.setPixelColor(i, led.Color(led_r, led_g, led_b));  
    i++;
  }

  led.show();
  delay(1200);

  for (int i = 0; i < 256; i++) {
    led.setPixelColor(i, led.Color(0, 0, 0));  
  }
  led.show();

  if (pushButton() == true) return true;  
  return false;
}

